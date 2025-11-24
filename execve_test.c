#include <unistd.h>
#include "libft/libft.h"
#include <stdlib.h>

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
	char	**splited;

	if (argc != 5)
		return (1);
	pid = fork();
	if (pid == 0)
	{
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
	else
	{
		char	result[1000];
		int bytes_read = read(1, result, 1000);
		write(0, result, bytes_read);
		splited = ft_split(argv[2], ' ');
		if (!splited)
			return (2);
		if (execve(splited[0], splited, envp) < 0)
			return (5);
	}
	return (0);
}
