/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_configure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:17:57 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/08 14:53:39 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int	ft_configure_philosophers(t_philosophers **ph, char **argv)
{
	*ph = malloc(sizeof(t_philosophers));
	if (!*ph)
		return (0);
	(*ph)->n_p = ft_atoi(argv[1]);
	(*ph)->die_t = ft_atoi(argv[2]);
	(*ph)->eat_t = ft_atoi(argv[3]);
	(*ph)->sleep_t = ft_atoi(argv[4]);
	(*ph)->max_eats = ft_atoi(argv[5]);
	(*ph)->someone_die = 0;
	(*ph)->philos = malloc(sizeof(t_philo) * (*ph)->n_p);
	if (!(*ph)->philos)
		return (free(ph), 0);
	return (1);
}

void	ft_configure_philos(t_philosophers **ph, long time)
{
	int	i;

	i = 0;
	while (i < (*ph)->n_p)
	{
		if (i == 0)
			(*ph)->philos[i].l_fork = &(*ph)->philos[(*ph)->n_p - 1].r_fork;
		else
			(*ph)->philos[i].l_fork = &(*ph)->philos[i - 1].r_fork;
		(*ph)->philos[i].n_p = (*ph)->n_p;
		(*ph)->philos[i].die_t = (*ph)->die_t;
		(*ph)->philos[i].eat_t = (*ph)->eat_t;
		(*ph)->philos[i].sleep_t = (*ph)->sleep_t;
		(*ph)->philos[i].last_eat = time;
		(*ph)->philos[i].max_eats = (*ph)->max_eats;
		//(*ph)->philos[i].someone_die = &(*ph)->someone_die;
		(*ph)->philos[i].someone_die = 0;
		(*ph)->philos[i].i = i + 1;
		if ((*ph)->philos[i].i % 2 == 0)
			(*ph)->philos[i].start_eat = 0;
		else
			(*ph)->philos[i].start_eat = 1;
		pthread_mutex_init(&(*ph)->philos[i].r_fork, 0);
		i++;
	}
}
