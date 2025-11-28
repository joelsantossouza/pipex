/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:13:03 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/28 16:15:46 by joesanto         ###   ########.fr       */
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
int		exec_pipe(char *pcmd, char **envp, int read_end, int write_end);
int		exec_pipe_chain(size_t size, char **cmds, char **envp, int end[2]);

// GET
int		get_cmd(t_cmd *cmd, char *pcmd, char **envp);

// FREES AND CLOSES
void	free_cmd(t_cmd *cmd);
int		close_pipe(int read_end, int write_end);

#endif
