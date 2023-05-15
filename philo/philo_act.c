/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:48:32 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/15 17:13:31 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pickup(t_philo *philo)
{
	pthread_mutex_lock(&(philo->share->forks[philo->left].fork));
	philo->share->forks[philo->left].state = UP;
	print_msg(philo, "has taken a fork", "\033[0;32m");
	if (philo->args->number == 1)
	{
		usleep(philo->args->time_to_die * 1000);
		return ;
	}
	pthread_mutex_lock(&(philo->share->forks[philo->right].fork));
	philo->share->forks[philo->right].state = UP;
	print_msg(philo, "has taken a fork", "\033[0;32m");
}

void	eat(t_philo *philo)
{
	if (philo->args->number != 1)
	{
		print_msg(philo, "is eating", "\033[0;34m");
		philo->eat_count++;
		pthread_mutex_lock(&(philo->share->lock_m));
		philo->last_meal = get_time();
		pthread_mutex_unlock(&(philo->share->lock_m));
		msleep(philo->args->time_to_eat);
	}
}

void	putdown(t_philo *philo)
{
	philo->share->forks[philo->left].state = DOWN;
	pthread_mutex_unlock(&(philo->share->forks[philo->left].fork));
	if (philo->args->number != 1)
	{
		philo->share->forks[philo->right].state = DOWN;
		pthread_mutex_unlock(&(philo->share->forks[philo->right].fork));
	}
}

void	ft_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping", "\033[0;35m");
	msleep(philo->args->time_to_sleep);
	print_msg(philo, "is thinking", "\033[0;37m");
}
