/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnougaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:46:53 by jnougaro          #+#    #+#             */
/*   Updated: 2022/01/06 17:02:09 by jnougaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	treat_usleep(t_philo *philo)
{
	if (philo->data->nb_philo > 4)
		usleep(philo->data->nb_philo * 1000);
	else
		usleep(1500);
}

int	check_time_current_meal(t_philo *philo)
{
	gettimeofday(&philo->start_meal, NULL);
	treat_usleep(philo);
	philo->current_meal = ((philo->start_meal.tv_sec * \
			(uint64_t)1000) + (philo->start_meal.tv_usec / 1000));
	if (philo->last_meal != 0)
	{
		if ((philo->current_meal - philo->last_meal) >= philo->data->time_die)
		{
			if (check_if_died(philo, 2) == 1)
				return (1);
			print_philo(0, philo, 5);
			pthread_mutex_lock(&philo->data->died);
			philo->data->philo_died = 1;
			pthread_mutex_unlock(&philo->data->died);
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
			return (1);
		}
	}
	pthread_mutex_lock(&philo->data->lock_meal);
	philo->last_meal = philo->current_meal;
	pthread_mutex_unlock(&philo->data->lock_meal);
	return (0);
}

int	check_if_died(t_philo *philo, int index)
{
	pthread_mutex_lock(&philo->data->died);
	if (philo->data->philo_died == 1)
	{
		if (index == 1)
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		else if (index == 2)
		{
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		}
		pthread_mutex_unlock(&philo->data->died);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->died);
	return (0);
}

void	assign_fork(t_philo *philo, int index)
{
	if (index == 1)
	{
		usleep(1000);
		philo->right_fork = philo->id - 1;
		philo->left_fork = philo->id - 2;
	}
	else if (index == 2)
	{
		philo->right_fork = philo->data->nb_fork - 1;
		philo->left_fork = philo->id - 1;
	}
	else
	{
		philo->right_fork = philo->id - 2;
		philo->left_fork = philo->id - 1;
	}
}		

int	die_before_meal(t_philo *philo)
{
	uint64_t	current_time;

	current_time = get_current_time(philo);
	if (current_time > philo->data->time_die && philo->meal_eaten == 0)
		return (1);
	return (0);
}
