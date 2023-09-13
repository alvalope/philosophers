/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:33:33 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/24 12:22:47 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void	ft_leaks(void)
{
	system("leaks -q a.out");
}

int	ft_check_alive(t_philo *philo, long time, int eating)
{
	time = ft_get_time(0);
	if (time - philo->last_eat > philo->die_t)
	{
		philo->death_time = time;
		if (eating)
		{
			pthread_mutex_unlock(&philo->r_fork);
			pthread_mutex_unlock(&*philo->l_fork);
		}
		philo->someone_die = 1;
		return (0);
	}
	return (1);
}

void	ft_usleep(int action_time, long start)
{
	long	time;

	time = ft_get_time(0);
	while (start + action_time >= time)
	{
		usleep(10);
		time = ft_get_time(0);
	}
}

int	ft_eat(t_philo *philo)
{
	long	time;

	if (!philo->start_eat)
		usleep(100);
	time = ft_get_time(0);
	if (!ft_check_alive(philo, time, 0))
	{
		philo->someone_die = 1;
		return (0);
	}
	if (pthread_mutex_lock(&philo->r_fork) == 0
		&& pthread_mutex_lock(&*philo->l_fork) == 0)
	{
		time = ft_get_time(0);
		if (!ft_check_alive(philo, time, 1))
		{
			philo->someone_die = 1;
			return (0);
		}
		philo->last_eat = time;
		printf("%05ld %d has taken a fork\n", time, philo->i);
		printf("%05ld %d is eating\n", time, philo->i);
		if (philo->max_eats != -1)
			philo->n_eats += 1;
		time = ft_get_time(0);
		ft_usleep(philo->eat_t, time);
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(&*philo->l_fork);
	}
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	long	time;

	time = ft_get_time(0);
	if (time - philo->last_eat + philo->sleep_t > philo->die_t)
	{
		printf("%05ld %d is sleeping\n", time, philo->i);
		ft_usleep(philo->die_t - philo->eat_t, time);
		time = ft_get_time(0);
		philo->death_time = time;
		philo->someone_die = 1;
		return (0);
	}
	else if (!philo->someone_die)
	{
		printf("%05ld %d is sleeping\n", time, philo->i);
		ft_usleep(philo->sleep_t, time);
	}
	return (1);
}

int	ft_think(t_philo *philo)
{
	long	time;

	time = ft_get_time(0);
	printf("%05ld %d is thinking\n", time, philo->i);
	if (!ft_check_alive(philo, time, 0))
		return (0);
	return (1);
}

void	*ft_take_seat(void	*ph)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)ph;
	usleep(50);
	while (!philo->someone_die)
	{
		if (philo->n_p == 1)
		{
			usleep(philo->die_t * 1000);
			time = ft_get_time(0);
			philo->death_time = time;
			philo->someone_die = 1;
			break ;
		}
		if (!ft_eat(philo))
			break ;
		if (!ft_sleep(philo))
			break ;
		if (!ft_think(philo))
			break ;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int				i;
	t_philosophers	*ph;
	long			time;
	int				exit;
	int				feed;

	argc = 5;
	argv[1] = "4";
	argv[2] = "310";
	argv[3] = "200";
	argv[4] = "100";
	argv[5] = "7";
	//atexit(ft_leaks);
	if (argc == 5 || argc == 6)
	{	
		if (argc == 5)
			argv[5] = "-1";
		time = ft_get_time(1);
		if (!ft_configure_philosophers(&ph, argv))
			return (0);
		ft_configure_philos(&ph, time);
		i = 0;
		while (i < ph->n_p)
		{
			pthread_create(&ph->philos[i].thr, 0, ft_take_seat, &ph->philos[i]);
			usleep(50);
			i++;
		}
		/*i = -1;
		while (++i < ph->n_p)
			pthread_join(ph->philos[i].thr, 0);*/
		exit = 0;
		while (1)
		{
			i = 0;
			//usleep(1000);
			feed = 0;
			while (i < ph->n_p)
			{
				if (ph->max_eats != -1 && ph->philos[i].n_eats >= ph->max_eats)
					feed++;
				if (feed == ph->n_p)
				{
					exit = 1;
					printf("ALL FEEDED");
					break ;
				}
				if (ph->philos[i].someone_die)
				{
					time = ft_get_time(0);
					printf("%05ld %ld %d died\n", time, ph->philos[i].death_time, ph->philos[i].i);
					exit = 1;
					i = 0;
					while (i < ph->n_p)
					{
						ph->philos[i].someone_die = 1;
						//pthread_detach(ph->philos[i].thr);
						i++;
					}
					break ;
				}
				i++;
			}
			if (exit == 1)
				break ;
		}
		ft_free_philos(ph);
	}
	return (0);
}
