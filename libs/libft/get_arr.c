/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:03:28 by filferna          #+#    #+#             */
/*   Updated: 2024/09/23 14:29:53 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <fcntl.h>

void	m_matrix_2(char *stash, char **line, int a, int j)
{
	while (*stash)
	{
		if (*stash && *stash != '\n')
		{
			line[j][a] = *stash;
			stash++;
			a++;
		}
		if (*stash == '\n')
		{
			line[j][a] = 0;
			stash++;
			if (*stash)
			{
				j++;
				a = 0;
				line[j] = (char *)malloc(sizeof(char *)
						* ft_strclen(stash, '\n'));
			}
			if (*stash && !line[j])
				free_matrix(line);
		}
	}
	line[j][a] = 0;
	line[++j] = NULL;
}

static char	**m_matrix(char **line, char *stas)
{
	int		i;
	int		a;
	int		j;
	char	*stash;

	stash = stas;
	i = -1;
	a = 2;
	j = 0;
	while (stash[++i])
		if (stash[i] == '\n')
			a++;
	if (i < 1 || !*stash)
		return (NULL);
	line = (char **)malloc(sizeof(char *) * a);
	if (!line)
		return (NULL);
	a = 0;
	line[j] = (char *)malloc(sizeof(char) * ft_strclen(stash, '\n'));
	if (!line[j])
		return (NULL);
	m_matrix_2(stash, line, a, j);
	return (line);
}

static char	*join(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		a;

	if (!s2 || !*s2)
		return (s1);
	i = ft_strclen(s1, 0) + ft_strclen(s2, 0);
	new_str = (char *)malloc(sizeof(char) * i + 1);
	if (!new_str)
		return (NULL);
	a = -1;
	i = 0;
	if (s1 && *s1)
	{
		i = -1;
		while (s1[++i])
			new_str[i] = s1[i];
	}
	while (s2[++a])
		new_str[i++] = s2[a];
	new_str[i] = 0;
	if (s1)
		free(s1);
	return (free(s2), new_str);
}

char	*get_stash(char *buffer, char **stash, int bytes_read, int fd)
{
	while (bytes_read != 0)
	{
		buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buffer)
			return (free(stash), NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free_lines(buffer, *stash), NULL);
		if (bytes_read == 0)
		{
			if (buffer)
				free(buffer);
			return (*stash);
		}
		buffer[bytes_read] = 0;
		*stash = join(*stash, buffer);
	}
	return (*stash);
}

char	**get_arr(int fd)
{
	int				bytes_read;
	char			*buffer;
	char			**line;
	static char		*stash;

	line = NULL;
	bytes_read = 1;
	stash = NULL;
	buffer = NULL;
	if (fd < 0)
		return (NULL);
	get_stash(buffer, &stash, bytes_read, fd);
	if (!stash)
		return (NULL);
	line = m_matrix(line, stash);
	free(stash);
	return (line);
}
/*
int	main(void)
{
	int	j;
	int	fd;
	char	**line;

	j = 0;
	fd = open("text", O_RDONLY);
	line = get_arr(fd);
	while (line[j])
		printf("%s\n", line[j++]);
	free_matrix(line);
	return (0);
}
*/
