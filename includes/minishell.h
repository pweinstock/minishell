/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 11:39:48 by pweinsto          #+#    #+#             */
/*   Updated: 2021/11/25 11:03:45 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"

# define WORD 1
# define OUTPUT 2
# define APPEND 3
# define INPUT 4
# define HEREDOC 5
# define PIPE 6
# define SQUOTE '\''
# define CSQUOTE 8
# define DQUOTE '"'
# define CDQUOTE 10

int	heredoc_break;

typedef struct	s_lex
{
	char *str;
	int type;
	struct s_lex *previous;
	struct s_lex *next;
}				t_lex;

typedef struct s_data {
	char	**envp;
	char	*path_prefix;
	char	*str;
	char	*file_in;
	char	*file_out;
	char	*file;
	int		is_heredoc;
	int		is_piped;
	int		is_child;
	int		fd_in;
	int		fd_out;
	int		original_stdin;
	int		original_stdout;
	int		redirection;
	int		error_ret;
}				t_data;

//signals.c
void	signal_handler(int sig);
void	stty(t_data *data);
void	heredoc_signal(int sig);

// list.c
t_lex	*ft_lexnew(char *str, int type);
void	ft_lexadd_back(t_lex *lst, t_lex *new);
int		lex_len(t_lex *lst);
void	print_lex(t_lex *lst);
int		free_list(t_lex *lst);
void ft_lexcreate(t_lex **lex, char *str, int type);

//lexical_analysis
int	lex_analyzer(t_lex *lex, t_data *data);
int	space(t_lex **lex, char **token);
char	*ft_strchrjoin(char *s1, char const s2);
int	output(t_lex **lex, char **token, t_data *data);
int	input(t_lex **lex, char **token, char *str);
int	pipes(t_lex **lex, char **token /*, t_data *data */);
// int	squote(t_lex **lex, char **token, char *str);
// int	dquote(t_lex **lex, char **token, char *str);
int	quotes(char **token, t_data *data, char *quote);
int	dollar(t_lex **lex, char **token, t_data *data);
// char	*ft_charmult(char c, int i);

int		execute(char **input, t_data *data);
void	init_data(t_data *data, char **envp);
void	rm(t_data *data);

//parsing
int	parser(t_lex *lex, t_data *data);
char	**str_array(t_lex *lst);
char	**ft_strarr_copy(char **str);


//utils
int	get_envnum(char **envp, char *needle);

#endif