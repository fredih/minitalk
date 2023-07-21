/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantonio <aantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:25:38 by aantonio          #+#    #+#             */
/*   Updated: 2023/07/21 10:02:22 by aantonio         ###   ########.fr       */
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
		{
			kill(server_pid, SIGUSR1);
			write(1, "1", 1);
		}
		else
		{
			kill(server_pid, SIGUSR2);
			write(1, "0", 1);
		}
		bitmask = bitmask >> 1;
	}
	write(1, "\n", 1);
}

int	main(int argc, char *argv[] )
{
	int		server_pid;
	size_t	str_index;

	server_pid = atoi(argv[1]);
	if (argc != 3)
	{
		write(2,"Error: Only two arguments are expected!", 40);
		exit(EXIT_FAILURE);
	}
	str_index = 0;
	while (argv[2][str_index] != '\0')
	{
		send_char(argv[2][str_index], server_pid);
		str_index++;
	}
	send_char('\0', server_pid);
	usleep(1000);
	kill(server_pid, SIGUSR1);
	// if (*argv[2] == '1')
	// 	kill(server_pid, SIGUSR1);
	// if (*argv[2] == '2')
	// 	kill(server_pid, SIGUSR2);
	// printf("%s\n",argv[2]);
	return (0);
}
