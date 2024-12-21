#include "../minishell.h"

int	take_len(char *str, char out)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == out)
		{
			len = len - 1;
			i++;
		}
		if (str[i])
			i++;
	}
	return (len);
}

char	*ft_take_out_back(char *str, char out)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = take_len(str, out);
	new = (char *)malloc((sizeof(char) * len) + 1);
	i = 0;
	len = 0;
	while (str[len])
	{
		if (str[len] == out)
			len++;
		if (str[len])
			new[i++] = str[len];
		if (str[len])
			len++;
	}
	new[i] = 0;
	return (free(str), new);
}

int	ft_here_loop_2(t_cmds *cmd, t_menu *menu)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input && !ft_static(1))
			input = cmd->redir->token;
		if (!input && ft_static(1))
		{
			ft_static(3);
			close(cmd->here_fds[1]);
			close(cmd->here_fds[0]);
			return (dup2(menu->fd_in, STDIN_FILENO), 0);
		}
		if (!ft_strcmp(input, cmd->redir->token))
		{
			cmd->redir = cmd->redir->next;
			return (1);
		}
		else
		{
			put_str_fd(input, cmd->here_fds[1]);
		}
	}
	return (1);
}

int	ft_here_loop(t_cmds *cmds, t_menu *menu)
{
	char	*input;
	t_cmds	*cmd;
	t_args	*first_redir;

	cmd = cmds;
	first_redir = cmd->redir;
	input = NULL;
	signal(SIGINT, signal_handle);
	while (cmd->redir)
	{
		while (cmd->redir && cmd->redir->type == HERE_DOC)
		{
			pipe(cmd->here_fds);
			if (!ft_here_loop_2(cmd, menu))
				return (0);
			close(cmd->here_fds[1]);
		}
		if (cmd->redir && cmd->redir->type != HERE_DOC)
			cmd->redir = cmd->redir->next;
	}
	cmd->redir = first_redir;
	return (1);
}

int	ft_here_doc(t_menu *menu)
{
	int		result;
	t_cmds	*cmds;
	t_cmds	*first_node;

	cmds = NULL;
	result = 1;
	if (menu->cmds)
	{
		cmds = *menu->cmds;
		first_node = *menu->cmds;
	}
	while (cmds)
	{
		if (cmds->redir)
			result = ft_here_loop(cmds, menu);
		if (!result)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			return (0);
		}
		cmds = cmds->next;
	}
	*menu->cmds = first_node;
	return (1);
}
