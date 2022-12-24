/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:10:15 by dantonik          #+#    #+#             */
/*   Updated: 2022/12/24 05:35:54 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *args)
{
	t_args	*pargs;

	pargs = (t_args *)args;
	pthread_mutex_lock(&pargs->check_mutex[pargs->pid]);
	pargs->last_meal[pargs->pid] = pargs->start_time;
	pthread_mutex_unlock(&pargs->check_mutex[pargs->pid]);
	ft_print(pargs, P_THINK);
	if (pargs->pid % 2 == 0)
		ft_sleep(pargs->time_to_eat);
	while (pargs->alive[pargs->pid] == 1)
	{
		usleep(200);
		pthread_mutex_lock(&pargs->forks[pargs->first_fork]);
		ft_print(pargs, P_FORK);
		pthread_mutex_lock(&pargs->forks[pargs->second_fork]);
		ft_print(pargs, P_FORK);
		ft_print(pargs, P_EAT);
		pthread_mutex_lock(&pargs->check_mutex[pargs->pid]);
		pargs->last_meal[pargs->pid] = get_time();
		if (pargs->meals_to_finish[pargs->pid] > 0)
			pargs->meals_to_finish[pargs->pid]--;
		pthread_mutex_unlock(&pargs->check_mutex[pargs->pid]);
		ft_sleep(pargs->time_to_eat);
		pthread_mutex_unlock(&pargs->forks[pargs->second_fork]);
		pthread_mutex_unlock(&pargs->forks[pargs->first_fork]);
		ft_print(pargs, P_SLEEP);
		ft_sleep(pargs->time_to_sleep);
		ft_print(pargs, P_THINK);
	}
	return (NULL);
}
