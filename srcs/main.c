/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:23:39 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/27 14:09:21 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	//if (argc < 5)
	//{
	//	ft_fprintf(2, "Usage: %s <file1> <cmd1> <cmd2> <file2>\n", *argv);
	//	return (1);
	//}
	if (argc < 3)
		return (1);

	#include <stdlib.h>
	#include <unistd.h>
	#include <sys/wait.h>
	int fd1[2];
	int fd2[2];

	if (pipe(fd1) < 0)
		return (1);
	if (pipe(fd2) < 0)
		return (1);
	argv++;
	t_cmd	cmd = {
		*argv,
		(char *[]){*argv, NULL},
	};
	int pid1 = execve_pipe(&cmd, envp, 0, fd1[1]);
	argv++;
	cmd = (t_cmd){
		*argv,
		(char *[]){*argv, NULL},
	};
	close(fd1[1]);
	int pid2 = execve_pipe(&cmd, envp, fd1[0], fd2[1]);
	close(fd1[0]);
	argv++;
	cmd = (t_cmd){
		*argv,
		(char *[]){*argv, NULL},
	};
	close(fd2[1]);
	int pid3 = execve_pipe(&cmd, envp, fd2[0], 1);
	close(fd2[0]);

	waitpid(pid1, 0, 0);
	waitpid(pid2, 0, 0);
	waitpid(pid3, 0, 0);
	return (0);
}
