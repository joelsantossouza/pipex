/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:37:17 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/30 12:53:46 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	heredoc(const char *delim)
{
	const int	delim_len = ft_strlen(delim);
	int			fd[2];
	char		*line;
	ssize_t		len;

	if (pipe(fd) < 0)
		return (perror("pipe"), -1);
	line = 0;
	while (1)
	{
		if (write(STDOUT_FILENO, "> ", 2) < 0)
			return (perror("write"), close_pipe(fd), -1);
		len = ft_getline(&line, STDIN_FILENO);
		if (len < 0)
			return (perror("ft_getline"), close_pipe(fd), -1);
		if (write(fd[1], line, len) < 0)
			return (perror("write"), close_pipe(fd), free(line), -1);
		if (!line || (!ft_strncmp(line, delim, delim_len) && line[delim_len] == '\n'))
			break ;
	}
	return (close(fd[1]), free(line), fd[0]);
}
