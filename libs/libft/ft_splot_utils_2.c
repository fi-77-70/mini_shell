/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splot_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:44:46 by filferna          #+#    #+#             */
/*   Updated: 2024/12/20 17:45:11 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_space(char *str, int *j, int *i, char *previous)
{
	int		a;
	char	*matrix;

	a = 0;
	if ((*j >= *i || str[*j] == 0))
		return (previous);
	if (str[*i] && (str[*i + 1] == 0 && str[*i] != ' ') && str[*i] != '>'
		&& str[*i] != '<' && str[*i] != '|')
		*i += 1;
	matrix = (char *)malloc(sizeof(char) * (*i - *j) + 1);
	if (!matrix)
		return (NULL);
	while (*j < *i)
	{
		matrix[a] = str[*j];
		*j += 1;
		a++;
	}
	matrix[a] = 0;
	return (matrix);
}
