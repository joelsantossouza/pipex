/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_chain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:10:00 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/29 12:30:29 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <sys/wait.h>

int	exec_pipe_chain(size_t size, char **cmds, char **envp, int end[2])
{
	int	fd[2];

	if (pipe(fd) < 0)
		return (-1);
	if (exec_pipe(*cmds++, envp, end, fd) < 0)
		return (close_pipe(fd), -1);
	size -= 2;
	while (size-- && *cmds)
	{
		end[0] = fd[0];
		close(fd[1]);
		if (pipe(fd) < 0)
			return (close(end[0]), -1);
		if (exec_pipe(*cmds++, envp, end, fd) < 0)
			return (close(end[0]), close_pipe(fd), -1);
		safe_close(&end[0]);
	}
	safe_close(&fd[1]);
	if (exec_pipe(*cmds, envp, fd, end) < 0)
		return (close(fd[0]), -1);
	close(fd[0]);
	while (wait(NULL) > 0)
		;
	return (0);
}
