/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantonio <aantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:25:38 by aantonio          #+#    #+#             */
/*   Updated: 2023/07/15 10:42:34 by aantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[] )
{
	int	server_pid;

	if (argc != 3)
	{
		printf("Only one argument expected!");
		exit(-1);
	}
	server_pid = atoi(argv[1]);
	if (*argv[2] == '1')
		kill(server_pid, SIGUSR1);
	if (*argv[2] == '2')
		kill(server_pid, SIGUSR2);
	printf("%s\n",argv[2]);
	return (0);
}
