/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:50:43 by ecolin            #+#    #+#             */
/*   Updated: 2022/10/07 12:59:47 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_fork(t_fork *forks, int num)
{
	int		i;
	t_fork	*index;
	t_fork	*tmp;

	i = 0;
	if (!forks)
		return ;
	index = forks;
	while (index && i++ < num)
	{
		tmp = index->next;
		if (pthread_mutex_destroy(&index->mutex))
			return ;
		free(index);
		index = tmp;
	}
}

void	free_philo(t_philo *philos)
{
	t_philo	*index;
	t_philo	*tmp;

	if (!philos)
		return ;
	index = philos;
	while (index)
	{
		tmp = index->next;
		if (pthread_mutex_destroy(&index->meal_check))
			return ;
		free(index);
		index = tmp;
	}
}

void	free_table(t_info	*info)
{
	free_fork(info->forks, info->philo_num);
	free_philo(info->philo);
	if (pthread_mutex_destroy(&info->mutex))
		return ;
	free(info);
}
