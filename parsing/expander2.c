#include "../minishell.h"

int	checker_ex(char *line, int i, int quote)
{
	if (line[i] && line[i + 1] && (line[i] == '$')
		&& (ft_isalnum(line[i + 1])
			|| line[i + 1] == '?' || line[i + 1] == '$'
			|| ((line[i + 1] == '"' || line[i + 1] == 39) && quote < 0)))
		return (1);
	else
		return (0);
}

void	ex_utils(char **line, int *i)
{
	char	*temp;

	temp = *line;
	if (temp[*i] == 92 && temp[*i + 1])
		*i += 1;
	if (temp[*i])
		*i += 1;
}

void	ex_utils_2(char *line, int *i, int *quote)
{
	if (line[*i] == '"')
		*quote *= -1;
	if (line[*i] == 39 && *quote < 0)
	{
		*i += 1;
		while (line[*i] && line[*i] != 39)
			*i += 1;
	}
}

char	*ft_expand(char *line, t_menu *menu)
{
	int	i;
	int	quote;

	i = 0;
	quote = -1;
	if (!line)
		return (NULL);
	while (line[i])
	{
		ex_utils_2(line, &i, &quote);
		if (checker_ex(line, i, quote))
			line = ft_expander(line, i, menu);
		ex_utils(&line, &i);
	}
	return (line);
}
