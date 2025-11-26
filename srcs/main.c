/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:23:39 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/26 22:49:37 by joesanto         ###   ########.fr       */
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
	#include <sys/wait.h>
	#include <fcntl.h>
	int fd[2];

	if (pipe(fd) < 0)
		return (1);
	char *argv1[2] = {*(argv + 2), 0};
	t_cmd	cmd1 = {
		argv[2],
		argv1,
		envp,
	};
	char *argv2[2] = {*(argv + 3), 0};
	t_cmd	cmd2 = {
		argv[3],
		argv2,
		envp,
	};
	int	pid1;
	int	pid2;
	int file1 = open(argv[1], O_RDONLY);
	int file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	pid1 = execve_pipe(&cmd1, file1, fd[1]);
	close(fd[1]);
	pid2 = execve_pipe(&cmd2, fd[0], file2);
	close(fd[0]);

	waitpid(pid1, 0, 0);
	waitpid(pid2, 0, 0);

	return (0);
}
