#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	fds[2];
	int	pid;
	int parent_nbr;
	int child_nbr;
	int	max;

	if (argc != 2)
		return (1);
	if (pipe(fds) < 0)
		return (2);
	max = atoi(argv[1]);
	pid = fork();
	if (pid == 0)
	{
		parent_nbr = 0;
		while (parent_nbr < max)
		{
			printf("increment by child: %d\n", parent_nbr++);
			write(fds[1], &parent_nbr, sizeof(parent_nbr));
			usleep(10000);
			read(fds[0], &parent_nbr, sizeof(parent_nbr));
		}
	}
	else
	{
		child_nbr = 0;
		while (child_nbr < max)
		{
			read(fds[0], &child_nbr, sizeof(child_nbr));
			printf("increment by parent %d\n", child_nbr++);
			usleep(100);
			write(fds[1], &child_nbr, sizeof(child_nbr));
		}
	}
	close(fds[0]);
	close(fds[1]);
	return (0);
}
