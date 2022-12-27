/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:15:39 by dantonik          #+#    #+#             */
/*   Updated: 2022/12/27 12:55:42 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// int	done(t_args *args)
// {
// 	int	alive;

// 	alive = 1;
// 	pthread_mutex_lock(&args->check_mutex[args->pid]);
// 	if (*args->alive == 0)
// 		alive = 0;
// 	pthread_mutex_unlock(&args->check_mutex[args->pid]);
// 	return (alive);
// }

int	ft_print(t_args *args, int msg)
{
	static pthread_mutex_t	print = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&print);
	if (msg == P_DEAD || is_alive(args, args->pid))
	{
		printf("%d %d ", (int)(get_time() - args->start_time), \
		args->pid + 1);
		if (msg == P_EAT)
			printf("is eating\n");
		else if (msg == P_THINK)
			printf("is thinking\n");
		else if (msg == P_SLEEP)
			printf("is sleeping\n");
		else if (msg == P_FORK)
			printf("has taken a fork\n");
		else if (msg == P_DEAD)
			printf("died\n");
	}
	pthread_mutex_unlock(&print);
	return (0);
}
