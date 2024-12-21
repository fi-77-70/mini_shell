/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:55:53 by pmachado          #+#    #+#             */
/*   Updated: 2024/12/20 23:19:01 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_menu(t_menu *menu)
{
	if (!menu->line[0])
	{
		free(menu->mshh);
		free(menu->line);
		return (0);
	}
	*(menu->mshh) = lexer(menu->mshh, menu->line, menu);
	free_line(menu->line);
	return (1);
}

int	main_exe(t_menu *menu)
{
	menu->cmds = ft_cmd_div(*(menu->mshh));
	menu->first_cmd = menu->cmds;
	if (!ft_here_doc(menu))
	{
		free_all(menu);
		return (0);
	}
	process_handler(menu);
	if (menu->pid_arr)
		wait_for_process(menu);
	return (1);
}

int	loop_check(t_menu *menu)
{
	if (!main_menu(menu))
		return (0);
	if (ft_input_check(menu->mshh))
	{
		if (!main_exe(menu))
			return (0);
	}
	else
		return (free_list(menu->mshh), 0);
	return (1);
}

int	mini_loop(t_menu *menu)
{
	int		exit_code;
	char	*str;

	exit_code = 0;
	while (1)
	{
		signal(SIGINT, handle_sigint);
		exit_code = menu->return_code;
		str = readline("minishell: ");
		if (!str)
			return (printf("exit\n"), free_line(menu->env), free(menu),
				exit_code);
		add_history(str);
		str = ft_expand(str, menu);
		menu->line = ft_splot(str);
		free(str);
		menu->mshh = (t_args **)malloc(sizeof(t_args *));
		if (!loop_check(menu))
			continue ;
		if (!menu->cmds)
			menu->cmds = ft_cmd_div(*(menu->mshh));
		free_all(menu);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_menu	*menu;

	(void)ac;
	(void)av;
	menu = NULL;
	init_struct(&menu, envp);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	mini_loop(menu);
}
