/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:42:36 by pmachado          #+#    #+#             */
/*   Updated: 2024/12/23 11:54:44 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	symbol_utils_2(char *str, t_counter *ct, char **matrix, int *a)
{
	int	*i;
	int	*j;

	i = &ct->i;
	j = &ct->j;
	if (*i != *j)
		*i = *j;
	if (!ft_strncmp(str + *j, "<", 1))
		matrix[*a] = ft_strdup("<");
	else
		matrix[*a] = ft_strdup(">");
	*j += 1;
	*a += 1;
	check_symbol(str, ct, matrix, a);
}

void	symbol_utils(char *str, t_counter *ct, char **matrix, int *a)
{
	int	*i;
	int	*j;

	i = &ct->i;
	j = &ct->j;
	if (*i != *j)
		*i = *j;
	*i += 2;
	if (!ft_strncmp(str + *j, ">>", 2))
		matrix[*a] = ft_strdup(">>");
	else
		matrix[*a] = ft_strdup("<<");
	*j += 2;
	*a += 1;
	check_symbol(str, ct, matrix, a);
}

void	check_symbol(char *str, t_counter *ct, char **matrix, int *a)
{
	int	*i;
	int	*j;

	i = &ct->i;
	j = &ct->j;
	if (str[*i] == ' ' || (str[*i] != '|' && str[*i] != '<' && str[*i] != '>'))
		return ;
	if (str[*j] && str[*j + 1]
		&& (!ft_strncmp(str + *j, ">>", 2) || !ft_strncmp(str
				+ *j, "<<", 2)))
		symbol_utils(str, ct, matrix, a);
	else if (!ft_strncmp(str + *j, "<", 1) || !ft_strncmp(str + *j, ">", 1))
		symbol_utils_2(str, ct, matrix, a);
	else if (str[*i] == '|')
	{
		while (str[*i] == '|')
		{
			matrix[*a] = ft_strdup("|");
			*i += 1;
			*j += 1;
			*a += 1;
		}
	}
}

void	ft_splot_2(t_counter *ct, char **matrix, char *str)
{
	if (str[ct->j] == ' ')
		jump(str, &ct->j, &ct->i);
	if (str[ct->i] == 39)
		ft_quote(str, &ct->i, 39);
	if (str[ct->i] == '"')
		ft_quote(str, &ct->i, '"');
	if (str[ct->i] == ' ' || str[ct->i] == '|' || str[ct->i] == 0
		|| str[ct->i] == '<' || str[ct->i] == '>')
	{
		if ((ct->i == 0 || ct->i != ct->j) && str[ct->j] != '|'
			&& str[ct->j] != '>' && str[ct->j] != '<')
		{
			if (ct->i == 0)
				ct->i++;
			matrix[ct->a] = ft_space(str, &ct->j, &ct->i, matrix[ct->a]);
			ct->a++;
		}
		check_symbol(str, ct, matrix, &ct->a);
		if (str[ct->i] && ct->i > 0 && (str[ct->i] == '"' || str[ct->i] == 39))
			ct->i--;
	}
}

char	**ft_splot(char *str)
{
	char		**matrix;
	t_counter	*ct;
	int			yes;

	ct = (t_counter *)malloc(sizeof(t_counter));
	ct->i = 0;
	ct->j = 0;
	ct->a = 0;
	matrix = (char **)malloc(sizeof(char *) * (cut_count(str)) + 1);
	if (!matrix)
		return (NULL);
	yes = 0;
	while (str[ct->i++])
	{
		if (ct->i == 1 && !yes)
		{
			yes = 1;
			ct->i = 0;
		}
		ft_splot_2(ct, matrix, str);
		if (str[ct->i] == 0)
			break ;
	}
	matrix[ct->a] = NULL;
	return (free(ct), matrix);
}
