/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnougaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:18:43 by jnougaro          #+#    #+#             */
/*   Updated: 2022/01/06 17:02:30 by jnougaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct s_struct
{
	pthread_t		*philo_tab;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	died;
	pthread_mutex_t	lock_meal;
	pthread_mutex_t	lock_meal_eaten;
	struct timeval	start_simulation;
	struct timeval	end_simulation;
	struct timeval	get_now;
	int				nb_philo;
	int				nb_fork;
	int				time_eat;
	int				time_sleep;
	int				nb_must_eat;
	int				philo_died;
	uint64_t		time_die;
	uint64_t		now;	
}	t_struct;

typedef struct s_philo
{
	t_struct		*data;
	int				id;
	int				meal_eaten;
	int				right_fork;
	int				left_fork;
	uint64_t		current_meal;
	uint64_t		last_meal;
	struct timeval	start_meal;
	struct timeval	end_last_meal;
	pthread_mutex_t	check_death;
}	t_philo;

void		init_struct(t_struct *data);
void		print_error(int index);
void		check_arg(t_struct *data, char **argv);
void		fill_arg(t_struct *data, char **argv);
void		check_int_max(char **argv);
void		check_if_num(char **argv);
void		*routine(void *arg);
void		destroy_mutex(t_struct *data);
void		wait_philo(t_struct *data);
void		create_philo(t_struct *data);
void		create_mutex(t_struct *data);
void		free_philo(t_struct *data, t_philo **philo);
void		print_philo(uint64_t current_time, t_philo *philo, int i);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);
void		assign_fork(t_philo *philo, int index);
void		global_check_die(t_philo **philo, t_struct *data);
void		get_now(t_struct *data);
void		init_check_death(t_philo **philo, t_struct *data);
void		destroy_check_death(t_philo **philo, t_struct *data);
void		loop_check_die(t_philo **philo, t_struct *data, int i);
void		treat_usleep(t_philo *philo);
int			is_digit(int c);
int			ft_strlen(const char *s);
int			ft_strncmp(char *s1, char *s2, size_t n);
int			ft_atoi(const char *str);
int			die_before_meal(t_philo *philo);
int			philo_routine(t_philo *philo, int index);
int			check_if_died(t_philo *philo, int index);
int			check_time_current_meal(t_philo *philo);
int			philo_eat(t_philo *philo);
int			philo_sleep(t_philo *philo);
int			philo_take_fork(t_philo *philo);
int			check_death_before_meal(t_philo **philo, t_struct *data, int i);
int			check_diff(t_philo **philo, t_struct *data, int i);
uint64_t	get_current_time(t_philo *philo);
t_philo		**init_each_philo(t_philo **philo, t_struct *data);

#endif
