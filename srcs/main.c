/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:23:39 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/27 21:04:34 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	//if (argc < 5)
	//{
	//	ft_fprintf(2, "Usage: %s <file1> <cmd1> <cmd2> <file2>\n", *argv);
	//	return (1);
	//}
	if (argc < 3)
		return (1);
	exec_pipe_chain(argc - 1, argv + 1, envp, (int [2]){0, 1});
	return (0);
}
