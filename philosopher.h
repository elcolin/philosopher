/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:09:47 by ecolin            #+#    #+#             */
/*   Updated: 2022/10/10 12:59:46 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>

typedef struct s_fork{
	int				id;
	pthread_mutex_t	mutex;
	struct s_fork	*next;
}	t_fork;

typedef struct s_philo{
	int				id;
	pthread_t		thread;
	struct s_philo	*next;
	pthread_mutex_t	meal_check;
	long int		last_meal;
	int				meals_left;
	t_fork			*left;
	t_fork			*right;
	struct s_info	*info;
}	t_philo;

typedef struct s_info{
	t_fork			*forks;
	t_philo			*philo;
	pthread_t		grim_reaper;
	int				all_ate;
	int				corpses;
	int				philo_num;
	int				die;
	int				sleep;
	int				eat;
	int				meals_num;
	pthread_mutex_t	mutex;
}	t_info;

t_info			*juicy_infos(char **argv, int argc);
t_philo			*philo_party(int num, t_fork *forks, t_info *info);
t_fork			*set_the_forks(int num);
long int		timestamp(void);
void			locked_print(t_info *info, int id, char *statement);
int				ft_atoi(const char *nptr);
int				ft_isdigit(int c);
void			free_philo(t_philo *philos);
void			free_fork(t_fork *forks, int num);
int				check_args(int argc, char **argv);
void			free_table(t_info	*info);
void			get_sleep(int sleep, t_info *info);

#endif