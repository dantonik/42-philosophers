/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:10:15 by dantonik          #+#    #+#             */
/*   Updated: 2022/12/27 14:21:52 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_alive(t_args	*pargs, int i)
{
	int	alive;

	pthread_mutex_lock(pargs->check_mutex);
	alive = *pargs->alive;
	pthread_mutex_unlock(pargs->check_mutex);
	return (alive);
}

static void	routine_loop(t_args *pargs)
{
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
	while (is_alive(pargs, pargs->pid) == 1)
	{
		if (pargs->pid % 2 == 0)
			usleep(1000);
		routine_loop(pargs);
	}
	return (NULL);
}
