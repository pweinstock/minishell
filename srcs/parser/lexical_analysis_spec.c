/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis_spec.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:12:11 by pweinsto          #+#    #+#             */
/*   Updated: 2021/12/01 13:08:23 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
