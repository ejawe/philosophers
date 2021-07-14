/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 23:26:35 by ejawe             #+#    #+#             */
/*   Updated: 2021/02/23 21:30:03 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_destroy_semaphores(t_info *info)
{
	sem_close(info->sem_status);
	sem_close(info->sem_eat);
	sem_close(info->sem_fork);
	sem_close(info->sem_died);
}

int		ft_error(t_info *info, char *error_msg)
{
	write(1, error_msg, ft_strlen(error_msg));
	ft_destroy_semaphores(info);
	return (1);
}
