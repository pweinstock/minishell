/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 08:42:53 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/05 15:28:26 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bltin_init(t_data *data)
{
	data->bltin_cmds = malloc(sizeof(char *) * 2);
	data->bltin_cmds[0] = ft_strdup("cd");
	data->bltin_cmds[1] = NULL;
	return (0);
}