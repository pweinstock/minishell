/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:50:41 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/06 16:11:19 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipex(char *input, char **envp, t_data *data)
{
	t_pipex	p_strct;

	ft_bzero(&p_strct, sizeof(t_pipex));
	if (error_handler(&p_strct, input) == ERROR)
		return (1);
	parsing_envpath(&p_strct, envp);
	if (forking(&p_strct, data, envp) == ERROR)
		return (1);
	free(p_strct.envpath);
	free(p_strct.cmd);
	return (0);
}
