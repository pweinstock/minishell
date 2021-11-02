/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 09:58:00 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/02 14:37:07 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# define TRUE 1
# define FALSE 0
# define ERROR -1

/*
** -----------------------------------------------------------------------------
** Includes
*/
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libs/libft/libft.h"
# include "minishell.h"

/*
** -----------------------------------------------------------------------------
** Structs and typedef.
*/

typedef struct s_pipex {
	char **cmd;
	char **envp;
	char **envpath;
	int	end[2];
	int cmdpathfound;
	int	cmd_amt;
	int	fd_in;
	int	fd_out;
	int	fd_temp;
	int	cmd_count;
	pid_t child;
}				t_pipex;

const static char	*g_bltin_cmds[9] = {
	"cd",
	"exit",
	"pikachu",
	"pwd",
	"echo",
	"env",
	"unset",
	"export",
	NULL
};
/*
** -----------------------------------------------------------------------------
** Function prototypes
*/
int		ft_chrsrch(char *haystack, char needle);
int		ft_revchrsrch(char *haystack, char needle);
int		get_envnum(char **envp, char *needle);

int		execute(char **input, t_data *data);
int		error_handler(t_pipex *p_strct, char *input);
void	runcmd(t_pipex *p_strct, char **cmd, char **envp);
int		forking(t_pipex *p_strct, char **envp);
void	parsing_envpath(t_pipex *p_strct, char **envp);
char	**split_args(char *temp);

void	bltin_cd(t_pipex *p_strct, char **cmd);
int		bltin_compare(char *needle);
int		bltin_init(t_pipex *p_strct);
void	bltin_exit(t_pipex *p_strct);
void	bltin_pikachu(void);
void	bltin_pwd(char **cmd);
void	bltin_echo(t_pipex *p_strct, char **cmd);
void	bltin_env(t_pipex *p_strct, char **cmd);
void	bltin_unset(t_pipex *p_strct, char **cmd);
void	bltin_export(t_pipex *p_strct, char **cmd);
void	runbltin(t_pipex *p_strct, char **cmd, int cmdnbr);


#endif