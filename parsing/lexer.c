#include "../minishell.h"

void	ft_get_type(t_args **mshh, t_menu *menu, char *token)
{
	t_args	*msh;

	msh = *mshh;
	if (!ft_strcmp(token, "|"))
		msh->type = PIPE;
	else if (!ft_strcmp(token, "~"))
	{
		free((*mshh)->token);
		(*mshh)->token = ft_strdup(menu->til);
		msh->type = ARG;
	}
	else if (!ft_strcmp(token, "$$"))
	{
		free((*mshh)->token);
		(*mshh)->token = NULL;
		(*mshh)->token = env_get("$", menu);
		msh->type = ARG;
	}
	else if (!ft_strcmp(token, ">"))
		msh->type = RED_OUT;
	else if (!ft_strcmp(token, ">>"))
		msh->type = APP_OUT;
	else if (!ft_strcmp(token, "<"))
		msh->type = RED_IN;
	else if (!ft_strcmp(token, "<<"))
		msh->type = HERE_DOC;
	else
		msh->type = 0;
}

void	create_tokens(t_args **mshh, char **mtr)
{
	int	j;
	t_args *temp;
	t_args	*msh;

	j = -1;
	temp = *mshh;
	temp = (t_args *)malloc(sizeof(t_args));
	if (!temp)
		return ;
	temp->prev = NULL;
	msh = temp;
	while (mtr[++j])
	{
		temp->token = ft_strdup(mtr[j]);
		temp->type = 0;
		if(mtr[j + 1])
		{
			temp->next = (t_args *)malloc(sizeof(t_args));
			if (!temp->next)
				return ;
			temp->next->prev = temp;
		}
		else
			temp->next = NULL;
		temp = temp->next;
	}
	*mshh = msh;
}

t_args	*lexer(t_args **mshh, char **line, t_menu *menu)
{
	int		j;
	t_args	*msh;
	t_args	*temp;
	
	j = -1;
	create_tokens(mshh, line);
	if (!*mshh)
		return (NULL);
	msh = *mshh;
	temp = msh;
	while(line[++j])
	{
		*mshh = temp;
		if (!msh->type)
			ft_get_type(&msh, menu, line[j]);
		if (!msh->type)
			msh->type = ARG;
		if (msh->next)
			msh = msh->next;
	}
	*mshh = temp;
	return (temp);
}
