/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:06:54 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/29 12:12:08 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>

int	exec_pipe(char *pcmd, char **envp, int pipe1[2], int pipe2[2])
{
	t_cmd	cmd;
	int		pid;

	if (get_cmd(&cmd, pcmd, envp) < 0)
		return (-1);
	if (!cmd.path)
		return (free_cmd(&cmd), 0);
	pid = fork();
	if (pid < 0)
		return (free_cmd(&cmd), -1);
	if (pid != 0)
		return (free_cmd(&cmd), pid);
	if (dup2(pipe1[0], STDIN_FILENO) < 0)
		(free_cmd(&cmd), exit(-1));
	if (dup2(pipe2[1], STDOUT_FILENO) < 0)
		(free_cmd(&cmd), exit(-1)); // FD LEAK --> PREVIOUT DUP2 WORK CORRECTLY!
	close_pipe(pipe1);
	close_pipe(pipe2);
	execve(cmd.path, cmd.argv, envp);
	(free_cmd(&cmd), exit(-1));
}
