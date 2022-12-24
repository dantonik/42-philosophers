/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:20:22 by dantonik          #+#    #+#             */
/*   Updated: 2022/12/23 08:28:01 by dantonik         ###   ########.fr       */
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
# define MAX_PHILOS 199

enum e_print
{
	P_EAT,
	P_SLEEP,
	P_THINK,
	P_FORK,
	P_DEAD,
	P_FULL
};

typedef struct s_args
{
	int					pid;
	int					n_philos;
	size_t				start_time;
	size_t				*last_meal;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					finished;
	int					*meals_to_finish;
	int					*alive;
	pthread_mutex_t		*forks;
	int					first_fork;
	int					second_fork;
	pthread_mutex_t		*check_mutex;
	struct s_args		*args;
}	t_args;

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