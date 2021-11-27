/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:12:03 by pweinsto          #+#    #+#             */
/*   Updated: 2021/11/27 19:36:07 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lex_analyzer(t_data *data)
{
	t_lex	*lex;
	char	*token;
	char	quote;

	quote = 0;
	token = (char *)ft_calloc(1, sizeof(char));
	lex_analyzer2(&lex, data, &token, &quote);
	if (ft_strlen(token))
		space(&lex, &token);
	free(token);
	//print_lex(lex);
	parser(lex, data);
	return (1);
}

int	lex_analyzer2(t_lex **lex, t_data *data, char **token, char *quote)
{
	while (*data->str)
	{
		if (*data->str == ' ')
			space(lex, token);
		else if (*data->str == SQUOTE)
			*quote = SQUOTE;
		else if (*data->str == DQUOTE)
			*quote = DQUOTE;
		else if (*data->str == '>' || *data->str == '<')
			redirection(lex, token, data);
		else if (*data->str == '|')
			pipes(lex, token);
		else if (*data->str == '$')
			dollar(lex, token, data);
		else
			*token = ft_strchrjoin(*token, *data->str);
		data->str++;
		if (*quote)
			quotes(token, data, quote);
	}
	return (1);
}

int	dollar(t_lex **lex, char **token, t_data *data)
{
	data->str++;
	if (!*data->str || *data->str == ' ')
	{
		*token = ft_strchrjoin(*token, '$');
		space(lex, token);
		data->str--;
		return (1);
	}
	else if (*data->str == '?')
	{
		*token = ft_strjoin(*token, ft_itoa(data->error_ret));
		space(lex, token);
		return (1);
	}
	else if (ft_isdigit(*data->str))
		return (1);
	else if (*data->str == '>' || *data->str == '<')
	{
		*token = ft_strchrjoin(*token, '$');
		redirection(lex, token, data);
	}
	dollar2(lex, token, data);
	return (1);
}

int	dollar2(t_lex **lex, char **token, t_data *data)
{
	char	*var;
	int		i;
	char	*res;

	var = (char *)ft_calloc(1, sizeof(char));
	if (ft_isalpha(*data->str))
	{
		while (ft_isalpha(*data->str) || ft_isdigit(*data->str))
		{
			var = ft_strchrjoin(var, *data->str);
			data->str++;
		}
		data->str--;
		var = ft_strchrjoin(var, '=');
		i = get_envnum(data->envp, var);
		if (i >= 0)
		{
			res = ft_substr(data->envp[i], ft_strlen(var), \
			ft_strlen(data->envp[i]) - ft_strlen(var));
			*token = ft_strjoin(*token, res);
			space(lex, token);
		}
	}
	return (1);
}

int	pipes(t_lex **lex, char **token)
{
	space(lex, token);
	ft_lexcreate(lex, NULL, PIPE);
	return (1);
}

int	redirection(t_lex **lex, char **token, t_data *data)
{
	char	c;

	c = *data->str;
	space(lex, token);
	data->str++;
	if (*data->str == c)
	{
		if (c == '>')
			ft_lexcreate(lex, NULL, APPEND);
		else
			ft_lexcreate(lex, NULL, HEREDOC);
	}
	else
	{
		if (c == '>')
			ft_lexcreate(lex, NULL, OUTPUT);
		else
			ft_lexcreate(lex, NULL, INPUT);
		data->str--;
	}
	return (1);
}

int	quotes(char **token, t_data *data, char *quote)
{
	while (*data->str)
	{
		if (*data->str == *quote && quote_reset(data, quote))
			break ;
		else if (*data->str == '$' && *quote == DQUOTE)
		{
			data->str++;
			if (*data->str && ft_isdigit(*data->str))
				data->str++;
			else if (*data->str && !ft_isalpha(*data->str))
				*token = ft_strchrjoin(*token, '$');
			else
			{
				quotes_var(token, data);
				if (*data->str == '"' && quote_reset(data, quote))
					break ;
			}
		}
		*token = ft_strchrjoin(*token, *data->str);
		data->str++;
	}
	return (1);
}

int	quote_reset(t_data *data, char *quote)
{
	*quote = 0;
	data->str++;
	return (1);
}

int	quotes_var(char **token, t_data *data)
{
	char	*var;
	int		i;
	char	*res;

	var = (char *)ft_calloc(1, sizeof(char));
	while (*data->str && (ft_isalpha(*data->str) || ft_isdigit(*data->str)))
	{
		var = ft_strchrjoin(var, *data->str);
		data->str++;
	}
	var = ft_strchrjoin(var, '=');
	i = get_envnum(data->envp, var);
	if (i >= 0)
	{
		res = ft_substr(data->envp[i], ft_strlen(var), \
		ft_strlen(data->envp[i]) - ft_strlen(var));
		*token = ft_strjoin(*token, res);
	}
	return (1);
}

int	space(t_lex **lex, char **token)
{
	if (ft_strlen(*token) == 0)
		return (1);
	ft_lexcreate(lex, ft_strdup(*token), WORD);
	free(*token);
	*token = (char *)ft_calloc(1, sizeof(char));
	**token = '\0';
	return (1);
}

char	*ft_strchrjoin(char *s1, char const s2)
{
	char			*new_string;
	unsigned int	index;
	unsigned int	length;

	length = ft_strlen(s1) + 1;
	new_string = ft_calloc(length + 1, sizeof(char));
	if (!new_string)
		return (0);
	index = 0;
	while (index < length && s1[index] != '\0')
	{
		new_string[index] = s1[index];
		index++;
	}
	s1 = NULL;
	free(s1);
	new_string[index] = s2;
	index++;
	new_string[index] = '\0';
	return (new_string);
}
