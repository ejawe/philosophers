/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 22:09:37 by ejawe             #+#    #+#             */
/*   Updated: 2021/02/23 22:27:44 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_lock_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->eating);
	ft_print_status(philo, "died");
	philo->info->is_dead = 1;
	pthread_mutex_unlock(&philo->info->eating);
}

void	*ft_death(void *rphilo)
{
	t_philo *philo;

	philo = rphilo;
	while (!philo->info->is_dead)
	{
		pthread_mutex_lock(&philo->info->died);
		if (!philo->info->is_dead &&
				(ft_gettime() - philo->start_meal) > philo->info->die_time)
		{
			if (philo->info->must_eat_time > 0 &&
					philo->must_eat_count >= philo->info->must_eat_time)
			{
				pthread_mutex_unlock(&philo->info->died);
				return (NULL);
			}
			ft_lock_death(philo);
			pthread_mutex_unlock(&philo->info->died);
			return (NULL);
		}
		usleep(100);
		pthread_mutex_unlock(&philo->info->died);
	}
	return (NULL);
}

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->eating);
	ft_print_status(philo, "is eating");
	philo->start_meal = ft_gettime();
	philo->must_eat_count = philo->must_eat_count + 1;
	usleep(100);
	pthread_mutex_unlock(&philo->info->eating);
}

void	ft_eat(t_philo *philo)
{
	if (philo->info->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->info->lock_forks[(philo->index + 1)
				% philo->info->nb_philo]);
		ft_print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->info->lock_forks[philo->index]);
		ft_print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->info->lock_forks[philo->index]);
		ft_print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->info->lock_forks[(philo->index + 1)
				% philo->info->nb_philo]);
		ft_print_status(philo, "has taken a fork");
	}
	ft_eating(philo);
	usleep(philo->info->eat_time * 1000);
	pthread_mutex_unlock(&philo->info->lock_forks[philo->index]);
	pthread_mutex_unlock(&philo->info->lock_forks[(philo->index + 1)
			% philo->info->nb_philo]);
}

void	*ft_routine(void *rphilo)
{
	t_philo *philo;

	philo = rphilo;
	philo->start_meal = ft_gettime();
	while (!philo->info->is_dead)
	{
		ft_eat(philo);
		if (philo->info->is_dead || (philo->info->must_eat_time > 0 &&
					philo->must_eat_count >= philo->info->must_eat_time))
			return (NULL);
		if (!philo->info->is_dead)
			ft_print_status(philo, "is sleeping");
		usleep(philo->info->sleep_time * 1000);
		if (!philo->info->is_dead)
			ft_print_status(philo, "is thinking");
	}
	return (NULL);
}
