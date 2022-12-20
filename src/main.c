/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:19:35 by dantonik          #+#    #+#             */
/*   Updated: 2022/12/20 16:37:02 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_values(t_args args)
{
	if (args.time_to_die < MIN_TIME || args.time_to_eat < \
	MIN_TIME || args.time_to_sleep < MIN_TIME)
		return (1);
	return (0);
}

void	init_thread_args(t_args args, t_args *thread_args, \
t_args *check_thread_args)
{
	int	i;

	i = -1;
	check_thread_args->n_philos = args.n_philos;
	check_thread_args->alive = args.alive;
	check_thread_args->check_mutex = args.check_mutex;
	check_thread_args->finished = 0;
	while (++i < args.n_philos)
	{
		if (i % 2 == 0)
		{
			thread_args[i].first_fork = i;
			thread_args[i].second_fork = (i + 1) % args.n_philos;
		}
		else
		{
			thread_args[i].first_fork = (i + 1) % args.n_philos;
			thread_args[i].second_fork = i;
		}
		thread_args[i].pid = i;
		thread_args[i].n_philos = args.n_philos;
		thread_args[i].time_to_eat = args.time_to_eat;
		thread_args[i].time_to_die = args.time_to_die;
		thread_args[i].time_to_sleep = args.time_to_sleep;
		thread_args[i].alive = args.alive;
		thread_args[i].meals_to_finish = args.meals_to_finish;
		thread_args[i].forks = args.forks;
		thread_args[i].check_mutex = args.check_mutex;
	}
}

int	main(int argc, char *argv[])
{
	t_args		args;
	t_args		*thread_args;
	t_args		check_thread_args;
	pthread_t	*threads;
	int			i;

	if (argc < 5 || argc > 6)
		return (printf("Error: wrong amount of arguments!\n"), 1);
	if (atoi(argv[1]) == 1)
		return (printf("0 1 died\n"), 0);
	parse_data(argv + 1, argc, &args);
	if (check_values(args))
		return (printf("Error: invalid input!\n"), 1);
	thread_args = (t_args *)malloc(sizeof(t_args) * args.n_philos);
	init_thread_args(args, thread_args, &check_thread_args);
	threads = (pthread_t *)malloc(args.n_philos * sizeof(pthread_t));
	i = -1;
	while (++i < args.n_philos)
		pthread_create(&threads[i], NULL, routine, (void *)&thread_args[i]);
	i = -1;
	while (++i < args.n_philos)
		pthread_detach(threads[i]);
	// while (++i < args.n_philos)
	// 	pthread_join(threads[i], NULL);
	check_death(&check_thread_args);
	return (0);
}
