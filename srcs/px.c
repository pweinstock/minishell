/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:50:41 by khirsig           #+#    #+#             */
/*   Updated: 2021/09/27 17:05:49 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipex(int argc, char **argv, char **envp, t_data *data)
{
	if (error_handler(data, argc, argv) == ERROR)
		return (1);
	parsing_envpath(data, envp);
	if (forking(data, envp) == ERROR)
		return (1);
	write(2, "Test\n", 6);
	return (0);
}
