/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 05:25:47 by nrossa            #+#    #+#             */
/*   Updated: 2023/11/23 10:13:16 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_give_fork(t_data *data)
{
	int	i;
	int	nb;

	i = 0;
	nb = data->philo_nb;
	while (i < nb)
	{
		if (i == 0)
		{
			data->philo_data[i].fork[LEFT] = &data->fork[nb - 1];
			data->philo_data[i].fork[RIGHT] = &data->fork[0];
		}
		else
		{
			data->philo_data[i].fork[LEFT] = &data->fork[i - 1];
			data->philo_data[i].fork[RIGHT] = &data->fork[i];
		}
		i++;
	}
}

static int	ft_get_fork_data(t_data	*data)
{
	int	i;

	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->fork)
		return (KO);
	memset(data->fork, '\0', sizeof(pthread_mutex_t) * data->philo_nb);
	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	return (OK);
}

static int	ft_get_philo_data(t_data *data)
{
	int	i;

	data->philo_data = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philo_data)
		return (KO);
	memset(data->philo_data, '\0', sizeof(t_philo) * data->philo_nb);
	i = 0;
	while (i < data->philo_nb)
	{
		data->philo_data[i].id = i + 1;
		data->philo_data[i].time[DEATH] = data->time[DEATH];
		data->philo_data[i].time[EAT] = data->time[EAT];
		data->philo_data[i].time[SLEEP] = data->time[SLEEP];
		data->philo_data[i].meal_nb = data->meal_nb;
		data->philo_data[i].start_time = data->start_time;
		data->philo_data[i].death = &data->death;
		data->philo_data[i].print = &data->print;
		data->philo_data[i].meal_mutex = &data->meal_mutex;
		data->philo_data[i].last_mutex = &data->last_mutex;
		data->philo_data[i].death_mutex = &data->death_mutex;
		i++;
	}
	return (OK);
}

static int	ft_get_data(t_data *data, int argc, char **argv)
{
	data->time[DEATH] = ft_atoi(argv[2]);
	data->time[EAT] = ft_atoi(argv[3]);
	data->time[SLEEP] = ft_atoi(argv[4]);
	data->philo_nb = ft_atoi(argv[1]);
	if (argc == 5)
		data->meal_nb = -1;
	else if (argc == 6)
		data->meal_nb = ft_atoi(argv[5]);
	data->start_time = ft_get_time();
	data->death = 0;
	return (OK);
}

int	ft_init_data(t_data *data, int argc, char **argv)
{
	ft_get_data(data, argc, argv);
	if (data->time[DEATH] == 0 || data->philo_nb == 1)
		return (KO);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->last_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	ft_get_philo_data(data);
	ft_get_fork_data(data);
	ft_give_fork(data);
	return (OK);
}
