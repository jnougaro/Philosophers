/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnougaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:45:16 by jnougaro          #+#    #+#             */
/*   Updated: 2022/01/04 16:47:40 by jnougaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*so1;
	unsigned char	*so2;

	i = 0;
	so1 = (unsigned char *)s1;
	so2 = (unsigned char *)s2;
	while ((so1[i] || so2[i]) && i < n)
	{
		if (so1[i] != so2[i])
			return (so1[i] - so2[i]);
		i++;
	}	
	return (0);
}

int	is_digit(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}

void	print_error(int index)
{
	if (index == 1)
		printf("Error: wrong number of arguments\n");
	else if (index == 2)
		printf("Error: argument is not a number or is invalid\n");
	else if (index == 3)
		printf("Error: argument is greater than int max\n");
	else if (index == 4)
		printf("Error: number of required meal is 0\n");
	else if (index == 5)
		printf("Error: there is no philosopher\n");
}

void	free_philo(t_struct *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		free(philo[i]);
		i++;
	}
	free(philo);
	philo = NULL;
}
