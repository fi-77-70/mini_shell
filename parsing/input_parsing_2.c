/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:21:00 by filferna          #+#    #+#             */
/*   Updated: 2024/12/21 02:21:02 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_multiple_here_doc(t_args *msh)
{
	int	check;

	while (msh->next)
	{
		check = msh->type;
		if (check == msh->next->type && check == HERE_DOC)
			return (0);
		msh = msh->next;
	}
	return (1);
}

int	check_multiple_app(t_args *msh)
{
	int	check;

	while (msh->next)
	{
		check = msh->type;
		if (check == msh->next->type && check == APP_OUT)
			return (0);
		msh = msh->next;
	}
	return (1);
}

int	check_multiple_red_out(t_args *msh)
{
	int	check;

	while (msh->next)
	{
		check = msh->type;
		if (check == msh->next->type && check == RED_OUT)
			return (0);
		msh = msh->next;
	}
	return (1);
}

int	check_multiple_red_in(t_args *msh)
{
	int	check;

	while (msh->next)
	{
		check = msh->type;
		if (check == msh->next->type && check == RED_IN)
			return (0);
		msh = msh->next;
	}
	return (1);
}

int	check_multiple_pipes(t_args *msh)
{
	int	check;

	if (msh->type == PIPE)
		return (0);
	while (msh)
	{
		check = msh->type;
		if ((!msh->next || check == msh->next->type) && check == PIPE)
			return (0);
		msh = msh->next;
	}
	return (1);
}
