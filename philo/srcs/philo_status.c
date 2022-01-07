/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnougaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:03:03 by jnougaro          #+#    #+#             */
/*   Updated: 2022/01/06 17:24:43 by jnougaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_take_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
		usleep(100);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	if (check_if_died(philo, 1) == 1)
		return (1);
	print_philo(0, philo, 1);
	if (philo->data->nb_philo == 1)
	{
		usleep(philo->data->time_die * 1000);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		print_philo(0, philo, 5);
		return (1);
	}
	if (philo->id % 2 != 0)
		usleep(100);
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	if (check_if_died(philo, 2) == 1)
		return (1);
	print_philo(0, philo, 1);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	print_philo(0, philo, 2);
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_lock(&philo->data->lock_meal_eaten);
	philo->meal_eaten += 1;
	pthread_mutex_unlock(&philo->data->lock_meal_eaten);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	if (philo->meal_eaten == philo->data->nb_must_eat)
		return (1);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	print_philo(0, philo, 3);
	usleep(philo->data->time_sleep * 1000);
	return (0);
}
