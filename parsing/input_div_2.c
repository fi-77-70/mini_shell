#include "../minishell.h"

int	get_args_size(t_args *msh)
{
	int	size;

	size = 0;
	while (msh)
	{
		if (msh->type == RED_IN || msh->type == HERE_DOC || msh->type == APP_OUT
			|| msh->type == RED_OUT)
			msh = msh->next->next;
		if (msh && msh->type == PIPE)
			break ;
		if (msh && msh->type == ARG)
			size++;
		if (msh)
			msh = msh->next;
	}
	return (size);
}

void	get_args_2(t_args *temp, char **args)
{
	int	i;

	i = 0;
	while (temp)
	{
		if (temp && temp->type == PIPE)
			break ;
		if (temp->type == RED_IN || temp->type == HERE_DOC
			|| temp->type == APP_OUT || temp->type == RED_OUT)
			temp = temp->next;
		if (temp && temp->type == ARG && (!temp->prev
				|| (temp->prev->type != RED_IN && temp->prev->type != RED_OUT
					&& temp->prev->type != APP_OUT
					&& temp->prev->type != HERE_DOC)))
			args[i++] = ft_strdup(temp->token);
		if (temp)
			temp = temp->next;
	}
	args[i] = NULL;
}

char	**get_args(t_args *msh, t_cmds *cmd)
{
	int		i;
	int		size;
	char	**args;
	t_args	*temp;

	i = 0;
	size = get_args_size(msh);
	args = cmd->args;
	temp = msh;
	if (size == 0)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	get_args_2(temp, args);
	return (args);
}

t_args	*get_redir(t_args *msh)
{
	t_args	*redir;

	redir = (t_args *)malloc(sizeof(t_args));
	redir->type = msh->type;
	if (msh->next)
		redir->token = msh->next->token;
	redir->next = NULL;
	return (redir);
}
