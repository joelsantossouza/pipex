/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:38:17 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/28 16:04:50 by joesanto         ###   ########.fr       */
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
			return (0);
		free(*cmd_path);
	}
	*cmd_path = 0;
	return (0);
}

int	get_cmd(t_cmd *cmd, char *pcmd, char **envp)
{
	const char	*paths = ft_strchr(get_path(envp), '=');

	cmd->argv = ft_split(pcmd, ' ');
	if (!cmd->argv)
		return (-1);
	cmd->path = 0;
	if (ft_strchr(pcmd, '/') && access(pcmd, X_OK) == 0)
	{
		cmd->path = ft_strdup(pcmd);
		if (!cmd->path)
			return (free_cmd(cmd), -1);
	}
	else if (paths)
	{
		if (get_cmd_path(&cmd->path, cmd->argv[0], (char *)++paths) < 0)
			return (free_cmd(cmd), -1);
	}
	return (0);
}
