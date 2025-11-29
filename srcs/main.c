/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:23:39 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/29 21:32:37 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int	file1;
	int	file2;

	if (argc < 5)
	{
		ft_fprintf(2, "Usage: %s <file1> <cmd1> <cmd2> [cmd...] <file2>\n", *argv);
		return (1);
	}
	file1 = open(argv[1], O_RDONLY);
	if (file1 < 0)
		(write(STDERR_FILENO, "pipex: ", 7), perror(argv[1]));
	file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (file2 < 0)
		return (close(file1), 2);
	return (exec_pipe_chain(argc - 3, argv + 2, envp, (int [2]){file1, file2}));
}
