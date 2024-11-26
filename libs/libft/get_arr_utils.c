/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:20:13 by filferna          #+#    #+#             */
/*   Updated: 2024/09/23 14:29:21 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_lines(char *buf, char *stash)
{
	if (buf)
		free(buf);
	if (stash)
		free(stash);
}

int	ft_strclen(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i + 1);
	return (i + 1);
}
