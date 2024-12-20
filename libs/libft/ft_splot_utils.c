/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splot_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:42:11 by filferna          #+#    #+#             */
/*   Updated: 2024/12/20 17:42:50 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	jump(char *str, int *j, int *i)
{
	while (str[*j] && str[*j] == ' ')
		*j += 1;
	*i = *j;
}

void	ft_quote(char *str, int *i, char sep)
{
	*i += 1;
	while (str[*i] && str[*i] != sep)
		*i += 1;
}

void	cut_words(char *str, int *i, int *j, int *word)
{
	while (str[*i])
	{
		if (str[*i] == '"')
			ft_quote(str, i, '"');
		else if (str[*i] == 39)
			ft_quote(str, i, 39);
		else if (str[*i] != ' ' && str[*i] != '|'
			&& str[*i] != '<' && str[*i] != '>'
			&& *word == 0)
		{
			*j += 1;
			*word = 1;
		}
		else if (str[*i] == ' ' || str[*i] == '|'
			|| str[*i] == '<' || str[*i] == '>')
			*word = 0;
		if (str[*i])
			*i += 1;
	}
}

void	cut_symbols(char *str, int *i, int *j)
{
	while (str[*i])
	{
		if (str[*i] == '"')
		{
			ft_quote(str, i, '"');
			*j += 1;
		}
		if (str[*i] == 39)
		{
			ft_quote(str, i, 39);
			*j += 1;
		}
		if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
			*j += 1;
		if (str[*i] && str[*i + 1] && ((str[*i + 1] == '<'
					&& str[*i] == '<') || (str[*i + 1] == '>'
					&& str[*i] == '>')))
			*i += 2;
		if (str[*i])
			*i += 1;
	}
}

int	cut_count(char *str)
{
	int	i;
	int	j;
	int	word;

	i = 0;
	j = 1;
	word = 0;
	cut_symbols(str, &i, &j);
	i = 0;
	cut_words(str, &i, &j, &word);
	return (j);
}
