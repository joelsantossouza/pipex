/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:23:39 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/30 17:32:37 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	const int	is_heredoc = ft_strcmp(argv[1], "here_doc") == 0;
	int			file1;
	int			file2;

	if (argc < 5 + is_heredoc)
	{
		ft_fprintf(STDERR_FILENO, "Usage: %s <file1 | here_doc DELIM> <cmd1> <cmd2> [cmd...] <file2>\n", *argv);
		return (1);
	}
	if (!is_heredoc)
	{
		file1 = open(argv[1], O_RDONLY);
		if (file1 < 0)
			(write(STDERR_FILENO, "pipex: ", 7), perror(argv[1]));
		file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (file2 < 0)
			return (write(STDERR_FILENO, "pipex: ", 7), perror(argv[argc - 1]), close(file1), 1);
		return (exec_pipe_chain(argc - 3, argv + 2, envp, (int [2]){file1, file2}));
	}
	file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (file2 < 0)
		return (write(STDERR_FILENO, "pipex: ", 7), perror(argv[argc - 1]), 1);
	return (exec_pipe_chain(argc - 4, argv + 3, envp, (int [2]){heredoc(argv[2]), file2}));
}
