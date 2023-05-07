/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:58:25 by nakoo             #+#    #+#             */
/*   Updated: 2023/05/07 13:42:44 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	wait_children(int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

static int	set_dinner(t_philo **philo)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (i < (*philo)->share->args->number)
	{
		(*philo)[i].pid = fork();
		if ((*philo)[i].pid == 0)
			routine(&(*philo)[i]);
		else if ((*philo)[i].pid < 0)
			return (1);
		i++;
	}
	// is_end(*philo);
	// exit(0);
	pthread_create(&monitor, NULL, is_end, (*philo));
	pthread_join(monitor, NULL);
	wait_children((*philo)->share->args->number);
	return (0);
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
	if (set_dinner(&philo))
		return (print_error("Failed to fork", 1));
	clean_memory(philo, &share);
	return (0);
}
