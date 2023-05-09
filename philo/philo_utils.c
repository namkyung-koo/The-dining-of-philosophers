/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:00:05 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/09 18:32:27 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *msg, int value)
{
	ft_putstr_fd(msg, 2);
	return (value);
}

void	print_msg(t_philo *philo, char *msg, char *color)
{
	uint64_t	now;

	pthread_mutex_lock(&(philo->share->finish_m));
	if (philo->share->running)
	{
		now = get_time();
		printf("%s%llu %d %s\n", color, now - philo->share->start_time, \
		philo->id + 1, msg);
	}
	pthread_mutex_unlock(&(philo->share->finish_m));
}

void	clean_memory(t_philo *philo, t_share *share)
{
	int	i;

	i = 0;
	while (i < share->args->number)
	{
		pthread_mutex_destroy(&(share->forks[i].fork));
		i++;
	}
	pthread_mutex_destroy(&(share->lock_m));
	pthread_mutex_destroy(&(share->finish_m));
	free(share->forks);
	free(philo);
}
