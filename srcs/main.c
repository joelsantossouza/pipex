/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:23:39 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/26 20:53:43 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		ft_fprintf(2, "Usage: %s <file1> <cmd1> <cmd2> <file2>\n", *argv);
		return (1);
	}

	#include <unistd.h>
	int fd[2];

	if (pipe(fd) < 0)
		return (1);
	char *argv1[2] = {*(argv + 1), 0};
	t_cmd	cmd1 = {
		argv[1],
		argv1,
		envp,
	};
	char *argv2[2] = {*(argv + 2), 0};
	t_cmd	cmd2 = {
		argv[2],
		argv2,
		envp,
	};
	if (execve_pipe(&cmd1, 0, fd[1]) < 0)
		return (1);
	if (execve_pipe(&cmd2, fd[0], 1) < 0)
		return (2);

	close(fd[0]);
	close(fd[1]);
	return (0);
}
