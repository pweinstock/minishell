/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:12:03 by pweinsto          #+#    #+#             */
/*   Updated: 2021/12/01 13:13:54 by pweinsto         ###   ########.fr       */
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
