/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:21:09 by filferna          #+#    #+#             */
/*   Updated: 2024/12/21 02:21:11 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unquote_3(t_args *temp, char *final, int *a, char *quote)
{
	int	i;

	i = 0;
	while (temp->token[i])
	{
		while (temp->token[i] && temp->token[i] != 39 && temp->token[i] != '"')
		{
			final[*a] = temp->token[i];
			*a += 1;
			i++;
		}
		if (temp->token[i] && (i == 0 || (temp->token[i - 1] && temp->token[i
						- 1] != 92)))
		{
			*quote = temp->token[i];
			i++;
		}
		while (temp->token[i] != *quote && temp->token[i])
		{
			final[*a] = temp->token[i++];
			*a += 1;
		}
		if (temp->token[i])
			i++;
	}
}

void	ft_unquote_two(t_args **msh, int length)
{
	char	*final;
	char	quote;
	int		i;
	int		a;
	t_args	*temp;

	i = 0;
	a = 0;
	temp = *msh;
	final = (char *)malloc(sizeof(char) * length + 1);
	quote = temp->token[i];
	ft_unquote_3(temp, final, &a, &quote);
	final[a] = 0;
	free((*msh)->token);
	(*msh)->token = final;
}

int	ft_unquote(t_args **msh)
{
	char	quote;
	int		i;
	int		length;
	int		n;
	t_args	*temp;

	temp = *msh;
	i = -1;
	n = 0;
	while (temp->token[++i])
	{
		if ((temp->token[i] == 39 || temp->token[i] == '"') && (i == 0
				|| (temp->token[i - 1] && temp->token[i - 1] != 92)))
		{
			quote = temp->token[i];
			n += 2;
			i++;
			while (temp->token[i] != quote && temp->token[i])
				i++;
			if (temp->token[i] != quote)
				return (0);
		}
	}
	length = ft_strlen(temp->token) - n;
	return (ft_unquote_two(msh, length), 2);
}

int	ft_check_quotes(t_args **mshh)
{
	int		zero;
	int		check;
	t_args	*msh;

	zero = -1;
	check = 1;
	msh = *mshh;
	while ((*mshh))
	{
		while ((*mshh)->token[++zero])
		{
			if ((*mshh)->token[zero] == '"' || (*mshh)->token[zero] == 39)
				check = ft_unquote(&(*mshh));
			if (!check)
				return ((*mshh) = msh, 0);
			else if (check == 2)
				break ;
		}
		check = 1;
		zero = -1;
		(*mshh)->token = ft_take_out_back((*mshh)->token, 92);
		(*mshh) = (*mshh)->next;
	}
	return ((*mshh) = msh, 1);
}

int	ft_input_check(t_args **mshh)
{
	t_args	*msh;

	msh = *mshh;
	if (!check_multiple_pipes(msh))
		return (wem("Error: sequential pipes\n"), 0);
	if (!check_red_file_name(msh))
		return (wem("Error: redirect file name missing\n"), 0);
	if (!check_multiple_red_in(msh))
		return (wem("Error: sequential redirections\n"), 0);
	if (!check_multiple_red_out(msh))
		return (wem("Error: sequential redirections\n"), 0);
	if (!check_multiple_here_doc(msh))
		return (wem("Error: sequential here docs\n"), 0);
	if (!check_multiple_app(msh))
		return (wem("Error: sequential redirections\n"), 0);
	if (!ft_check_quotes(mshh))
		return (wem("Error: unclosed quotes\n"), 0);
	return (1);
}
