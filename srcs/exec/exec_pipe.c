/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:06:54 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/29 13:50:16 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

static inline
void	clean_child(int pipe1[2], int pipe2[2], t_cmd *cmd)
{
	close_pipe(pipe1);
	close_pipe(pipe2);
	free_cmd(cmd);
}

int	exec_pipe(char *pcmd, char **envp, int pipe1[2], int pipe2[2])
{
	t_cmd	cmd;
	int		pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid != 0)
		return (pid);
	if (get_cmd(&cmd, pcmd, envp) < 0)
		(perror("get_cmd"), close_pipe(pipe1), close_pipe(pipe2), exit(errno));
	if (!cmd.path)
		(cmd_not_found(cmd.argv[0]), clean_child(pipe1, pipe2, &cmd), exit(127));
	if (dup2(pipe1[0], STDIN_FILENO) < 0)
		(perror("dup2"), clean_child(pipe1, pipe2, &cmd), exit(errno));
	if (dup2(pipe2[1], STDOUT_FILENO) < 0)
		(perror("dup2"), clean_child(pipe1, pipe2, &cmd), exit(errno));
	close_pipe(pipe1);
	close_pipe(pipe2);
	execve(cmd.path, cmd.argv, envp);
	(perror("execve"), free_cmd(&cmd), exit(errno));
}
