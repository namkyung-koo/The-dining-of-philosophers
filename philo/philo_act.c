/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:48:32 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/06 15:19:12 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pickup(t_philo *philo)
{
	pthread_mutex_lock(&(philo->share->forks[philo->left]));
	print_msg(philo, "has taken a left fork", "\033[0;32m");
	pthread_mutex_lock(&(philo->share->forks[philo->right]));
	print_msg(philo, "has taken a right fork", "\033[0;32m");
}

void	eat(t_philo *philo)
{
	print_msg(philo, "is eating", "\033[0;34m");
	pthread_mutex_lock(&(philo->share->lock_m));
	philo->eat_count++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(philo->share->lock_m));
	msleep(philo->share->args->time_to_eat);
}

void	putdown(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->share->forks[philo->left]));
	pthread_mutex_unlock(&(philo->share->forks[philo->right]));
}

void	ft_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping", "\033[0;35m");
	msleep(philo->share->args->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_msg(philo, "is thinking", "\033[0;37m");
	usleep(500);
}
