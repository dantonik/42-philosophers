/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:10:15 by dantonik          #+#    #+#             */
/*   Updated: 2022/12/20 16:09:39 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *args)
{
	t_args	*pargs;

	pargs = (t_args *)args;
	pargs->start_time = get_time();
	pargs->last_meal = pargs->start_time;
	while (1)
	{
		// printf("%zu, %i\n", get_time() - pargs->last_meal, pargs->time_to_die);
		if (get_time() - pargs->last_meal > (unsigned long)pargs->time_to_die)
		{
			pthread_mutex_lock(&pargs->check_mutex[pargs->pid]);
			pargs->alive = 0;
			pthread_mutex_unlock(&pargs->check_mutex[pargs->pid]);
			ft_print(pargs, P_DEAD);
			return (NULL);
		}
		pthread_mutex_lock(&pargs->forks[pargs->first_fork]);
		ft_print(pargs, P_FORK);
		pthread_mutex_lock(&pargs->forks[pargs->second_fork]);
		ft_print(pargs, P_FORK);
		ft_print(pargs, P_EAT);
		pargs->last_meal = get_time();
		ft_sleep(pargs->time_to_eat);
		pthread_mutex_unlock(&pargs->forks[pargs->second_fork]);
		pthread_mutex_unlock(&pargs->forks[pargs->first_fork]);
		ft_print(pargs, P_SLEEP);
		ft_sleep(pargs->time_to_sleep);
		ft_print(pargs, P_THINK);
	}
}