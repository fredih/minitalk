/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantonio <aantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:33:50 by aantonio          #+#    #+#             */
/*   Updated: 2023/07/15 12:59:52 by aantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 

char*	g_text;

void	handler(int signum, siginfo_t *info, void *ucontext)
{
	static unsigned char	bit = 128;
	static int				bit_counter = 0;
	char					*tmp;
	static size_t			text_index = 0;

	if (bit_counter == 8)
	{
		if (g_text[text_index] == '\0')
		{
			write(1, "\n", 1);
			write(1, g_text, text_index + 1);
			write(1, "\n", 1);
			free(g_text);
			exit(0);
		}
		else
		{
			text_index++;
			tmp = g_text;
			g_text = malloc(sizeof(char)*text_index + 1);
			strncpy(g_text, tmp, text_index);
			free(tmp);
			bit = 128;
			bit_counter = 0;
		}
	}
	if (signum == SIGUSR1)
	{
		g_text[text_index] = g_text[text_index] | bit;
		write(1, "Received SIGUSR1!", 18);
		write(1, "\n", 1);
		// counterw = bit;
		// printf("\n"BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(bit));
		// write(1, g_text, 2);
		write(1, "\n", 1);
		bit = bit >> 1;
		bit_counter++;
		// counterw++;
		pause();
	}
	if (signum == SIGUSR2)
	{
		// printf("\n"BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(bit));
		write(1, "Received SIGUSR2!", 18);
		write(1, "\n", 1);
		// write(1, g_text, 2);

		// counterw = bit;
		// write(1, &(counterw), 1);
		write(1, "\n", 1);
		bit = bit >> 1;
		bit_counter++;
		// counterw++;
		pause();
	}
	write(2, "Error! Must use SIGUSR1 or SIGUSR2!\n", 37);
}

void	set_signals(void (*hndlr)(int, siginfo_t*, void*), struct sigaction sa)
{
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = hndlr;
	sa.sa_flags = SA_NODEFER;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(void)
{
	int					server_pid;
	struct sigaction	sa;

	g_text = malloc(sizeof(char)*1);
	g_text[0] = '\0';
	server_pid = getpid();
	set_signals(handler, sa);
	printf("Server PID: %d\n", server_pid);
	pause();
	free(g_text);
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
