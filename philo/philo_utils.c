/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:00:05 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/09 22:32:11 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_fork_state(t_philo *philo, int flag)
{
	int	ret;

	ret = FALSE;
	if (flag == LEFT)
	{
		// pthread_mutex_lock(&(philo->share->forks[philo->left].fork));
		if (philo->share->forks[philo->left].state == DOWN)
		{
			ret = TRUE;
			philo->share->forks[philo->left].state = UP;
			return (ret);
		}
		// pthread_mutex_unlock(&(philo->share->forks[philo->left].fork));
	}
	else if (flag == RIGHT)
	{
		// pthread_mutex_lock(&(philo->share->forks[philo->right].fork));
		if (philo->share->forks[philo->right].state == DOWN)
		{
			ret = TRUE;
			philo->share->forks[philo->right].state = UP;
			return (ret);
		}
		// pthread_mutex_unlock(&(philo->share->forks[philo->right].fork));
	}
	return (ret);
}

int	pick_fork(t_philo *philo, int flag)
{
	int	is_pick;

	is_pick = FALSE;
	while (1)
	{
		is_pick = get_fork_state(philo, flag);
		if (is_pick == TRUE)
			return (1);
	}
}

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
