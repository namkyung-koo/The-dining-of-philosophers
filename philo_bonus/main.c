/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:58:25 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/06 22:57:39 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	set_dinner(t_philo **philo)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (i < (*philo)->share->args->number)
	{
		(*philo)[i].pid = fork();
		if ((*philo[i]).pid == 0)
			routine(&(*philo)[i]);
		else if ((*philo)[i].pid > 0)
			wait_children(*philo);
		i++;
	}
	pthread_create(&monitor, NULL, is_end, (*philo));
	pthread_join(monitor, NULL);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_share	share;
	t_args	args;

	if (ac < 5 || ac > 6)
		return (print_error("The number of ac must be 5 or 6.\n", 1));
	if (init_args(&args, ac, av) || init_share(&share, &args) \
	|| init_philo(&philo, &share))
		return (1);
	set_dinner(&philo);
	return (0);
}
