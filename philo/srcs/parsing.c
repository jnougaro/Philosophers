/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnougaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:01:43 by jnougaro          #+#    #+#             */
/*   Updated: 2022/01/04 16:48:07 by jnougaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_int_max(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j] == '0')
			j++;
		if (ft_strlen(&argv[i][j]) > ft_strlen("2147483647"))
		{
			print_error(3);
			exit(1);
		}
		else if (ft_strlen(&argv[i][j]) == ft_strlen("2147483647"))
		{
			if (ft_strncmp(&argv[i][j], "2147483647", \
					ft_strlen(&argv[i][j])) > 0)
			{
				print_error(3);
				exit(1);
			}
		}
		i++;
	}
}

void	fill_arg(t_struct *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	if (data->nb_philo == 0)
	{
		print_error(5);
		exit(1);
	}
	data->nb_fork = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nb_must_eat = ft_atoi(argv[5]);
}

void	check_if_num(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (is_digit(argv[i][j]) == 0)
			{
				print_error(2);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void	check_arg(t_struct *data, char **argv)
{
	check_if_num(argv);
	check_int_max(argv);
	fill_arg(data, argv);
	if (data->nb_must_eat == 0)
	{
		print_error(4);
		exit(1);
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * sign);
}
