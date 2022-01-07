/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnougaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:43:09 by jnougaro          #+#    #+#             */
/*   Updated: 2021/12/23 14:50:09 by jnougaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_struct	data;

	if (argc != 5 && argc != 6)
	{
		print_error(1);
		exit(1);
	}
	init_struct(&data);
	check_arg(&data, argv);
	gettimeofday(&data.start_simulation, NULL);
	create_philo(&data);
	destroy_mutex(&data);
	free(data.forks);
	free(data.philo_tab);
	return (0);
}
