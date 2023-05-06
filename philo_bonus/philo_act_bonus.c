/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:48:32 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/06 19:08:57 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pickup(t_philo *philo)
{
	print_msg(philo, "has taken a left fork", "\033[0;32m");
	if (philo->share->args->number == 1)
	{
		usleep(philo->share->args->time_to_die * 1000);
	}
	print_msg(philo, "has taken a right fork", "\033[0;32m");
}

void	eat(t_philo *philo)
{
	print_msg(philo, "is eating", "\033[0;34m");
	philo->eat_count++;
	philo->last_meal = get_time();
	msleep(philo->share->args->time_to_eat);
}

void	putdown(t_philo *philo)
{
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
