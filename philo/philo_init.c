/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:51:46 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/10 11:08:43 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_args *args, int ac, char **av)
{
	args->number = ft_atoi(av[1]);
	if (args->number < 1)
		return (print_error("The number of philosophers must exceed 0.\n", 1));
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		args->must_eat_count = ft_atoi(av[5]);
		if (args->must_eat_count == 0)
			return (print_error("must_eat_count must be positive(not 0).\n", 1));
	}
	else
		args->must_eat_count = 0;
	if (args->number == -1 || args->time_to_die == -1 || \
	args->time_to_eat == -1 || args->time_to_sleep == -1 || \
	args->must_eat_count == -1)
		return (1);
	if (args->time_to_die < 60 || args->time_to_eat < 60 || \
	args->time_to_sleep < 60)
		return (print_error("The value of time must exceed 59ms.\n", 1));
	return (0);
}

int	init_share(t_share *share, t_args *args)
{
	share->forks = (t_fork *)malloc(sizeof(t_fork) * args->number);
	if (share->forks == NULL)
		return (print_error("Failed to allocate memory.\n", 1));
	share->running = 1;
	share->args = args;
	share->full_philo = 0;
	share->start_time = get_time();
	pthread_mutex_init(&(share->lock_m), NULL);
	pthread_mutex_init(&(share->print_m), NULL);
	pthread_mutex_init(&(share->finish_m), NULL);
	return (0);
}

int	init_philo(t_philo **philo, t_share *share)
{
	int	i;

	*philo = (t_philo *)malloc(sizeof(t_philo) * share->args->number);
	if (*philo == NULL)
	{
		free(share->forks);
		return (print_error("Failed to allocate memory.\n", 1));
	}
	i = 0;
	while (i < share->args->number)
	{
		(*philo)[i].id = i;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % share->args->number;
		(*philo)[i].eat_count = 0;
		(*philo)[i].share = share;
		(*philo)[i].last_meal = get_time();
		pthread_mutex_init(&(share->forks[i].fork), NULL);
		share->forks[i].state = DOWN;
		i++;
	}
	share->philo = *philo;
	return (0);
}
