/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:38:17 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/28 10:41:43 by joesanto         ###   ########.fr       */
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
char	*get_cmd_path(char *pcmd, char *paths)
{
	char	*path;
	size_t	len;

	while (*paths)
	{
		path = paths + (*paths == ':');
		paths = ft_strchrnul(path, ':');
		len = paths - path;
		if (len <= 0)
			continue ;
		path = ft_strndup(path, len + 1);
		if (!path)
			return (0);
		path[len] = '/';
		path = ft_strjoin(path, pcmd, free, 0);
		if (!path)
			return (0);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (0);
}

int	get_cmd(t_cmd *cmd, char *pcmd, char **envp)
{
	const char	*paths = ft_strchr(get_path(envp), '=');

	free_cmd(cmd);
	cmd->argv = ft_split(pcmd, ' ');
	if (!cmd->argv)
		return (-1);
	cmd->path = 0;
	if (ft_strchr(pcmd, '/') && access(pcmd, X_OK) == 0)
		cmd->path = ft_strdup(pcmd);
	else if (paths)
		cmd->path = get_cmd_path(cmd->argv[0], (char *)++paths);
	if (!cmd->path)
		return (ft_freearray((void **)cmd->argv, free), -1);
	return (0);
}
