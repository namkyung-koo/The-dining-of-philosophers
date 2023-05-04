/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:55:28 by nakoo             #+#    #+#             */
/*   Updated: 2023/04/24 14:07:22 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>

enum e_boolean {
	FALSE,
	TRUE
};

typedef struct s_args {
	int	number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_count;
}	t_args;

typedef struct s_philo	t_philo;

typedef struct s_share {
	int				running;
	int				full_philo;
	t_args			*args;
	t_philo			*philo;
	uint64_t		start_time;
	pthread_mutex_t	lock_m;
	pthread_mutex_t	died_m;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_m;
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

/* ft_utils.c */
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);

/* utils.c */
uint64_t	get_time(void);
void		msleep(int time);
int			print_error(char *msg, int value);
void		clean_memory(t_philo *philo, t_share *share);
void		print_msg(t_philo *philo, char *msg, char *color);

/* simulation.c */
void		*routine(void *ptr);

#endif