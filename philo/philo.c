/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:58:25 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/04 17:57:45 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_args(t_args *args, int ac, char **av)
{
	memset(args, 0, sizeof(t_args));
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
		return (print_error("The value of time must exceed 60ms.\n", 1));
	return (0);
}

static int	init_share(t_share *share, t_args *args)
{
	memset(share, 0, sizeof(t_share));
	share->forks = (pthread_mutex_t *) \
	malloc(sizeof(pthread_mutex_t) * args->number);
	if (share->forks == NULL)
		return (print_error("Failed to allocate memory.\n", 1));
	share->running |= 1;
	share->args = args;
	share->full_philo = 0;
	share->start_time = get_time();
	pthread_mutex_init(&(share->lock_m), NULL);
	pthread_mutex_init(&(share->print_m), NULL);
	return (0);
}

static int	init_philo(t_philo **philo, t_share *share)
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
		pthread_mutex_init(&(share->forks[i]), NULL);
		i++;
	}
	share->philo = *philo;
	return (0);
}

int	check_finish(t_philo *philo)
{
	uint64_t	now;

	pthread_mutex_lock(&(philo->share->lock_m));
	now = get_time();
	if (now - philo->last_meal >= (uint64_t)philo->share->args->time_to_die)
	{
		print_msg(philo, "died", "\033[0;31m");
		philo->share->running &= ~1;
		pthread_mutex_unlock(&(philo->share->lock_m));
		return (0);
	}
	if (philo->share->args->number == philo->share->full_philo)
	{
		philo->share->running &= ~1;
		pthread_mutex_unlock(&(philo->share->lock_m));
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_share	share;
	t_args	args;
	int		i;

	if (ac < 5 || ac > 6)
		return (print_error("The number of ac must be 5 or 6.\n", 1));
	if (init_args(&args, ac, av) || init_share(&share, &args) \
	|| init_philo(&philo, &share))
		return (1);
	i = 0;
	while (i < args.number)
	{
		pthread_create(&(philo[i].pthread), NULL, routine, &(philo[i]));
		if (args.number == 1)
			pthread_detach(philo[i].pthread);
		i++;
	}
	clean_memory(philo, &share);
	return (0);
}
