/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 18:02:37 by pweinsto          #+#    #+#             */
/*   Updated: 2021/11/09 15:12:53 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lex_analyzer(t_lex *lex, char *str, t_data *data)
{
	char	*token;
	t_lex	*element;

	token = (char *)malloc(sizeof(char));
	str--;
	*str = 0;
	str++;
	while (*str)
	{
		if (*str == ' ')
			space(&lex, &token);
		else if (*str == '>')
		{
			if (output(&lex, &token, &*str) == 2)
				str++;
		}
		else if (*str == '<')
		{
			if (input(&lex, &token, &*str) == 2)
				str++;
		}
		else if (*str == '|')
			pipes(&lex, &token);
		else if (*str == '\'')
			str += squote(&lex, &token, &*str);
		else if (*str == '"')
			str += dquote(&lex, &token, &*str);
		else
			token = ft_strchrjoin(token, *str);
		str++;
	}
	if (ft_strlen(token))
	{
		if (lex == NULL)
			lex = ft_lexnew(ft_strdup(token), WORD);
		else
		{
			element = ft_lexnew(ft_strdup(token), WORD);
			ft_lexadd_back(lex, element);
		}
	}
	//free(token);
	//print_lex(lex);
	parser(lex, data);
	return (1);
}

int	dquote(t_lex **lex, char **token, char *str)
{
	t_lex	*element;
	int i;

	if (*lex == NULL && ft_strlen(*token))
	{
		*lex = ft_lexnew(ft_strdup(*token), WORD);
	}
	else if (ft_strlen(*token))
	{
		element = ft_lexnew(ft_strdup(*token), WORD);
		ft_lexadd_back(*lex, element);
	}
	free(*token);
	*token = (char *)malloc(sizeof(char));
	**token = '\0';
	str--;
	if (*str != ' ' && *str != 0)
	{
		if (*lex == NULL)
			*lex = ft_lexnew("\"", CDQUOTE);
		else
		{
			element = ft_lexnew("\"", CDQUOTE);
			ft_lexadd_back(*lex, element);
		}
	}
	else
	{
		if (*lex == NULL)
			*lex = ft_lexnew("\"", DQUOTE);
		else
		{
			element = ft_lexnew("\"", DQUOTE);
			ft_lexadd_back(*lex, element);
		}
	}

	i = 0;
	str += 2;
	while (*str != '"')
	{
		if (*str == 0)
		{
			printf("Error!\n");
			break;
		}
		*token = ft_strchrjoin(*token, *str);
		str++;
		i++;
	}
	if (*lex == NULL && ft_strlen(*token))
	{
		*lex = ft_lexnew(ft_strdup(*token), WORD);
	}
	else if (ft_strlen(*token))
	{
		element = ft_lexnew(ft_strdup(*token), WORD);
		ft_lexadd_back(*lex, element);
	}
	free(*token);
	*token = (char *)malloc(sizeof(char));
	**token = '\0';
	if (*str == '"')
	{
		str++;
		if (*str != ' ' && *str != 0)
		{
			element = ft_lexnew("\"", CDQUOTE);
			ft_lexadd_back(*lex, element);
		}
		else
		{
			element = ft_lexnew("\"", DQUOTE);
			ft_lexadd_back(*lex, element);
		}
	}
	return (i + 1);
}

int	squote(t_lex **lex, char **token, char *str)
{
	t_lex	*element;
	int i;

	if (*lex == NULL && ft_strlen(*token))
	{
		*lex = ft_lexnew(ft_strdup(*token), WORD);
	}
	else if (ft_strlen(*token))
	{
		element = ft_lexnew(ft_strdup(*token), WORD);
		ft_lexadd_back(*lex, element);
	}
	free(*token);
	*token = (char *)malloc(sizeof(char));
	**token = '\0';
	str--;
	if (*str != ' ' && *str != 0)
	{
		if (*lex == NULL)
			*lex = ft_lexnew("'", CSQUOTE);
		else
		{
			element = ft_lexnew("'", CSQUOTE);
			ft_lexadd_back(*lex, element);
		}
	}
	else
	{
		if (*lex == NULL)
			*lex = ft_lexnew("'", SQUOTE);
		else
		{
			element = ft_lexnew("'", SQUOTE);
			ft_lexadd_back(*lex, element);
		}
	}

	i = 0;
	str += 2;
	while (*str != '\'')
	{
		if (*str == 0)
		{
			printf("Error!\n");
			break;
		}
		*token = ft_strchrjoin(*token, *str);
		str++;
		i++;
	}
	if (*lex == NULL && ft_strlen(*token))
	{
		*lex = ft_lexnew(ft_strdup(*token), WORD);
	}
	else if (ft_strlen(*token))
	{
		element = ft_lexnew(ft_strdup(*token), WORD);
		ft_lexadd_back(*lex, element);
	}
	free(*token);
	*token = (char *)malloc(sizeof(char));
	**token = '\0';
	if (*str == '\'')
	{
		str++;
		if (*str != ' ' && *str != 0)
		{
			element = ft_lexnew("'", CSQUOTE);
			ft_lexadd_back(*lex, element);
		}
		else
		{
			element = ft_lexnew("'", SQUOTE);
			ft_lexadd_back(*lex, element);
		}
	}
	return (i + 1);
}

int	pipes(t_lex **lex, char **token)
{
	t_lex	*element;

	if (*lex == NULL && ft_strlen(*token))
	{
		*lex = ft_lexnew(ft_strdup(*token), WORD);
	}
	else if (ft_strlen(*token))
	{
		element = ft_lexnew(ft_strdup(*token), WORD);
		ft_lexadd_back(*lex, element);
	}
	free(*token);
	*token = (char *)malloc(sizeof(char));
	**token = '\0';
	element = ft_lexnew("|", PIPE);
	ft_lexadd_back(*lex, element);
	return (1);
}

int	input(t_lex **lex, char **token, char *str)
{
	t_lex	*element;

	if (*lex == NULL && ft_strlen(*token))
		*lex = ft_lexnew(ft_strdup(*token), WORD);
	else if (ft_strlen(*token))
	{
		element = ft_lexnew(ft_strdup(*token), WORD);
		ft_lexadd_back(*lex, element);
	}
	str++;
	if (*str == '<')
	{
		element = ft_lexnew("<<", HEREDOC);
		ft_lexadd_back(*lex, element);
		free(*token);
		*token = (char *)malloc(sizeof(char));
		**token = '\0';
		return(2);
	}
	else
	{
		if (*lex == NULL)
			*lex = ft_lexnew("<", INPUT);
		else
		{
			element = ft_lexnew("<", INPUT);
			ft_lexadd_back(*lex, element);
		}	
		free(*token);
		*token = (char *)malloc(sizeof(char));
		**token = '\0';
		return (1);
	}
}

int	output(t_lex **lex, char **token, char *str)
{
	t_lex	*element;

	if (*lex == NULL && ft_strlen(*token))
		*lex = ft_lexnew(ft_strdup(*token), WORD);
	else if (ft_strlen(*token))
	{
		element = ft_lexnew(ft_strdup(*token), WORD);
		ft_lexadd_back(*lex, element);
	}
	str++;
	if (*str == '>')
	{
		element = ft_lexnew(">>", APPEND);
		ft_lexadd_back(*lex, element);
		free(*token);
		*token = (char *)malloc(sizeof(char));
		**token = '\0';
		return(2);
	}
	else
	{
		element = ft_lexnew(">", OUTPUT);
		ft_lexadd_back(*lex, element);
		free(*token);
		*token = (char *)malloc(sizeof(char));
		**token = '\0';
		return (1);
	}
}

int	space(t_lex **lex, char **token)
{
	t_lex	*element;

	if (ft_strlen(*token) == 0)
		return (1);
	if (*lex == NULL)
	{
		*lex = ft_lexnew(ft_strdup(*token), WORD);
	}
	else
	{
		element = ft_lexnew(ft_strdup(*token), WORD);
		ft_lexadd_back(*lex, element);
	}
	free(*token);
	*token = (char *)malloc(sizeof(char));
	**token = '\0';
	return (1);
}

char	*ft_strchrjoin(char *s1, char const s2)
{
	char			*new_string;
	unsigned int	index;
	unsigned int	length;

	// if (!s1 || !s2)
	// 	return (0);
	length = ft_strlen(s1) + 1;
	new_string = malloc(length + 1);
	if (!new_string)
		return (0);
	index = 0;
	while (index < length && s1[index] != '\0')
	{
		new_string[index] = s1[index];
		index++;
	}
	//printf("s1: %s\ns2 %c\n", s1, s2);
	s1 = NULL;
	free(s1);
	new_string[index] = s2;
	index++;
	new_string[index] = '\0';
	return (new_string);
}