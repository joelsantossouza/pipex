#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	pid;

	(void) argc;
	(void) argv;
	pid = fork();
	printf("PID: %d\n", pid);
	return (0);
}

