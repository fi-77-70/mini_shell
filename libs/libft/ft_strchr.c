/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:03:33 by filferna          #+#    #+#             */
/*   Updated: 2024/12/21 01:07:33 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*temp;

	temp = (char *)str;
	if (!temp)
		return (NULL);
	while (*temp != (char)c && *temp != '\0')
		temp++;
	if (*temp == (char)c)
		return (temp);
	return (NULL);
}
/*
int main(void)
{
	const char str[] = "hello";

	char *ptr = ft_strchr(str, 'l');
	printf("%s\n", ptr);
	return (0);
}*/