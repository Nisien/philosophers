/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_simulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 01:37:32 by nrossa            #+#    #+#             */
/*   Updated: 2023/12/21 21:24:10 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_check_meal(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_mutex);
	if (philo->meal_nb != -1)
		philo->meal_nb--;
	pthread_mutex_unlock(philo->meal_mutex);
}

static void	*ft_philo_loop(t_philo *philo,
	pthread_mutex_t *first, pthread_mutex_t *second)
{
	while (philo->meal_nb)
	{
		pthread_mutex_lock(philo->death_mutex);
		if (*philo->death)
			return (pthread_mutex_unlock(philo->death_mutex), NULL);
		pthread_mutex_unlock(philo->death_mutex);
		pthread_mutex_lock(first);
		ft_print_state(philo, FORK);
		pthread_mutex_lock(second);
		ft_print_state(philo, FORK);
		ft_print_state(philo, EAT);
		pthread_mutex_lock(philo->last_mutex);
		philo->last_meal = ft_get_time();
		pthread_mutex_unlock(philo->last_mutex);
		ft_check_meal(philo);
		ft_msleep(philo->time[EAT]);
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		ft_print_state(philo, SLEEP);
		ft_msleep(philo->time[SLEEP]);
		ft_print_state(philo, THINKING);
	}
	return (NULL);
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->print);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->last_mutex);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(philo->last_mutex);
	if (philo->id % 2)
	{
		ft_print_state(philo, THINKING);
		ft_msleep(philo->time[EAT] / 2);
	}
	ft_philo_loop(philo, philo->fork[RIGHT], philo->fork[LEFT]);
	return (NULL);
}

void	ft_start_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(pthread_t) * data->philo_nb);
	if (!data->philo)
		return ;
	pthread_mutex_lock(&data->print);
	while (i < data->philo_nb)
	{
		pthread_create(&data->philo[i], NULL,
			&ft_philo_routine, (void *)&data->philo_data[i]);
		i++;
	}
	pthread_mutex_unlock(&data->print);
}
