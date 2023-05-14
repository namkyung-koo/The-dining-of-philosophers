/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:58:25 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/14 18:41:37 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	pthread_t	monitor;
	t_philo		*philo;
	t_share		share;
	t_args		args;
	int			i;

	if (ac < 5 || ac > 6)
		return (print_error("The number of ac must be 5 or 6.\n", 1));
	if (init_args(&args, ac, av) || init_share(&share, args.number) \
	|| init_philo(&philo, &share, &args))
		return (1);
	i = -1;
	pthread_mutex_lock(&(philo->share->lock_m));
	while (++i < args.number)
		pthread_create(&(philo[i].pthread), NULL, routine, &(philo[i]));
	pthread_mutex_unlock(&(philo->share->lock_m));
	pthread_create(&monitor, NULL, is_end, philo);
	pthread_join(monitor, NULL);
	check_finish(philo);
	i = -1;
	while (++i < args.number)
		pthread_join(philo[i].pthread, NULL);
	clean_memory(philo, &share);
	return (0);
}
