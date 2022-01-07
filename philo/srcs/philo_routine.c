/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnougaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 10:00:06 by jnougaro          #+#    #+#             */
/*   Updated: 2022/01/06 16:40:33 by jnougaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(uint64_t current_time, t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->print);
	if (current_time == 0)
		current_time = get_current_time(philo);
	pthread_mutex_lock(&philo->data->died);
	if (philo->data->philo_died == 1)
	{
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->data->died);
		return ;
	}
	pthread_mutex_unlock(&philo->data->died);
	if (i == 1)
		printf("%5lu_in_ms %d has taken a fork\n", current_time, philo->id);
	else if (i == 2)
		printf("%5lu_in_ms %d\e[0;32m is eating\e[0m\n", current_time, philo->id);
	else if (i == 3)
		printf("%5lu_in_ms %d\e[0;34m is sleeping\e[0m\n", \
			current_time, philo->id);
	else if (i == 4)
		printf("%5lu_in_ms %d\e[0;35m is thinking\e[0m\n", \
			current_time, philo->id);
	else if (i == 5)
		printf("%5lu_in_ms %d\e[0;31m died\e[0m\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

uint64_t	get_current_time(t_philo *philo)
{
	uint64_t	ret_start;
	uint64_t	ret_end;
	uint64_t	current_time;

	ret_start = ((philo->data->start_simulation.tv_sec * (uint64_t)1000) \
				+ (philo->data->start_simulation.tv_usec / 1000));
	gettimeofday(&philo->data->end_simulation, NULL);
	ret_end = ((philo->data->end_simulation.tv_sec * (uint64_t)1000) \
				+ (philo->data->end_simulation.tv_usec / 1000));
	current_time = (ret_end - ret_start);
	return (current_time);
}

void	get_now(t_struct *data)
{
	gettimeofday(&data->get_now, NULL);
	data->now = ((data->get_now.tv_sec * (uint64_t)1000) \
			+ (data->get_now.tv_usec / 1000));
}

int	philo_routine(t_philo *philo, int index)
{
	assign_fork(philo, index);
	if (philo_take_fork(philo) == 1)
		return (1);
	if (check_time_current_meal(philo) == 1)
		return (1);
	if (check_if_died(philo, 2) == 1)
		return (1);
	if (philo_eat(philo) == 1)
		return (1);
	if (check_if_died(philo, 0) == 1)
		return (1);
	if (philo_sleep(philo) == 1)
		return (1);
	if (check_if_died(philo, 0) == 1)
		return (1);
	print_philo(0, philo, 4);
	return (0);
}

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if (philo->id % 2 == 0)
		{
			if (philo_routine(philo, 1) == 1)
				break ;
		}
		else if (philo->id % 2 != 0)
		{
			if (philo->id == 1)
			{
				if (philo_routine(philo, 2) == 1)
					break ;
			}	
			else
			{
				if (philo_routine(philo, 3) == 1)
					break ;
			}
		}
	}
	return (NULL);
}
