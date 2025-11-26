/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:06:54 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/26 20:48:49 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	execve_pipe(t_cmd *cmd, int read_end, int write_end)
{
	const int	pid = fork();

	if (pid < 0)
		return (-1);
	if (pid != 0)
		return (waitpid(pid, 0, 0));
	if (dup2(read_end, STDIN_FILENO) < 0)
		exit(-1);
	if (dup2(write_end, STDOUT_FILENO) < 0)
		exit(-1);
	close(read_end);
	close(write_end);
	if (execve(cmd->path, cmd->argv, cmd->envp) < 0)
		return (-1);
	exit(-1);
}
