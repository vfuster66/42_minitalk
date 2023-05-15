/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuster- <vfuster-@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 07:44:40 by vfuster-          #+#    #+#             */
/*   Updated: 2023/04/14 11:54:32 by vfuster-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* cette fonction est utilisée pour initialiser un gestionnaire de signal
* pour le signal SIGUSR1 ou SIGUSR2 avec les options spécifiées dans la
* structure susr. Le pointeur de fonction handler sera appelé lorsque le
* signal est reçu, avec des informations supplémentaires telles que le numéro
* du signal et des infos sur l'état de la machine lorsqu'il a été reçu.*/

void	init_sig(int sig, void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	susr;

	susr.sa_sigaction = handler;
	susr.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	sigemptyset(&susr.sa_mask);
	if (sig == SIGUSR1)
		sigaction(SIGUSR1, &susr, 0);
	else if (sig == SIGUSR2)
		sigaction(SIGUSR2, &susr, 0);
}
