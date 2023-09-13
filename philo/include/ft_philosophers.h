/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:34:16 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/08 14:16:56 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILOSOPHERS_H
# define FT_PHILOSOPHERS_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thr;
	int				i;
	int				n_p;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	int				max_eats;
	int				n_eats;
	long			last_eat;
	long			death_time;
	int				start_eat;
	int				someone_die;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_philosophers
{
	t_philo	*philos;
	int		i;
	int		n_p;
	int		someone_die;
	int		die_t;
	int		eat_t;
	int		sleep_t;
	int		max_eats;
}	t_philosophers;

int		ft_atoi(const char *str);
long	ft_get_time(int start);
void	ft_free_philos(t_philosophers *philos);

int		ft_configure_philosophers(t_philosophers **ph, char **argv);
void	ft_configure_philos(t_philosophers **ph, long time);

int		main(int argc, char *argv[]);

#endif