/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuster- <vfuster-@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:51:01 by vfuster-          #+#    #+#             */
/*   Updated: 2023/04/17 07:44:43 by vfuster-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/********************************************************************** *
*                                                                       *
* __CHAR_BIT__ : macro definie dans le standard C qui donne le nombre   *
* de bit utilises pour representer un char.                             *
* siginfo_t : utilise pour stocker des infos supp comme numero          *
* de signal...                                                          *
* static char : utilise pour stocker les bits du message recu un par un *
* static int : compteur du nombre de bits restants a recevoir dans le   *
* message                                                               *
* (void)context : instruction vide qui force le compilateur a           *
* considerer la variable comme utilisee pour eviter un avertissement    *
* de compilation.                                                       *
*                                                                       *	
*********************************************************************** */

void	sig_usr(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit = -1;

	(void)context;
	if (kill(info->si_pid, 0) < 0)
	{
		ft_printf("ERROR : cant send signal to PID : %d\n", info->si_pid);
		exit(EXIT_FAILURE);
	}
	if (bit < 0 && !c)
		ft_printf("\nClient say : ");
	if (bit < 0)
		bit = __CHAR_BIT__ * sizeof(c) - 1;
	if (sig == SIGUSR1)
		c |= 1 << bit;
	else if (sig == SIGUSR2)
		c &= ~(1 << bit);
	if (!bit && c)
		ft_putchar_fd(c, 1);
	else if (!bit && !c)
		kill(info->si_pid, SIGUSR2);
	bit--;
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	init_sig(SIGUSR1, &sig_usr);
	init_sig(SIGUSR2, &sig_usr);
	ft_printf("PID : %d", getpid());
	while (1)
		sleep(1);
}
