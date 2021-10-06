/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 08:42:53 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/05 15:57:05 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bltin_init(t_data *data)
{
	data->bltin_cmds = malloc(sizeof(char *) * 3);
	data->bltin_cmds[0] = ft_strdup("cd");
	data->bltin_cmds[1] = ft_strdup("exit");
	data->bltin_cmds[2] = NULL;
	return (0);
}