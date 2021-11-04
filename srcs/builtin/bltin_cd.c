/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 08:39:20 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/04 15:07:20 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	old_pwd(t_pipex *p_strct, char *oldpath)
{
	int	envnum;

	envnum = get_envnum(p_strct->data->envp, "OLDPWD");
	if (envnum != -1)
	{
		free(p_strct->data->envp[envnum]);
		p_strct->data->envp[envnum] = ft_strjoin("OLDPWD=", oldpath);
	}
	else
		addback_env(p_strct, ft_strjoin("OLDPWD=", oldpath));
	return ;
}

void	no_such_file(char *str)
{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
}

void	bltin_cd(t_pipex *p_strct, char **cmd)
{
	int		envnum;
	char	*cwd;
	char	*oldpath;

	oldpath = getcwd(NULL, 0);
	envnum = get_envnum(p_strct->data->envp, "HOME=");
	if (!cmd[1] && envnum != -1 && chdir(p_strct->data->envp[envnum] + 5) == -1)
	{
		no_such_file(p_strct->data->envp[envnum]);
		return ;
	}
	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] == '\0')
	{
		envnum = get_envnum(p_strct->data->envp, "OLDPWD=");
		if (envnum != -1)
			chdir(p_strct->data->envp[envnum] + 7);
		else
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	}
	else if (cmd[1] && chdir(cmd[1]) == -1)
	{
		no_such_file(cmd[1]);
		return ;
	}
	cwd = getcwd(NULL, 0);
	cwd += ft_revchrsrch(cwd, '/') + 1;
	free(p_strct->data->path_prefix);
	p_strct->data->path_prefix = ft_strdup(cwd);
	old_pwd(p_strct, oldpath);
	return ;
}
