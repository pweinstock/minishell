/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:50:41 by khirsig           #+#    #+#             */
/*   Updated: 2021/09/29 08:40:57 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipex(int argc, char **argv, char **envp, t_data *data)
{
	t_pipex	p_strct;

	ft_bzero(&p_strct, sizeof(t_pipex));
	if (error_handler(&p_strct, argc, argv) == ERROR)
		return (1);
	parsing_envpath(&p_strct, envp);
	if (forking(&p_strct, data, envp) == ERROR)
		return (1);
	// write(2, "Test\n", 6);
	free(p_strct.envpath);
	return (0);
}
