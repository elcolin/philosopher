/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:04:55 by ecolin            #+#    #+#             */
/*   Updated: 2022/10/10 14:49:14 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->right->mutex);
	locked_print(philo->info, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->left->mutex);
	locked_print(philo->info, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->meal_check);
	philo->last_meal = timestamp();
	if (philo->meals_left > 0)
		philo->meals_left--;
	pthread_mutex_unlock(&philo->meal_check);
	locked_print(philo->info, philo->id, "is eating");
	get_sleep(philo->info->eat, philo->info);
	pthread_mutex_unlock(&philo->right->mutex);
	pthread_mutex_unlock(&philo->left->mutex);
}

void	routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->mutex);
	pthread_mutex_unlock(&philo->info->mutex);
	if (philo->id % 2)
		usleep(1000);
	pthread_mutex_lock(&philo->info->mutex);
	while (!philo->info->corpses && philo->meals_left)
	{
		pthread_mutex_unlock(&philo->info->mutex);
		locked_print(philo->info, philo->id, "is thinking");
		is_eating(philo);
		locked_print(philo->info, philo->id, "is sleeping");
		get_sleep(philo->info->sleep, philo->info);
		pthread_mutex_lock(&philo->info->mutex);
	}
	philo->info->all_ate++;
	pthread_mutex_unlock(&philo->info->mutex);
}

void	is_he_dead(t_info *info)
{
	t_philo	*index;

	while (info->all_ate != info->philo_num && !info->corpses)
	{
		pthread_mutex_unlock(&info->mutex);
		index = info->philo;
		while (index)
		{
			pthread_mutex_lock(&index->meal_check);
			if (timestamp() - index->last_meal >= info->die
				&& index->meals_left != 0)
			{
				pthread_mutex_lock(&info->mutex);
				info->corpses = 1;
				printf("%ld %d has died\n", timestamp(), index->id);
				pthread_mutex_unlock(&index->meal_check);
				return ;
			}
			pthread_mutex_unlock(&index->meal_check);
			index = index->next;
		}
		pthread_mutex_lock(&info->mutex);
	}
}

void	thread_launcher(t_info *info)
{
	t_philo	*index;

	index = info->philo;
	pthread_mutex_lock(&info->mutex);
	while (index)
	{
		if (pthread_create(&index->thread, 0, (void *) &routine, index))
			return ;
		index = index->next;
	}
	pthread_mutex_unlock(&info->mutex);
	usleep(1000);
	pthread_mutex_lock(&info->mutex);
	is_he_dead(info);
	pthread_mutex_unlock(&info->mutex);
	index = info->philo;
	while (index)
	{
		if (pthread_join(index->thread, 0))
			return ;
		index = index->next;
	}
}

int	main(int argc, char *argv[])
{
	t_info	*info;

	if (!check_args(argc, argv))
		return (0);
	info = juicy_infos(argv, argc);
	if (info->philo_num <= 1)
	{
		if (info->philo_num == 1)
			printf("%ld %d has died\n", timestamp(), 1);
		return (free(info), 0);
	}
	info->forks = set_the_forks(info->philo_num);
	if (!info->forks)
		return (free(info), 0);
	info->philo = philo_party(info->philo_num, info->forks, info);
	if (!info->philo)
		return (free_fork(info->forks, info->philo_num), free(info), 0);
	thread_launcher(info);
	free_table(info);
}
