/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:06:54 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/28 16:11:24 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>

int	exec_pipe(char *pcmd, char **envp, int read_end, int write_end)
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
	if (dup2(read_end, STDIN_FILENO) < 0)
		(free_cmd(&cmd), exit(-1));
	if (dup2(write_end, STDOUT_FILENO) < 0)
		(free_cmd(&cmd), exit(-1)); // FD LEAK --> PREVIOUT DUP2 WORK CORRECTLY!
	if (read_end != STDIN_FILENO)
		close(read_end);
	if (write_end != STDOUT_FILENO)
		close(write_end);
	execve(cmd.path, cmd.argv, envp);
	(free_cmd(&cmd), exit(-1));
}
