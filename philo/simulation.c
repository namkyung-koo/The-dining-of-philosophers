/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:48:32 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/04 17:21:19 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	dining(t_philo *philo)
{
	pthread_mutex_lock(&(philo->share->forks[philo->left]));
	print_msg(philo, "has taken a left fork", "\033[0;32m");
	usleep(50);
	pthread_mutex_lock(&(philo->share->forks[philo->right]));
	print_msg(philo, "has taken a right fork", "\033[0;32m");
	usleep(50);
	print_msg(philo, "is eating", "\033[0;34m");
	pthread_mutex_lock(&(philo->share->lock_m));
	philo->eat_count++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(philo->share->lock_m));
	msleep(philo->share->args->time_to_eat);
	pthread_mutex_unlock(&(philo->share->forks[philo->left]));
	pthread_mutex_unlock(&(philo->share->forks[philo->right]));
}

static void	sleep_and_think(t_philo *philo)
{
	print_msg(philo, "is sleeping", "\033[0;35m");
	msleep(philo->share->args->time_to_sleep);
	print_msg(philo, "is thinking", "\033[0;37m");
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (!((philo->id) & 1))
		usleep(1000);
	while (42)
	{
		dining(philo);
		if (philo->share->args->must_eat_count == philo->eat_count)
		{
			pthread_mutex_lock(&(philo->share->lock_m));
			philo->share->full_philo++;
			pthread_mutex_unlock(&(philo->share->lock_m));
			break ;
		}
		pthread_mutex_lock(&(philo->share->died_m));
		if (!(philo->share->running & 1))
			break ;
		pthread_mutex_unlock(&(philo->share->died_m));
		sleep_and_think(philo);
	}
	pthread_mutex_unlock(&(philo->share->died_m));
	return (NULL);
}
