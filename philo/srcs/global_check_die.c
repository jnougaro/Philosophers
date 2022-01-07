/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_check_die.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnougaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:05:14 by jnougaro          #+#    #+#             */
/*   Updated: 2022/01/06 16:41:10 by jnougaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_check_death(t_philo **philo, t_struct *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&philo[i]->check_death, NULL);
		i++;
	}
}

void	destroy_check_death(t_philo **philo, t_struct *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&philo[i]->check_death);
		i++;
	}
}

int	check_death_before_meal(t_philo **philo, t_struct *data, int i)
{
	if (die_before_meal(philo[i]) == 1)
	{
		print_philo(0, philo[i], 5);
		pthread_mutex_lock(&data->died);
		data->philo_died = 1;
		pthread_mutex_unlock(&data->died);
		pthread_mutex_unlock(&philo[i]->check_death);
		pthread_mutex_unlock(&data->lock_meal);
		return (1);
	}
	return (0);
}

int	check_diff(t_philo **philo, t_struct *data, int i)
{
	pthread_mutex_lock(&data->lock_meal_eaten);
	if (philo[i]->meal_eaten != data->nb_must_eat)
		print_philo(0, philo[i], 5);
	pthread_mutex_unlock(&data->lock_meal_eaten);
	pthread_mutex_lock(&data->died);
	data->philo_died = 1;
	pthread_mutex_unlock(&data->died);
	pthread_mutex_unlock(&philo[i]->check_death);
	pthread_mutex_unlock(&data->lock_meal);
	return (1);
}

void	loop_check_die(t_philo **philo, t_struct *data, int i)
{
	while (i < data->nb_philo)
	{
		usleep(200);
		pthread_mutex_lock(&philo[i]->check_death);
		pthread_mutex_lock(&data->lock_meal);
		if (philo[i]->last_meal == 0)
		{
			if (check_death_before_meal(philo, data, i) == 1)
				break ;
		}
		else if (philo[i]->last_meal != 0 && \
				((data->now - philo[i]->last_meal) > data->time_die))
		{
			if (check_diff(philo, data, i) == 1)
				break ;
		}
		pthread_mutex_unlock(&data->lock_meal);
		pthread_mutex_unlock(&philo[i]->check_death);
		i++;
	}
}
