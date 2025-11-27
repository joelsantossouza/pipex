/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_chain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:10:00 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/27 20:59:31 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

int	exec_pipe_chain(size_t size, char **cmds, char **envp, int end[2])
{
	t_cmd	cmd;
	int		pipe1[2];
	int		pipe2[2];

	if (pipe(pipe1) < 0)
		return (-1);
	cmd = (t_cmd){};
	if (get_cmd(&cmd, *cmds, envp) < 0 || execve_pipe(&cmd, envp, end[0], pipe1[1]) < 0)
		return (close_pipe(pipe1[0], pipe1[1]), free_cmd(&cmd), -1);
	while (size-- && *cmds)
	{
		if (pipe(pipe2) < 0)
			return (close_pipe(pipe1[0], pipe1[1]), -1);
		close(pipe1[1]);
		if (get_cmd(&cmd, *cmds, envp) < 0 || execve_pipe(&cmd, envp, pipe1[0], pipe2[1]) < 0)
			return (close(pipe1[0]), free_cmd(&cmd), -1);
		close(pipe1[0]);
		if (pipe(pipe1) < 0)
			return (close_pipe(pipe2[0], pipe2[1]), -1);
		close(pipe2[1]);
		if (get_cmd(&cmd, *cmds, envp) < 0 || execve_pipe(&cmd, envp, pipe2[0], pipe1[1]) < 0)
			return (close(pipe2[0]), free_cmd(&cmd), -1);
		close(pipe2[0]);
	}
	close(pipe1[1]);
	if (get_cmd(&cmd, *cmds, envp) < 0 || execve_pipe(&cmd, envp, pipe1[0], pipe2[1]) < 0)
		return (close(pipe1[0]), free_cmd(&cmd), -1);
	close(pipe1[0]);
	return (0);
}
