/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:49:01 by alvalope          #+#    #+#             */
/*   Updated: 2023/06/14 14:31:04 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sum;
	int	neg;

	i = 0;
	neg = 1;
	sum = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = sum * 10 + (str[i] - 48);
		i++;
	}
	return (sum * neg);
}

long	ft_get_time(int start)
{
	static struct timeval	t0;
	struct timeval			tm;

	if (start)
		gettimeofday(&t0, 0);
	gettimeofday(&tm, 0);
	return ((tm.tv_sec - t0.tv_sec) * 1000 + (tm.tv_usec - t0.tv_usec) / 1000);
}

void	ft_free_philos(t_philosophers *philos)
{
	free(philos->philos);
	free(philos);
}
