/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_chain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:10:00 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/27 23:14:14 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

int	exec_pipe_chain(size_t size, char **cmds, char **envp, int end[2])
{
	t_cmd	cmd;
	int		fd[2];

	if (pipe(fd) < 0)
		return (-1);
	cmd = (t_cmd){};
	if (get_cmd(&cmd, *cmds++, envp) < 0 || execve_pipe(&cmd, envp, end[0], fd[1]) < 0)
		return (close_pipe(fd[0], fd[1]), free_cmd(&cmd), -1);
	size -= 2;
	while (size-- && *cmds)
	{
		end[0] = fd[0];
		close(fd[1]);
		if (pipe(fd) < 0)
			return (-1);
		if (get_cmd(&cmd, *cmds++, envp) < 0 || execve_pipe(&cmd, envp, end[0], fd[1]) < 0)
			return (close_pipe(fd[0], fd[1]), free_cmd(&cmd), -1);
		close(end[0]);
	}
	close(fd[1]);
	if (get_cmd(&cmd, *cmds, envp) < 0 || execve_pipe(&cmd, envp, fd[0], end[1]) < 0)
		return (close(fd[0]), free_cmd(&cmd), -1);
	close(fd[0]);
	free_cmd(&cmd);
	return (0);
}
