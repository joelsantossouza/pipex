/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:06:54 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/28 12:32:45 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>

int	execve_pipe(t_cmd *cmd, char **envp, int read_end, int write_end)
{
	int	pid;

	if (!cmd->path)
		return (NOT_FOUND); // FOR SOME REASOM WHEN HAS AN INVALID COMMAND BETWEEN CMDS, THE PIPE CONTINUE TO THE VALID ONE, BUT SHOULD GIVE NOTHING AS OUTPUT
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid != 0)
		return (pid);
	if (dup2(read_end, STDIN_FILENO) < 0)
		exit(-1);
	if (dup2(write_end, STDOUT_FILENO) < 0)
		exit(-1); // FD LEAK --> PREVIOUT DUP2 WORK CORRECTLY!
	if (read_end != STDIN_FILENO)
		close(read_end);
	if (write_end != STDOUT_FILENO)
		close(write_end);
	execve(cmd->path, cmd->argv, envp);
	exit(-1);
}
