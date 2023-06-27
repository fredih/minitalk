/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantonio <aantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:25:38 by aantonio          #+#    #+#             */
/*   Updated: 2023/06/27 13:40:54 by aantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[] )
{
	int	server_pid;

	if (argc > 2)
	{
		printf("One argument expected!");
	}
	server_pid = atoi(argv[1]);
	kill(server_pid, SIGUSR1);
	return (0);
}
