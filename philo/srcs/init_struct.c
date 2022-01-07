/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnougaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:31:04 by jnougaro          #+#    #+#             */
/*   Updated: 2022/01/04 11:30:28 by jnougaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(t_struct *data)
{
	data->nb_philo = 0;
	data->nb_fork = 0;
	data->time_die = 0;
	data->time_eat = 0;
	data->time_sleep = 0;
	data->nb_must_eat = -1;
	data->philo_died = 0;
}

t_philo	**init_each_philo(t_philo **philo, t_struct *data)
{
	int	i;

	i = 0;
	philo = ft_calloc(sizeof(t_philo *), data->nb_philo);
	if (!philo)
		exit(1);
	while (i < data->nb_philo)
	{
		philo[i] = ft_calloc(sizeof(t_philo), 1);
		if (!philo[i])
			exit(1);
		philo[i]->id = 0;
		philo[i]->current_meal = 0;
		philo[i]->last_meal = 0;
		philo[i]->meal_eaten = 0;
		philo[i]->right_fork = 0;
		philo[i]->left_fork = 0;
		i++;
	}
	return (philo);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*str;

	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_memset(str, 0, (count * size));
	return (str);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *) b;
	while (i < len)
	{
		str[i] = (unsigned char) c;
		i++;
	}
	return (b);
}
