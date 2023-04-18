/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuster- <vfuster-@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 07:44:40 by vfuster-          #+#    #+#             */
/*   Updated: 2023/04/14 07:48:31 by vfuster-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* cette fonction est utilisée pour initialiser un gestionnaire de signal
* pour le signal SIGUSR1 ou SIGUSR2 avec les options spécifiées dans la
* structure susr. Le pointeur de fonction handler sera appelé lorsque le
* signal est reçu, avec des informations supplémentaires telles que le numéro
* du signal et des informations sur l'état de la machine lorsqu'il a été reçu.*/

void	init_sig(int sig, void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	sig_action;

// pointeur sur fonction handler au champ sa_sigaction de la structure
	sig_action.sa_sigaction = handler;
// SA_SIGINFO: pointeur sur structure siginfo_t
// SA_RESTART: appels systemes interrompus par signal redemarres automatiquement
// SA_NODEFER: signal recu non masque pendant l'execution
	sig_action.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
// initialise le masque des signaux bloques a un masque vide. Tous les signaux
// seront autorises pendant l'execution du programme
	sigemptyset(&sig_action.sa_mask);
// configure la gestion des signaux en fonction de sig. sigaction appele avec le
// numero de signal correspondant et un pointeur vers susr.
	if (sig == SIGUSR1)
		sigaction(SIGUSR1, &sig_action, 0);
	else if (sig == SIGUSR2)
		sigaction(SIGUSR2, &sig_action, 0);
}
