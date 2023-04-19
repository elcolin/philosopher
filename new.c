/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:01:37 by ecolin            #+#    #+#             */
/*   Updated: 2022/10/10 13:39:49 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_info	*juicy_infos(char **argv, int argc)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		exit(EXIT_FAILURE);
	info->philo_num = ft_atoi(argv[1]);
	if (!info->philo_num || info->philo_num > 200)
		return (info->philo_num = 0, info);
	info->die = ft_atoi(argv[2]);
	info->eat = ft_atoi(argv[3]);
	info->sleep = ft_atoi(argv[4]);
	info->corpses = 0;
	info->all_ate = 0;
	if (pthread_mutex_init(&info->mutex, 0))
		return (info->philo_num = 0, info);
	if (argc == 6)
		info->meals_num = ft_atoi(argv[5]);
	else
		info->meals_num = -1;
	return (info);
}

t_philo	*new_philo(int id, t_fork *left, t_fork *right, t_info *info)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new || pthread_mutex_init(&new->meal_check, 0))
		return (0);
	new->id = id;
	new->next = 0;
	new->left = left;
	new->right = right;
	new->info = info;
	new->last_meal = 0;
	new->meals_left = new->info->meals_num;
	return (new);
}

t_philo	*philo_party(int num, t_fork *forks, t_info *info)
{
	int		i;
	t_philo	*new;
	t_philo	*index;
	t_fork	*f_in;

	i = 2;
	new = new_philo(1, 0, forks, info);
	if (!new)
		return (0);
	f_in = forks;
	index = new;
	while (i <= num)
	{
		index->next = new_philo(i++, f_in, f_in->next, info);
		if (!index->next)
			return (free_philo(new), new = 0);
		index = index->next;
		f_in = f_in->next;
	}
	new->left = f_in;
	return (new);
}

t_fork	*new_fork(int id)
{
	t_fork	*new;

	new = malloc(sizeof(t_fork));
	if (!new || pthread_mutex_init(&new->mutex, 0))
		return (0);
	new->id = id;
	new->next = 0;
	return (new);
}

t_fork	*set_the_forks(int num)
{
	int		i;
	t_fork	*new;
	t_fork	*index;

	i = 1;
	new = new_fork(0);
	if (!new)
		return (0);
	index = new;
	while (i < num)
	{
		index->next = new_fork(i++);
		if (!index->next)
			return (free_fork(new, num), new = 0);
		index = index->next;
	}
	index->next = new;
	return (new);
}
