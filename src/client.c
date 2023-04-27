/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuster- <vfuster-@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:50:42 by vfuster-          #+#    #+#             */
/*   Updated: 2023/04/14 07:31:01 by vfuster-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// variable globale utilisee pour controler la transmission des donnees.
// initialisee a 0 avant l'envoi de chaque bit et mise a 1 dans sig_usr
// lorsqu'un signal SIGUSR1 est recu pour dire que le bit est bien transmis
int	g_bit_control;

void send_char(char c, pid_t pid)
{
    int bit;

    // Détermine le nombre de bits dans le type de données utilisé pour stocker un caractère
    bit = __CHAR_BIT__ * sizeof(c) - 1;

    // Pour chaque bit dans le caractère, envoie un signal SIGUSR1 ou SIGUSR2 au processus spécifié
    while (bit >= 0)
    {
        // Vérifie si le processus spécifié existe avant d'envoyer un signal
        if (kill(pid, 0) < 0)
        {
            ft_printf("ERROR : cant send sig to pid : %d\n", pid);
            exit(EXIT_FAILURE);
        }

        // Réinitialise le contrôle de bits avant d'envoyer le signal
        g_bit_control = 0;

        // Envoie un signal SIGUSR1 ou SIGUSR2 en fonction de la valeur du bit actuel
        if (c & (1 << bit))
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);

        // Passe au bit suivant
        bit--;

        // Attends que le contrôle de bits soit mis à jour par le gestionnaire de signal
        while (g_bit_control != 1)
            usleep(10);
    }
}


void send_str(char *str, pid_t pid)
{
    int cur;

    cur = 0;
    while (str[cur])
    {
        // Envoyer le caractère à l'indice cur à l'aide de la fonction send_char
        send_char(str[cur], pid);
        cur++;
    }

    // Envoyer un caractère nul pour indiquer la fin de la chaîne
    send_char(0, pid);
}


void sig_usr(int sig)
{
    // Si le signal reçu est SIGUSR1
    if (sig == SIGUSR1) 
    {
        // Définir la variable globale g_bit_control à 1 pour indiquer que le bit a été reçu
        g_bit_control = 1; 
    }
    // Si le signal reçu est SIGUSR2
    else if (sig == SIGUSR2) 
    {
        // Afficher un message pour indiquer que le message a été reçu, puis quitter avec un code de succès
        ft_printf("Message received !\n");
        exit(EXIT_SUCCESS);
    }
}


int main(int ac, char **av)
{
    pid_t pid;

    // Vérifier le nombre d'arguments et afficher un message d'erreur si nécessaire
    if (ac != 3)
    {
        ft_printf("Usage : ./client <pid> <string to send>\n");
        exit(EXIT_FAILURE);
    }

    // Définir les gestionnaires de signal pour SIGUSR1 et SIGUSR2 sur la fonction sig_usr
    signal(SIGUSR1, &sig_usr);
    signal(SIGUSR2, &sig_usr);

    // Convertir l'argument pid en entier
    pid = ft_atoi(av[1]);

    // Vérifier si le pid est valide
    if (!pid)
    {
        ft_printf("%s is an invalid pid\n", av[1]);
        exit(EXIT_FAILURE);
    }

    // Envoyer la chaîne de caractères à travers le processus spécifié
    send_str(av[2], pid);

    // Attendre indéfiniment
    while (1)
        sleep(1);
}

