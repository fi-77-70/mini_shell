/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:29:31 by filferna          #+#    #+#             */
/*   Updated: 2024/12/13 17:05:37 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static long long	ft_len(long long n)
{
	long long	len;

	len = 1;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	ft_translate(char *str, long n, long long len)
{
	long long	i;

	i = 0;
	if (n < 0)
	{
		str[i++] = '-';
		n = n * -1;
	}
	str[len--] = '\0';
	while (n > 9)
	{
		str[len--] = (n % 10) + 48;
		n = n / 10;
	}
	str[len] = (n % 10) + 48;
	return ;
}

char	*ft_itol(long long n)
{
	long long		len;
	char			*result;
	long long		i;

	i = n;
	len = ft_len(n);
	if (n < 0)
	{
		result = (char *)malloc(len * sizeof(char) + 2);
		if (!result)
			return (NULL);
		ft_translate(result, i, len + 1);
	}
	else
	{
		result = (char *)malloc(len * sizeof(char) + 1);
		if (!result)
			return (NULL);
		ft_translate(result, i, len);
	}
	return (result);
}

// long long main(long long ac, char **av)
// {
// 	(void)ac;
// 	char *result = ft_itoa(ft_atoi(av[1]));
// 	prlong longf("result: %s", result);
// 	if (result)
// 		free(result);
// 	return(0);
// }