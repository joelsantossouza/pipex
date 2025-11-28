/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:38:17 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/28 12:22:26 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>

static inline
char	*get_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
			return (*envp);
		envp++;
	}
	return (0);
}

static inline
int	get_cmd_path(char **cmd_path, char *cmd, char *paths)
{
	char	*start;
	size_t	len;

	while (*paths)
	{
		start = paths + (*paths == ':');
		paths = ft_strchrnul(start, ':');
		len = paths - start;
		if (len <= 0)
			continue ;
		*cmd_path = malloc(sizeof(char) * (len + 2));
		if (!*cmd_path)
			return (-1);
		*(char *)ft_mempcpy(*cmd_path, start, len) = '/';
		(*cmd_path)[len + 1] = 0;
		*cmd_path = ft_strjoin(*cmd_path, cmd, free, 0);
		if (!*cmd_path)
			return (-1);
		if (access(*cmd_path, X_OK) == 0)
			return (FOUND);
		free(*cmd_path);
	}
	*cmd_path = 0;
	return (NOT_FOUND);
}

int	get_cmd(t_cmd *cmd, char *pcmd, char **envp)
{
	const char	*paths = ft_strchr(get_path(envp), '=');
	int			was_found;

	was_found = FOUND;
	free_cmd(cmd);
	cmd->argv = ft_split(pcmd, ' ');
	if (!cmd->argv)
		return (-1);
	if (ft_strchr(pcmd, '/') && access(pcmd, X_OK) == 0)
	{
		cmd->path = ft_strdup(pcmd);
		if (!cmd->path)
			return (free_cmd(cmd), -1);
	}
	else if (paths)
	{
		was_found = get_cmd_path(&cmd->path, cmd->argv[0], (char *)++paths);
		if (was_found < 0)
			return (free_cmd(cmd), -1);
	}
	return (was_found);
}
