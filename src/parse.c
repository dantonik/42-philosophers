/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:26:23 by dantonik          #+#    #+#             */
/*   Updated: 2022/12/27 14:16:50 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	parse_inner_loop(char **av, int ac, t_args *data, int i)
{
	if (ac == 6)
		data->meals_to_finish[i] = ft_atoi(av[4]);
	else
		data->meals_to_finish[i] = -1;
	data->alive[i] = 1;
	data->last_meal[i] = data->start_time;
	pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->check_mutex[i], NULL);
}

void	parse_data(char **av, int ac, t_args *data)
{
	int	i;

	data->n_philos = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	data->forks = (pthread_mutex_t *)malloc(data->n_philos * \
	sizeof(pthread_mutex_t));
	data->check_mutex = (pthread_mutex_t *)malloc(data->n_philos * \
	sizeof(pthread_mutex_t));
	data->meals_to_finish = (int *)malloc(data->n_philos * sizeof(int));
	data->alive = (int *)malloc(data->n_philos * sizeof(int));
	data->last_meal = (size_t *)malloc(data->n_philos * sizeof(size_t));
	i = -1;
	data->start_time = get_time();
	while (++i < data->n_philos)
		parse_inner_loop(av, ac, data, i);
}
