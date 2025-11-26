/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:30:06 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/26 11:47:04 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"

int	exec_cmd(char **argv, char **envp, int fd_in, int fd_out, int tmp)
{
	const int	pid = fork();

	if (pid < 0)
		return (-1);
	if (pid != 0)
		return (pid);
	if (tmp)
	{
		dup2(fd_in, 0);
		dup2(fd_out, 1);
		close(fd_in);
		close(fd_out);
	}
	return (execve(argv[0], argv, envp));
}

int	main(int argc, char **argv, char **envp)
{
	const int	file1 = open(argv[1], O_RDONLY);
	const int	file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_RDWR, 0666);
	int			fd[2];
	int			i;

	if (argc < 5)
		return (1);
	if (pipe(fd) < 0)
		return (2);
	exec_cmd(ft_split(argv[2], ' '), envp, file1, fd[1], 1);
	i = 2;
	while (++i < (argc - 3))
	{
		exec_cmd(ft_split(argv[i - 1], ' '), envp, fd[0], fd[1], 0);
		exec_cmd(ft_split(argv[i], ' '), envp, fd[0], fd[1], 0);
	}
	exec_cmd(ft_split(argv[i], ' '), envp, fd[0], file2, 0);
	return (0);
}
