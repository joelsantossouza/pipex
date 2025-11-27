/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:53:23 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/27 20:58:00 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	close_pipe(int read_end, int write_end)
{
	const int	ret = close(read_end);

	if (close(write_end) < 0)
		return (-1);
	return (ret);
}
