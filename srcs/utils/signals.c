/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:41:11 by pweinsto          #+#    #+#             */
/*   Updated: 2021/11/27 18:11:07 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_signal(t_data *data)
{
	data->changed_attr = data->original_attr;
	data->changed_attr.c_lflag -= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &data->changed_attr);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	heredoc_signal(int sig)
{
	if (sig == SIGINT)
		close(0);
}
