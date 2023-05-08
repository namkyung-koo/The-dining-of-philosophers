/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:58:25 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/08 17:14:32 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
int get_fork_state(struct s_fork *fork)
{
	int ret;
	
	ret = FAIL;
	pthread_mutex_lock(fork->lock);
	if (fork->state == DOWN){
		ret = SUC;
		fork->state = UP;
	}
	pthread_mutex_unlock(fork->lock);
	return (ret);
} 

int pick_fork()
{
	int isPick = 0;
	while(1)
	{
		isPick = get_fork_state(left_fork);
		if (isPick == SUC)
			return (1);
	}
}
*/
int	main(int ac, char **av)
{
	pthread_t	monitor;
	t_philo		*philo;
	t_share		share;
	t_args		args;
	int			i;

	if (ac < 5 || ac > 6)
		return (print_error("The number of ac must be 5 or 6.\n", 1));
	if (init_args(&args, ac, av) || init_share(&share, &args) \
	|| init_philo(&philo, &share))
		return (1);
	i = 0;
	while (i < args.number)
	{
		pthread_create(&(philo[i].pthread), NULL, routine, &(philo[i]));
		i++;
	}
	pthread_create(&monitor, NULL, is_end, philo);
	pthread_join(monitor, NULL);
	clean_memory(philo, &share);
	return (0);
}
