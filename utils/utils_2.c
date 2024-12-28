/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:16:38 by filferna          #+#    #+#             */
/*   Updated: 2024/12/27 17:22:20 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_atoll(char *str)
{
	long long	result;
	int			sign;

	if (!ft_strcmp(str, "-9223372036854775808"))
		return (LLONG_MIN);
	result = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return (result * sign);
}

void	put_str_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
	write(fd, "\n", 1);
}

int	ft_static(int sig)
{
	static int	i;

	if (sig == SIGINT)
		i = 1;
	else if (sig == 3)
		i = 0;
	return (i);
}

void	signal_handle(int sig)
{
	if (sig == SIGINT)
	{
		ft_static(SIGINT);
		rl_replace_line("", 0);
		printf("^C");
		menu()->return_code = 130;
		close(STDIN_FILENO);
	}
	else
		return ;
}
