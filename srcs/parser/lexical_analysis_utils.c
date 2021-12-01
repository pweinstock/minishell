/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:15:15 by pweinsto          #+#    #+#             */
/*   Updated: 2021/12/01 13:14:07 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
