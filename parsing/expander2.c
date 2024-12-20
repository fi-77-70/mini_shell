#include "../minishell.h"

int	checker_ex(char *line, int i, int quote)
{
	if (line[i] && line[i + 1] && (line[i] == '$' || line[i] == '~')
		&& (ft_isalnum(line[i + 1])
			|| line[i + 1] == '?' || line[i + 1] == '$'
			|| ((line[i + 1] == '"' || line[i + 1] == 39) && quote < 0)))
				return (1);
	else
		return (0);
}

char	*ft_expand(char *line, t_menu *menu)
{
	int	i;
	int	second;
	int	quote;

	i = 0;
	quote = -1;
	second = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '"')
			quote *= -1;
		if (line[i] == 39 && quote < 0)
		{
			i++;
			while (line[i] && line[i] != 39)
				i++;
		}
		if (checker_ex(line, i, quote))
		{
			line = ft_expander(line, i, menu);
			second = 1;
		}
		if (line[i] == 92 && line[i + 1])
			i++;
		if (line[i])
			i++;
		if (!line[i] && second)
		{
			second = 0;
			line = ft_take_out_back(line, '\\');
			i = 0;
		}
	}
	return (line);
}
