/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:00:05 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/06 19:07:32 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_error(char *msg, int value)
{
	ft_putstr_fd(msg, 2);
	return (value);
}

void	print_msg(t_philo *philo, char *msg, char *color)
{
	uint64_t	now;

	if (philo->share->running)
	{
		now = get_time();
		printf("%s%llu %d %s\n", color, now - philo->share->start_time, \
		philo->id + 1, msg);
	}
}

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	msleep(int time)
{
	uint64_t	t1;
	uint64_t	t2;

	t1 = get_time();
	while (1)
	{
		t2 = get_time();
		if (t2 - t1 >= (uint64_t)time)
			break ;
		usleep(100);
	}
}

void	clean_memory(t_philo *philo, t_share *share)
{
}
