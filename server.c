/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantonio <aantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:33:50 by aantonio          #+#    #+#             */
/*   Updated: 2023/06/27 13:38:39 by aantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void	my_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		printf("Received SIGUSR1!\n");
	}
}

int	main(void)
{
	int	server_pid;

	server_pid = getpid();
	printf("Server PID: %d\n", server_pid);
	pause();
	signal(SIGUSR1, my_handler);
	return (0);
}
