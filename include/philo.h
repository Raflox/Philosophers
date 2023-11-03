/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:39:12 by rafilipe          #+#    #+#             */
/*   Updated: 2023/10/31 20:51:12 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h> 
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>

# define ORANGE "\033[1;38;5;208m"	//Sleeping
# define GREEN "\033[1;32m" 		//Eating
# define RED "\033[1;31m"			//Death
# define YELLOW "\033[1;33m"		//Thinking
# define PURPLE "\033[1;35m"		//Fork
# define WHITE "\033[1;37m"			//Debug

typedef struct s_fork {
	int				status;
	pthread_mutex_t	hold;
}	t_fork;

typedef struct s_philo {
	int			id;
	int			last_meal;
	int			n_meal;
	pthread_t	philo;
	t_fork		*forks;
}	t_philo;

typedef struct s_config {
	int				philos_nb;
	int				t_sleep;
	int				t_eat;
	int				t_die;
	int				total_meals;
	int				start_time;
	int				is_dead;
	pthread_mutex_t	death;
	t_philo			*philos;
	pthread_mutex_t	log;
}	t_config;

/* DATA */
t_config	*data(void);
void		data_init(char **av);
int			threads_init(void);
void		*routine(void *philos);

/* ROUTINE */
void		eat(t_philo	*philo);
void		rest(t_philo *philo);
void		think(t_philo *philo);
int			grim_reaper(t_philo *philo);
int			death_check(void);

/* UTILS */
int			ft_atoi(const char *str);
void		ft_usleep(int time, t_philo *philo);
void		lock_fork(int fork, t_philo *philo);
void		unlock_forks(int fork, t_philo *philo);

/* CHECKERS */
int			check_digit(char *str);
int			check_args(int ac, char **av);

/* TIME */
int			time_elapsed(void);
int			get_time(void);

/* LOGGING */
void		logger(const char *msg, char *color, t_philo *philo);

/* ERROR */
void		error(const char *msg, int mode);
void		clean(int mode);

#endif