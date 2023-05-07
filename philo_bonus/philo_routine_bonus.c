/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:58:34 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/07 13:37:50 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_finish(t_philo *philo)
{
	sem_wait(philo->share->finish_s);
	if (!(philo->share->running))
	{
		sem_post(philo->share->finish_s);
		return (1);
	}
	sem_post(philo->share->finish_s);
	return (0);
}

static int	is_full(t_philo *philo)
{
	if (check_finish(philo))
	{
		putdown(philo);
		return (1);
	}
	if (philo->share->args->must_eat_count == philo->eat_count)
	{
		sem_wait(philo->share->lock_s);
		philo->share->full_philo++;
		sem_post(philo->share->lock_s);
		return (1);
	}
	return (0);
}

static void	*change_running(t_philo *philo)
{
	sem_wait(philo->share->finish_s);
	philo->share->running = 0;
	sem_post(philo->share->finish_s);
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
			sem_wait(philo->share->lock_s);
			if (get_time() - philo[i].last_meal \
			>= (uint64_t)philo->share->args->time_to_die)
			{
				sem_post(philo->share->lock_s);
				print_msg(philo, "died", "\033[0;31m");
				return (change_running(philo));
			}
			sem_post(philo->share->lock_s);
		}
		if (philo->share->args->number == philo->share->full_philo)
			return (change_running(philo));
	}
	return (NULL);
}

void	routine(t_philo *philo)
{
	if (!(philo->id & 1))
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
	return ;
}
