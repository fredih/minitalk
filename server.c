/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantonio <aantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:33:50 by aantonio          #+#    #+#             */
/*   Updated: 2023/08/11 18:41:20 by aantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*	g_text;

size_t	print_free_and_kill(size_t text_index, siginfo_t *info)
{
	write(1, g_text, text_index + 1);
	write(1, "\n", 1);
	free(g_text);
	kill(info->si_pid, SIGUSR2);
	text_index = 0;
}

void	handler(int signum, siginfo_t *info, void *ucontext)
{
	static unsigned char	bit = 128;
	char					*tmp;
	static size_t			text_index = 0;

	if (text_index == 0 && bit == 128)
	{
		g_text = ft_calloc(sizeof(char), 1);
	}
	if (bit == 0)
	{
		bit = 128;
		if (g_text[text_index] == '\0')
		{
			text_index = print_free_and_kill(text_index, info);
			return ;
		}
		text_index++;
		tmp = g_text;
		g_text = malloc(sizeof(char)*(text_index + 1));
		g_text[text_index] = 0;
		strncpy(g_text, tmp, text_index);
		free(tmp);
	}
	if (signum == SIGUSR1)
		g_text[text_index] = g_text[text_index] | bit;
	bit = bit >> 1;
}

void	set_signals(void (*hndlr)(int, siginfo_t*, void*), struct sigaction sa)
{
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = hndlr;
	sa.sa_flags = SA_NODEFER | SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(void)
{
	int					server_pid;
	struct sigaction	sa;

	server_pid = getpid();
	set_signals(handler, sa);
	printf("Server PID: %d\n", server_pid);
	while (1)
		pause();
	return (0);
}
