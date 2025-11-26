#include <unistd.h>
#include "libft/libft.h"
#include <stdlib.h>
#include <sys/wait.h>

int	listlen(char **argv)
{
	char	**ptr;

	ptr = argv;
	while (*ptr)
		ptr++;
	return (ptr - argv);
}

int	main(int argc, char **argv, char **envp)
{
	int		pid;
	int		pid2;
	char	**splited;
	int		fds[2];

	if (argc != 5)
		return (1);
	if (pipe(fds) < 0)
		return (2);
	pid = fork();

	if (pid == 0)
	{
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		splited = ft_split(argv[2], ' ');
		if (!splited)
			return (2);
		int	len = listlen(splited);
		char	*args[len + 2];
		ft_memcpy(args, splited, len * 8);
		args[len] = argv[1];
		args[len + 1] = NULL;
		if (execve(splited[0], args, envp) < 0)
			return (3);
		ft_fprintf(2, "Execve failed\n");
		free(splited); // GIVES LEAK ONCE THE PROGRAM SWAP THE CURRENT CODE AND MEMORY SEGMENT OF THE PROCESS
	}
	else if (0 == (pid2 = fork()))
	{
		dup2(fds[0], 0);
		close(fds[0]);
		close(fds[1]);
		splited = ft_split(argv[3], ' ');
		if (!splited)
			return (2);
		if (execve(splited[0], splited, envp) < 0)
			return (5);
	}
	close (fds[0]);
	close (fds[1]);

	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
