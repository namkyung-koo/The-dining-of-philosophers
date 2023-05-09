/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:01:16 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/09 18:31:28 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	res;

	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (print_error("Negative numbers are not allowed.\n", -1));
		str++;
	}
	if (*str == '\0')
		return (print_error("There are invaild arguments.\n", -1));
	res = 0;
	while ('0' <= *str && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (print_error("There are invaild arguments.\n", -1));
	return (res);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
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
