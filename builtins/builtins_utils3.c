/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:16:02 by filferna          #+#    #+#             */
/*   Updated: 2024/12/21 15:57:11 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_sig(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

char	*ft_strjoin_exp(char *env, char *value)
{
	int		len;
	int		j;
	int		i;
	int		jumped;
	char	*new;

	len = ft_strlen(env) + ft_strlen(value);
	new = (char *)malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	len = 0;
	jumped = 0;
	j = 0;
	i = 0;
	while (env[len])
	{
		if (env[len] && (env[len] != '+' || jumped))
			new[j++] = env[len++];
		if (env[len] && env[len] == '+')
			jumped = 1;
		if (!env[len])
			while (value[i])
				new[j++] = value[i++];
	}
	return (free(env), new[j] = 0, new);
}
