/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 00:25:16 by nrossa            #+#    #+#             */
/*   Updated: 2023/11/23 10:08:55 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (OK);
	return (KO);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	symbol;
	int	nb;

	i = 0;
	symbol = 1;
	nb = 0;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			symbol *= -1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	nb *= symbol;
	return (nb);
}

int	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_msleep(int mls)
{
	int	time;

	time = ft_get_time();
	usleep(mls * 900);
	while (ft_get_time() < time + mls)
		usleep(mls * 5);
}

void	*ft_print_state(t_philo *philo, int state)
{
	int	time;

	pthread_mutex_lock(philo->meal_mutex);
	if (philo->meal_nb == 0)
		return (pthread_mutex_unlock(philo->meal_mutex), NULL);
	pthread_mutex_unlock(philo->meal_mutex);
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->death)
		return (pthread_mutex_unlock(philo->death_mutex), NULL);
	pthread_mutex_unlock(philo->death_mutex);
	pthread_mutex_lock(philo->print);
	time = ft_get_time() - philo->start_time;
	if (state == FORK)
		printf("%d %d has taken a fork\n", time, philo->id);
	else if (state == EAT)
		printf("%d %d is eating\n", time, philo->id);
	else if (state == SLEEP)
		printf("%d %d is sleeping\n", time, philo->id);
	else if (state == THINKING)
		printf("%d %d is thinking\n", time, philo->id);
	else if (state == DEATH)
		printf("%d %d died\n", time, philo->id);
	pthread_mutex_unlock(philo->print);
	return (NULL);
}
