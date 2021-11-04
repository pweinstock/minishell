/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:23:04 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/04 08:06:30 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	runbltin(t_pipex *p_strct, char **cmd, int cmdnbr)
{
	if (cmdnbr == 0)
		bltin_cd(p_strct, cmd);
	if (cmdnbr == 1)
		bltin_exit(p_strct, cmd);
	if (cmdnbr == 2)
		bltin_pikachu();
	if (cmdnbr == 3)
		bltin_pwd(cmd);
	if (cmdnbr == 4)
		bltin_echo(p_strct, cmd);
	if (cmdnbr == 5)
		bltin_env(p_strct, cmd);
	if (cmdnbr == 6)
		bltin_unset(p_strct, cmd);
	if (cmdnbr == 7)
		bltin_export(p_strct, cmd);
	return ;
}
