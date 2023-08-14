/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantonio <aantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:25:38 by aantonio          #+#    #+#             */
/*   Updated: 2023/08/12 15:51:34 by aantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	send_char(char c, int server_pid)
{
	unsigned char	bitmask;

	bitmask = 128;
	while (bitmask != 0)
	{
		usleep(1000);
		if (bitmask & c)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		bitmask = bitmask >> 1;
	}
}

int	main(int argc, char *argv[] )
{
	int		server_pid;
	size_t	str_index;

	server_pid = atoi(argv[1]);
	if (argc != 3)
	{
		write(2, "Error: Only two arguments are expected!", 40);
		exit(EXIT_FAILURE);
	}
	str_index = 0;
	while (argv[2][str_index] != '\0')
	{
		send_char(argv[2][str_index], server_pid);
		str_index++;
	}
	send_char('\0', server_pid);
	// usleep(1000);
	kill(server_pid, SIGUSR1);
	// pause();
	return (0);
}
