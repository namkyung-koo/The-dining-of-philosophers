/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:55:28 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/10 11:21:05 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>

enum e_state {
	DOWN,
	UP
};

typedef struct s_args {
	int	number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_count;
}	t_args;

typedef struct s_fork {
	pthread_mutex_t	fork;
	int				state;
}	t_fork;

typedef struct s_philo	t_philo;

typedef struct s_share {
	int				running;
	int				full_philo;
	t_args			*args;
	t_philo			*philo;
	t_fork			*forks;
	uint64_t		start_time;
	pthread_mutex_t	lock_m;
	pthread_mutex_t	print_m;
	pthread_mutex_t	finish_m;
}	t_share;

typedef struct s_philo {
	int				id;
	int				left;
	int				right;
	int				eat_count;
	uint64_t		last_meal;
	t_share			*share;
	pthread_t		pthread;
}	t_philo;

/* philo_init.c */
int			init_args(t_args *args, int ac, char **av);
int			init_share(t_share *share, t_args *args);
int			init_philo(t_philo **philo, t_share *share);

/* philo_outils.c */
int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *s);

/* philo_utils.c */
int			print_error(char *msg, int value);
void		msleep(int time);
void		clean_memory(t_philo *philo, t_share *share);
void		print_msg(t_philo *philo, char *msg, char *color);
uint64_t	get_time(void);

/* philo_act.c */
void		pickup(t_philo *philo);
void		eat(t_philo *philo);
void		putdown(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		think(t_philo *philo);

/* philo_routine.c */
void		*routine(void *ptr);
void		*is_end(void *ptr);

#endif