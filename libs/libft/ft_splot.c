/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:38:58 by filferna          #+#    #+#             */
/*   Updated: 2024/11/28 14:12:45 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	jump(char *str, int *j, int *i)
{
	while (str[*j] && str[*j] == ' ')
		*j += 1;
	*i = *j;
}

void	ft_quote(char *str, int *i, char sep)
{
	*i += 1;
	while(str[*i] && str[*i] != sep)
		*i += 1;
}

int	cut_count(char *str)
{
	int	i;
	int	j;
	int	word;
	
	i = 0;
	j = 1;
	word = 0;
// While to count symbols
	while (str[i])
	{
		if (str[i] == '"')
			ft_quote(str, &i, '"');
		if (str[i] == 39)
			ft_quote(str, &i, 39);
		if (str[i] == '<' || str[i] == '>' || str[i] == '|')
			j++;
		if ((str[i + 1] == '<' && str[i] == '<') || (str[i + 1] == '>' && str[i] == '>'))
	 	 	i += 2;
		else
			i++;
	}
	i = 0;
// while to count words
	while (str[i])
	{
		if (str[i] == '"')
			ft_quote(str, &i, '"');
		if (str[i] == 39)
			ft_quote(str, &i, 39);
		if (str[i] != ' ' && str[i] != '|' && str[i] != '<' && str[i] != '>' && word == 0)
		{
			j++;
			word = 1;
		}
		if (str[i] == ' ' || str[i] == '|' || str[i] == '<' || str[i] == '>')
			word = 0;
		i++;
	}
	// printf("token number ----->>> [%d]\n", j);
	return (j);
}

char	*ft_space(char *str, int *j, int *i, char *previous)
{
	int		a;
	char	*matrix;

	a = 0;
	if ((*j >= *i || str[*j] == 0))
		return (previous);
	if (str[*i] && (str[*i + 1] == 0 && str[*i] != ' ') && str[*i] != '>' && str[*i] != '<' && str[*i] != '|')
		*i += 1;
	matrix = (char *)malloc(sizeof(char) * (*i - *j) + 1);
	if(!matrix)
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
void		check_symbol(char *str, int *j, int *i, char **matrix, int *a)
{
	if (str[*i] == ' ' || (str[*i] != '|' && str[*i] != '<' && str[*i] != '>'))
		return ;
	if (*(str + *j + 1) && (!ft_strncmp(str + *j, ">>", 2) || !ft_strncmp(str + *j, "<<", 2)))
	{
		if (*i != *j)
			*i = *j;
		*i += 2;
		if (!ft_strncmp(str + *j, ">>", 2))
			matrix[*a] = ft_strdup(">>");
		else
			matrix[*a] = ft_strdup("<<");
		*j += 2;
		*a += 1;
		check_symbol(str, j, i, matrix, a);
	}
	else if (!ft_strncmp(str + *j, "<", 1) || !ft_strncmp(str + *j, ">", 1))
	{
		if (*i != *j)
			*i = *j;
		*i += 1;
		if (!ft_strncmp(str + *j, "<", 1))
			matrix[*a] = ft_strdup("<");
		else
			matrix[*a] = ft_strdup(">");
		*j += 1;
		*a += 1;
		check_symbol(str, j, i, matrix, a);
	}
	else if (str[*i] == '|')
		while (str[*i] == '|')
		{
			matrix[*a] = ft_strdup("|");
			*i += 1;
			*j += 1;
			*a += 1;
		}
}

char	**ft_splot(char *str)
{
	char	**matrix;
	int		i;
	int		j;
	int		a;

	matrix = (char **)malloc(sizeof(char *) * (cut_count(str) + 2));
	if (!matrix)
		return (NULL);
	i = 0;
	j = 0;
	a = 0;
	while(str[i++])
	{
		if(i == 1)
			i = 0;
		if (str[j] == ' ')
			jump(str, &j, &i);
		if (str[i] == 39)
			ft_quote(str, &i, 39);
		if (str[i] == '"')
			ft_quote(str, &i, '"');
		if (str[i] == ' ' || str[i] == '|' || str[i] == 0 || str[i] == '<' || str[i] == '>')
		{
			if((i == 0 || i != j) && str[j] != '|' && str[j] != '>' && str[j] != '<')
			{
				if (i == 0)
					i++;
				matrix[a] = ft_space(str, &j, &i, matrix[a]);
				a++;
			}
			check_symbol(str, &j, &i, matrix, &a);
		}
		if (str[i] == 0)
			break ;
		if (i == 0)
			i = 1;
	}
	matrix[a] = NULL;
	return (matrix);
}
