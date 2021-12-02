/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 08:16:08 by khirsig           #+#    #+#             */
/*   Updated: 2021/12/02 10:04:05 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	child_process(t_pipex *p_strct)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &p_strct->data->original_attr);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (p_strct->data->is_heredoc == TRUE)
	{
		p_strct->data->fd_in = open(".heredoc", O_RDWR);
		p_strct->data->is_heredoc = FALSE;
	}
	if (dup2(p_strct->data->fd_in, STDIN_FILENO) == -1)
		exit(errno);
	if (dup2(p_strct->data->fd_out, STDOUT_FILENO) == -1)
		exit(errno);
	runcmd(p_strct, p_strct->cmd);
	free_cmdpath(p_strct);
	exit(EXIT_SUCCESS);
}

static int	create_child(t_pipex *p_strct)
{
	p_strct->child = fork();
	if (p_strct->child == -1)
		return (ERROR);
	if (p_strct->child == 0)
		child_process(p_strct);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(p_strct->child, &p_strct->data->error_ret, 0);
	p_strct->data->is_child = TRUE;
	if (WIFSIGNALED(p_strct->data->error_ret) != 0)
	{
		if (WTERMSIG(p_strct->data->error_ret) == SIGINT)
			ft_putstr_fd("\n", 2);
		if (WTERMSIG(p_strct->data->error_ret) == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
		p_strct->data->error_ret = WTERMSIG(p_strct->data->error_ret);
		p_strct->data->error_ret += 128;
		return (0);
	}
	p_strct->data->error_ret = WEXITSTATUS(p_strct->data->error_ret);
	return (0);
}

int	forking(t_pipex *p_strct)
{
	int	is_bltin;

	is_bltin = 0;
	is_bltin = bltin_compare(p_strct->cmd[0]);
	dup2(p_strct->data->fd_in, STDIN_FILENO);
	dup2(p_strct->data->fd_out, STDOUT_FILENO);
	if (is_bltin != -1 && p_strct->data->is_piped == FALSE)
		p_strct->data->error_ret = runbltin(p_strct, p_strct->cmd, is_bltin);
	else
	{
		if (pipe(p_strct->end) == -1)
		{
			perror("Error");
			return (ERROR);
		}
		if (create_child(p_strct) == ERROR)
			return (ERROR);
		close(p_strct->end[0]);
		close(p_strct->end[1]);
	}
	return (0);
}
