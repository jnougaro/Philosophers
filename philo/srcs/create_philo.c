/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnougaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:01:44 by jnougaro          #+#    #+#             */
/*   Updated: 2022/01/06 16:41:38 by jnougaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_mutex(t_struct *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
	{
		free(data->philo_tab);
		exit(1);
	}
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->died, NULL);
	pthread_mutex_init(&data->lock_meal, NULL);
	pthread_mutex_init(&data->lock_meal_eaten, NULL);
}

void	wait_philo(t_struct *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philo_tab[i], NULL) != 0)
		{
			free(data->forks);
			free(data->philo_tab);
			exit(1);
		}
		i++;
	}
}

void	global_check_die(t_philo **philo, t_struct *data)
{
	int	i;

	i = 0;
	init_check_death(philo, data);
	while (1)
	{
		if (data->nb_philo == 1)
			break ;
		i = 0;
		get_now(data);
		loop_check_die(philo, data, i);
		pthread_mutex_lock(&data->died);
		if (data->philo_died == 1)
		{
			pthread_mutex_unlock(&data->died);
			break ;
		}
		pthread_mutex_unlock(&data->died);
	}
	destroy_check_death(philo, data);
}

void	create_philo(t_struct *data)
{
	t_philo	**philo;
	int		i;

	i = 0;
	philo = NULL;
	create_mutex(data);
	data->philo_tab = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!data->philo_tab)
		exit(1);
	philo = init_each_philo(philo, data);
	while (i < data->nb_philo)
	{
		philo[i]->id = i + 1;
		philo[i]->data = data;
		if (pthread_create(&data->philo_tab[i], NULL, &routine, philo[i]) != 0)
		{
			free(data->philo_tab);
			exit(1);
		}
		i++;
	}
	global_check_die(philo, data);
	wait_philo(data);
	free_philo(data, philo);
}

void	destroy_mutex(t_struct *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->died);
	pthread_mutex_destroy(&data->lock_meal);
	pthread_mutex_destroy(&data->lock_meal_eaten);
}
