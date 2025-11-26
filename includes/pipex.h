/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:13:03 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/26 20:25:28 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

typedef struct s_cmd
{
	char	*path;
	char	**argv;
	char	**envp;
}	t_cmd;

// EXEC
int	execve_pipe(t_cmd *cmd, int read_end, int write_end);

#endif
