/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:58:34 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/09 08:45:59 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_finish(t_philo *philo)
{
	pthread_mutex_lock(&(philo->share->finish_m));
	if (!(philo->share->running))
	{
		pthread_mutex_unlock(&(philo->share->finish_m));
		return (1);
	}
	pthread_mutex_unlock(&(philo->share->finish_m));
	pthread_mutex_lock(&(philo->share->lock_m));
	if (philo->share->args->number == philo->share->full_philo)
	{
		pthread_mutex_unlock(&(philo->share->lock_m));
		return (1);
	}
	pthread_mutex_unlock(&(philo->share->lock_m));
	return (0);
}

static int	is_full(t_philo *philo)
{
	if (check_finish(philo))
		return (1);
	if (philo->share->args->must_eat_count == philo->eat_count)
	{
		pthread_mutex_lock(&(philo->share->lock_m));
		philo->share->full_philo++;
		pthread_mutex_unlock(&(philo->share->lock_m));
		return (1);
	}
	return (0);
}

static void	*change_running(t_philo *philo)
{
	pthread_mutex_lock(&(philo->share->finish_m));
	philo->share->running = 0;
	pthread_mutex_unlock(&(philo->share->finish_m));
	return (NULL);
}

void	*is_end(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)ptr;
	while (42)
	{
		usleep(100);
		i = -1;
		while (++i < philo->share->args->number)
		{
			pthread_mutex_lock(&(philo->share->lock_m));
			if (get_time() - philo[i].last_meal \
			>= (uint64_t)philo->share->args->time_to_die)
			{
				pthread_mutex_unlock(&(philo->share->lock_m));
				print_msg(&philo[i], "died", "\033[0;31m");
				return (change_running(philo));
			}
			pthread_mutex_unlock(&(philo->share->lock_m));
		}
		if (check_finish(philo))
			return (change_running(philo));
	}
	return (NULL);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (!((philo->id) & 1))
		usleep(1000);
	while (42)
	{
		pickup(philo);
		eat(philo);
		if (is_full(philo))
			break ;
		putdown(philo);
		ft_sleep(philo);
		think(philo);
	}
	putdown(philo);
	return (NULL);
}
