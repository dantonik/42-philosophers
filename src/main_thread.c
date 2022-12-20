/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:11:40 by dantonik          #+#    #+#             */
/*   Updated: 2022/12/20 15:52:46 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	kill_all(t_args *check_args, int i)
{
	check_args->alive[i] = 0;
	pthread_mutex_unlock(&check_args->check_mutex[i]);
	i = -1;
	while (++i < check_args->n_philos)
	{
		pthread_mutex_lock(&check_args->check_mutex[i]);
		check_args->alive[i] = 0;
		pthread_mutex_unlock(&check_args->check_mutex[i]);
	}
}

void	check_death(t_args *check_args)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i > check_args->n_philos)
		{
			pthread_mutex_lock(&check_args->check_mutex[i]);
			if (!check_args->alive[i])
				return (kill_all(check_args, i));
			if (check_args->meals_to_finish[i] == 0)
				check_args->finished++;
			if (check_args->finished == check_args->n_philos)
				return (kill_all(check_args, i));
			pthread_mutex_unlock(&check_args->check_mutex[i]);
			check_args->finished = 0;
			usleep(50);
		}
		usleep(500);
	}
}
