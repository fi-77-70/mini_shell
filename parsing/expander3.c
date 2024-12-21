/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:20:48 by filferna          #+#    #+#             */
/*   Updated: 2024/12/21 15:38:21 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_other_word(char *str, int *i, int direction)
{
	int	other_word;

	other_word = 0;
	while (str[*i] && str[*i] != '|')
	{
		if (str[*i] == ' ')
			other_word = 1;
		if (other_word == 1 && ft_isalnum(str[*i]))
			other_word = 2;
		if (other_word == 2)
			break ;
		if (*i == 0)
			break ;
		*i += direction;
	}
	return (other_word);
}

int	check_pipe_exist(char *str, int i)
{
	int	j;
	int	other_word;

	j = i;
	other_word = check_other_word(str, &i, 1);
	if (str[i] && str[i] == '|')
		return (1);
	i = j;
	other_word = check_other_word(str, &i, -1);
	if (i >= 0 && str[i] && str[i] == '|')
		return (1);
	return (0);
}
