/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:13:03 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/29 13:43:53 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>

typedef struct s_cmd
{
	char	*path;
	char	**argv;
}	t_cmd;

// EXEC
int		exec_pipe(char *pcmd, char **envp, int pipe1[2], int pipe2[2]);
int		exec_pipe_chain(size_t size, char **cmds, char **envp, int end[2]);

// GET
int		cmd_not_found(const char *pcmd);
int		get_cmd(t_cmd *cmd, char *pcmd, char **envp);

// FREES AND CLOSES
void	free_cmd(t_cmd *cmd);
int		safe_close(int *fd);
int		close_pipe(int fd[2]);

#endif
