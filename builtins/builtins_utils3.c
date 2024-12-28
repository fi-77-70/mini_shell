/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:16:02 by filferna          #+#    #+#             */
/*   Updated: 2024/12/28 15:11:09 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_sig(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	menu()->return_code = 130;
	rl_on_new_line();
}

char	*ft_strjoin_exp(const char *s1, char c, const char *s2)
{
	char	*result;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 2);
	if (ft_strchr(s1, '+'))
		len1--;
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	if (!ft_strchr(s1, '='))
		result[len1] = c;
	else
		len1 -= 1;
	ft_memcpy(result + len1 + 1, s2, len2);
	result[len1 + len2 + 1] = '\0';
	return (free((char *)s1), result);
}
