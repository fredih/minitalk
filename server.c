/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantonio <aantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:33:50 by aantonio          #+#    #+#             */
/*   Updated: 2023/07/14 17:52:44 by aantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void	my_handler(int signum)
{
	
		write(1, "Received signal signal()!\n", 27);
	if (signum == SIGUSR1)
	{
		write(1, "Received SIGUSR1!\n", 19);
		exit(0);
	}
}


void	handler(int signum, siginfo_t *info, void *ucontext)
{
	// write(1, "Received signal sigaction()!\n", 30);
	if (signum == SIGUSR1)
	{
		write(1, "Received SIGUSR1!\n", 19);
		struct sigaction	sa;

		// text = malloc(1);
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = handler;
		sa.sa_flags = SA_NODEFER|SA_RESETHAND;
		sigaction(SIGUSR1, &sa, NULL);
		pause();
		// text
	}
}

// char*	text;

int	main(void)
{
	int					server_pid;
	struct sigaction	sa;

	// text = malloc(1);
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = SA_NODEFER|SA_RESETHAND;
	server_pid = getpid();
	printf("Server PID: %d\n", server_pid);
	sigaction(SIGUSR1, &sa, NULL);
	// if (not finished text)
		pause();
	// write(text)

	// while (1)
	// {
	// 	sigaction(SIGUSR1, &new_action, NULL);
	// 	sleep();
	// }
	// free(text);
	return (0);
}


// int	main(void)
// {
// 	int	server_pid;
// 	struct sigaction new_action;

// 	new_action.sa_handler = handler;
// 	server_pid = getpid();
// 	printf("Server PID: %d\n", server_pid);
// 	sigaction (SIGUSR1, &new_action, NULL);
// 	// while(1)
// 	// 	continue;
// 	// signal(SIGUSR1, my_handler);
// 	pause();
// 	return (0);
// }
