/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_chain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:10:00 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/29 19:03:23 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <sys/wait.h>

static inline
int	last_cmd_status(int last_cmd_pid)
{
	int	status;

	waitpid(last_cmd_pid, &status, 0);
	while (wait(NULL) > 0)
		;
	return (WEXITSTATUS(status));
}

int	exec_pipe_chain(size_t size, char **cmds, char **envp, int end[2])
{
	int	fd[2];
	int	last_cmd_pid;

	if (pipe(fd) < 0)
		return (-1);
	if (exec_pipe(*cmds++, envp, end, fd) < 0)
		return (close_pipe(end), close_pipe(fd), -1);
	safe_close(&end[0]);
	safe_close(&fd[1]);
	while (size-- > 2 && *cmds)
	{
		end[0] = fd[0];
		if (pipe(fd) < 0)
			return (close_pipe(end), -1);
		if (exec_pipe(*cmds++, envp, end, fd) < 0)
			return (close_pipe(end), close_pipe(fd), -1);
		close(end[0]);
		close(fd[1]);
	}
	last_cmd_pid = exec_pipe(*cmds, envp, fd, end);
	if (last_cmd_pid < 0)
		return (close(fd[0]), safe_close(&end[1]), -1);
	close(fd[0]);
	safe_close(&end[1]);
	return (last_cmd_status(last_cmd_pid));
}
