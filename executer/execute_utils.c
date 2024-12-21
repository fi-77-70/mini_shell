/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:20:10 by filferna          #+#    #+#             */
/*   Updated: 2024/12/21 02:20:11 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_command_path(t_cmds *cmds, t_menu *menu)
{
	char	**possible_paths;
	char	*path;
	int		i;

	i = 0;
	possible_paths = NULL;
	path = env_get("PATH", menu);
	possible_paths = ft_split(path, ':');
	free(path);
	while (possible_paths && possible_paths[i])
	{
		path = ft_strjoin(possible_paths[i++], "/");
		path = ft_strjoin_free(path, cmds->cmd);
		if (!access(path, F_OK))
		{
			ft_free_matrix(possible_paths);
			return (path);
		}
		free(path);
	}
	ft_free_matrix(possible_paths);
	wem(cmds->cmd);
	wem(": command not found\n");
	free_mid_process(menu);
	exit(127);
}
