/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:52:19 by elise             #+#    #+#             */
/*   Updated: 2022/10/10 13:51:49 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long int	timestamp(void)
{
	static int				i;
	static struct timeval	start;
	struct timeval			time;

	if (!i)
	{
		gettimeofday(&start, 0);
		i++;
	}
	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000)
		- (start.tv_sec * 1000 + start.tv_usec / 1000));
}

void	locked_print(t_info *info, int id, char *statement)
{
	pthread_mutex_lock(&info->mutex);
	if (!info->corpses)
		printf("%ld %d %s\n", timestamp(), id, statement);
	pthread_mutex_unlock(&info->mutex);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argc > 6 || argc < 5)
		return (0);
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j++]))
				return (0);
		}
	}
	return (1);
}

void	get_sleep(int sleep, t_info *info)
{
	int long long	start;

	start = timestamp();
	while (timestamp() - start <= sleep)
	{
		pthread_mutex_lock(&info->mutex);
		if (info->corpses)
		{
			pthread_mutex_unlock(&info->mutex);
			return ;
		}
		pthread_mutex_unlock(&info->mutex);
		usleep(500);
	}
}
