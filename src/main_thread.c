/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:11:40 by dantonik          #+#    #+#             */
/*   Updated: 2022/12/23 08:33:02 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	kill_all(t_args *check_args, int i)
{
	ft_print(&check_args->args[i], P_DEAD);
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

static void	all_full(t_args *check_args)
{
	int	i;

	ft_print(&check_args->args[0], P_FULL);
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

	check_args->finished = 0;
	usleep(check_args->time_to_die);
	while (1)
	{
		i = -1;
		while (++i < check_args->n_philos)
		{
			pthread_mutex_lock(&check_args->check_mutex[i]);
			if ((get_time() - check_args->last_meal[i]) >= \
			(unsigned long)check_args->time_to_die)
				return (kill_all(check_args, i));
			// else if (check_args->alive[i] == 0)
			// 	return (kill_all(check_args, i));
			if (check_args->meals_to_finish[i] == 0)
				check_args->finished++;
			pthread_mutex_unlock(&check_args->check_mutex[i]);
		}
		if (check_args->finished == check_args->n_philos)
			return (all_full(check_args));
		check_args->finished = 0;
		usleep(1000 * 1);
	}
}
