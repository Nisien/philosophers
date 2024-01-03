/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 03:45:54 by nrossa            #+#    #+#             */
/*   Updated: 2023/11/23 10:12:40 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (KO);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (KO);
			j++;
		}
		i++;
	}
	return (OK);
}

static void	ft_special_case(t_data *data)
{
	if (data->time[DEATH] == 0)
		printf("0 1 died\n");
	else if (data->philo_nb == 1)
	{
		printf("0 1 has taken a fork\n");
		printf("%d 1 died\n", data->time[DEATH]);
	}
}

static void	*ft_reaper(t_data *data)
{
	int	i;

	while (OK)
	{
		i = 0;
		while (i < data->philo_nb)
		{
			pthread_mutex_lock(&data->last_mutex);
			if (ft_get_time() > (data->philo_data[i].last_meal
					+ data->time[DEATH]))
			{
				ft_print_state(&data->philo_data[i], DEATH);
				pthread_mutex_lock(&data->death_mutex);
				data->death = 1;
				pthread_mutex_unlock(&data->last_mutex);
				return (pthread_mutex_unlock(&data->death_mutex), NULL);
			}
			pthread_mutex_unlock(&data->last_mutex);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!ft_check_arg(argc, argv))
		return (printf("Bad argument(s)\n"), 0);
	memset(&data, '\0', sizeof(t_data));
	if (!ft_init_data(&data, argc, argv))
		return (ft_special_case(&data), 0);
	ft_start_simulation(&data);
	ft_reaper(&data);
	i = -1;
	while (++i < data.philo_nb)
		pthread_join(data.philo[i], NULL);
	i = -1;
	while (++i < data.philo_nb)
		pthread_mutex_destroy(&data.fork[i]);
	pthread_mutex_destroy(&data.death_mutex);
	pthread_mutex_destroy(&data.meal_mutex);
	pthread_mutex_destroy(&data.last_mutex);
	pthread_mutex_destroy(&data.print);
	free(data.philo);
	free(data.philo_data);
	free(data.fork);
	return (0);
}
