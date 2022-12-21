/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:20:22 by dantonik          #+#    #+#             */
/*   Updated: 2022/12/21 11:29:34 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <string.h>

# define BLACK	"\033[0;30m"
# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"
# define BLUE	"\033[0;34m"
# define PURPLE	"\033[0;35m"
# define CYAN	"\033[0;36m"
# define WHITE	"\033[0;37m"
# define RESET	"\033[0m"

# define MIN_TIME 60

enum e_print
{
	P_EAT,
	P_SLEEP,
	P_THINK,
	P_DEAD,
	P_FORK
};

typedef struct s_args
{
	int					pid;
	int					n_philos;
	size_t				start_time;
	size_t				last_meal;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					finished;
	int					*meals_to_finish; // number of times each philosopher must eat
	int					*alive; // array to keep track of which philosophers are still alive
	pthread_mutex_t		*forks; // array of mutexes for each fork
	int					first_fork;
	int					second_fork;
	pthread_mutex_t		*check_mutex; // mutex to protect data accessed by checking thread and philosopher threads
}	t_args;

// typedef struct s_philo
// {
// 	int					id;
// 	int					n_philos;
// 	size_t				start_time;
// 	pthread_mutex_t		fork;
// 	pthread_mutex_t		*first_fork;
// 	pthread_mutex_t		*second_fork;
// 	int					meals;
// 	pthread_mutex_t		mmeals;
// 	bool				done;
// 	pthread_mutex_t		mdone;
// 	size_t				last_meal;
// 	struct s_data		*data;
// }	t_philo;

// typedef struct s_data
// {
// 	int					n_philos;
// 	int					time_to_die;
// 	int					time_to_eat;
// 	int					time_to_sleep;
// 	int					total_meals;
// 	bool				alive;
// 	size_t				start_time;
// 	pthread_mutex_t		mutex;
// 	t_philo				*p;
// }	t_data;

// MAIN THREAD
void		check_death(t_args *check_args);

// MINILIBFT
long		ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);

// PARSE
void		parse_data(char **av, int ac, t_args *data);

// PRINT
int			ft_print(t_args *args, int msg);
int			done(t_args *args);

// ROUTINE
void		*routine(void *args);

// TIME
time_t		get_time(void);
void		ft_sleep(size_t sleep);

#endif