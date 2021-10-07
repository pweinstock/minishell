/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 09:58:00 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/07 10:12:35 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"

/*
** -----------------------------------------------------------------------------
** Structs and typedef.
*/
typedef struct s_data {
	char	**envp;
	char	*cmd;
	char	*path_prefix;
	int		fd_in;
	int		fd_out;
}				t_data;

typedef struct s_pipex {
	char ***cmd;
	char **envpath;
	int	end[2];
	int cmdpathfound;
	int	cmd_amt;
	int	fd_temp;
	int	cmd_count;
	pid_t child;
}				t_pipex;

const static char	*g_bltin_cmds[4] = {
	"cd",
	"exit",
	"pikachu",
	NULL
};
/*
** -----------------------------------------------------------------------------
** Function prototypes
*/
int		ft_chrsrch(char *haystack, char needle);
int		ft_revchrsrch(char *haystack, char needle);

int		pipex(char *input, char **envp, t_data *data);
int		error_handler(t_pipex *p_strct, char *input);
void	runcmd(t_pipex *p_strct, char **cmd, char **envp);
int		forking(t_pipex *p_strct, t_data *data, char **envp);
void	parsing_envpath(t_pipex *p_strct, char **envp);

void	bltin_cd(t_data *data, char **cmd);
int		bltin_compare(char *needle);
int		bltin_init(t_data *data);
void	bltin_exit(t_data *data);
void	bltin_pikachu(void);

void	signal_handler(int sig);
void	specifier(t_data *data, char *str);


#endif