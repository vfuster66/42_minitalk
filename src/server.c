/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuster- <vfuster-@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:51:01 by vfuster-          #+#    #+#             */
/*   Updated: 2023/04/14 08:01:19 by vfuster-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*****************************************************************************
*                                                                            *
* __CHAR_BIT__ : macro definie dans le standard C qui donne le nombre de bits*
* utilises pour representer un char.                                         *
* siginfo_t : utilise pour stocker des infos supp comme numero de signal...  *
* 

******************************************************************************/

void	sig_usr(int sig, siginfo_t *info, void *context)
{
	// variables statiques conservent leur valeur entre les appels de la fonction
	static char	c = 0;  // stocke le caractère en cours de réception
	static int	bit = -1;  // stocke le bit en cours de réception

	// évite un avertissement de compilation sur l'argument non utilisé
	(void)context;

	// vérifie si le PID est valide et accessible
	if (kill(info->si_pid, 0) < 0)
	{
		ft_printf("ERROR : cant send signal to PID : %d\n", info->si_pid);
		exit(EXIT_FAILURE);
	}

	// si le bit et le caractère sont à -1 (valeur initiale), alors affiche un message pour dire que le client envoie un message
	if (bit < 0 && !c)
		ft_printf("\nClient say : ");

	// si bit est à -1 (c'est-à-dire que nous commençons un nouveau caractère), alors nous fixons bit à la position du bit le plus significatif
	if (bit < 0)
		bit = __CHAR_BIT__ * sizeof(c) - 1;

	// si le signal reçu est SIGUSR1, définissez le bit à 1 dans le caractère en cours de réception
	if (sig == SIGUSR1)
		c |= 1 << bit;
	// sinon, définissez le bit à 0 dans le caractère en cours de réception
	else if (sig == SIGUSR2)
		c &= ~(1 << bit);

	// si nous avons terminé de recevoir les bits pour un caractère et que ce caractère est valide (non nul), affichez-le
	if (!bit && c)
		ft_putchar_fd(c, 1);
	// sinon, si nous avons terminé de recevoir les bits pour un caractère et que ce caractère est nul, nous signalons la fin de la transmission au client en envoyant un signal SIGUSR2
	else if (!bit && !c)
		kill(info->si_pid, SIGUSR2);

	// décrémenter bit pour passer au prochain bit
	bit--;

	// signaler au client que nous sommes prêts à recevoir le prochain bit
	kill(info->si_pid, SIGUSR1);
}


int	main(void)
{
	// On initialise la gestion des signaux pour les signaux SIGUSR1 et SIGUSR2
	init_sig(SIGUSR1, &sig_usr);
	init_sig(SIGUSR2, &sig_usr);

	// On affiche le PID du processus en cours d'exécution
	ft_printf("PID : %d", getpid());

	// Boucle infinie pour que le processus ne se termine pas
	while (1)
		sleep(1);
}
