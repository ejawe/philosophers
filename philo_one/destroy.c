/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:03:06 by ejawe             #+#    #+#             */
/*   Updated: 2021/02/23 21:40:21 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_destroy_mutex(t_info *info)
{
	int i;

	i = 0;
	if (info->lock_forks)
	{
		while (i < info->nb_philo)
		{
			pthread_mutex_destroy(&info->lock_forks[i]);
			i++;
		}
		free(info->lock_forks);
	}
	if (info)
	{
		pthread_mutex_destroy(&info->status);
		pthread_mutex_destroy(&info->died);
		pthread_mutex_destroy(&info->eating);
	}
}

int		ft_error(t_info *info, char *error_msg)
{
	write(1, error_msg, ft_strlen(error_msg));
	ft_destroy_mutex(info);
	return (1);
}
