#include "../minishell.h"

unsigned long long ft_atoll(char *str)
{
	long long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return (result * sign);
}

void put_str_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
	write(fd, "\n", 1);
}

void ft_here_loop(t_cmds *cmds)
{
	char	*input;
	t_cmds *cmd;
	t_args	*first_redir;

	cmd = cmds;
	first_redir = cmd->redir;
	input = NULL;
	while (cmd->redir)
	{
		while (cmd->redir && cmd->redir->type == HERE_DOC)
		{
			pipe(cmd->here_fds);
			while(1)
			{
				input = readline("> ");
				if (!ft_strcmp(input, cmd->redir->token))
				{
					cmd->redir = cmd->redir->next;
					break ;
				}
				else
				{
					put_str_fd(input, cmd->here_fds[1]);
				}
			}
			close(cmd->here_fds[1]);
		}
		if(cmd->redir && cmd->redir->type != HERE_DOC)
			cmd->redir = cmd->redir->next;
	}
	cmd->redir = first_redir;
}

void ft_here_doc(t_menu *menu)
{
	t_cmds	*cmds;
	t_cmds	*first_node;

	cmds = NULL;
	if(menu->cmds)
	{
		cmds = *menu->cmds;
		first_node = *menu->cmds;
	}
	while(cmds)
	{
		if (cmds->redir)
			ft_here_loop(cmds);
		cmds = cmds->next;
	}
	*menu->cmds = first_node;
}