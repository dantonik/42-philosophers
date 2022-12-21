/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:15:39 by dantonik          #+#    #+#             */
/*   Updated: 2022/12/21 13:42:38 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	done(t_args *args)
{
	int	alive;

	alive = 1;
	pthread_mutex_lock(&args->check_mutex[args->pid]);
	if (*args->alive == 0)
		alive = 0;
	pthread_mutex_unlock(&args->check_mutex[args->pid]);
	return (alive);
}

int	ft_print(t_args *args, int msg)
{
	static pthread_mutex_t	print = PTHREAD_MUTEX_INITIALIZER;
	static int dead = 0;

	// if ((msg != P_DEAD && done(args) == 0))
	// 	return (1);
	// if (msg == P_DEAD)
	// 	ft_sleep((unsigned long)args->time_to_die - (get_time() - args->last_meal));
	pthread_mutex_lock(&print);
	if (dead == 0)
	{
		if (msg == P_DEAD)
		{
			printf("%d %d %sdied%s\n", \
			(int)(get_time() - args->start_time), (args)->pid + 1, RED, RESET);
			dead = 1;
		}
		else
		{
			printf("%d %d ", (int)(get_time() - args->start_time), args->pid + 1);
			if (msg == P_EAT)
				printf("%sis eating%s\n", CYAN, RESET);
			else if (msg == P_THINK)
				printf("is thinking\n");
			else if (msg == P_SLEEP)
				printf("is sleeping\n");
			else if (msg == P_FORK)
				printf("has taken a fork\n");
		}
	}
	pthread_mutex_unlock(&print);
	return (0);
}
