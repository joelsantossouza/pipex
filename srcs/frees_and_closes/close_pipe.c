/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:53:23 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/29 20:39:45 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	close_pipe(int fd[2])
{
	const int	read_end = fd[0];
	const int	write_end = fd[1];
	int			ret;

	ret = 0;
	if (read_end > 2)
		ret = close(read_end);
	if (write_end > 2 && close(write_end) < 0)
		return (-1);
	return (ret);
}
