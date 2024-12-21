/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:21:05 by filferna          #+#    #+#             */
/*   Updated: 2024/12/21 02:21:06 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_red_file_name(t_args *msh)
{
	int	check;

	while (msh)
	{
		check = msh->type;
		if ((check == RED_IN || check == RED_OUT || check == APP_OUT
				|| check == HERE_DOC) && (!msh->next || msh->next->type != ARG))
			return (0);
		msh = msh->next;
	}
	return (1);
}
