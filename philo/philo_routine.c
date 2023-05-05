/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:58:34 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/05 19:53:44 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_full(t_philo *philo)
{
	if (philo->share->args->must_eat_count == philo->eat_count)
	{
		pthread_mutex_lock(&(philo->share->lock_m));
		philo->share->full_philo++;
		pthread_mutex_unlock(&(philo->share->lock_m));
		return (1);
	}
	return (0);
}

static int	is_end(void *ptr)
{
	t_philo		*philo;
	uint64_t	now;

	philo = (t_philo *)ptr;
	now = get_time();
	if (now - philo->last_meal >= (uint64_t)philo->share->args->time_to_die)
	{
		print_msg(philo, "died", "\033[0;31m");
		pthread_mutex_lock(&(philo->share->finish_m));
		philo->share->running = 0;
		pthread_mutex_unlock(&(philo->share->finish_m));
		return (1);
	}
	if (philo->share->args->number == philo->share->full_philo)
	{
		pthread_mutex_lock(&(philo->share->finish_m));
		philo->share->running = 0;
		pthread_mutex_unlock(&(philo->share->finish_m));
		return (1);
	}
	return (0);
}

void	*routine(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	if (!((philo->id) & 1))
		usleep(1000);
	while (42)
	{
		pickup(philo);
		if (is_end(philo))
			break ;
		eat(philo);
		if (is_end(philo))
			break ;
		putdown(philo);
		if (is_full(philo))
			break ;
		ft_sleep(philo);
		think(philo);
	}
	putdown(philo);
	return (NULL);
}
