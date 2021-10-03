/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luricard <luricard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 17:55:11 by luricard          #+#    #+#             */
/*   Updated: 2021/10/03 17:16:06 by luricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_var(void *var)
{
	free(var);
	var = NULL;
}

static char	*read_line_from_file(int fd, char *line_buff)
{
	char	*buff;
	int		bytes_read;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(line_buff, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free_var(buff);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		line_buff = ft_strjoin(line_buff, buff);
	}
	free_var(buff);
	return (line_buff);
}

static char	*extract_line_from_line_buff(char *line_buff)
{
	char	*result;
	int		i;

	if (!*line_buff)
		return (NULL);
	i = 0;
	while (line_buff[i] && line_buff[i] != '\n')
		i++;
	result = (char *)malloc(sizeof(char) * (i + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (line_buff[i] && line_buff[i] != '\n')
	{
		result[i] = line_buff[i];
		i++;
	}
	if (line_buff[i] == '\n')
	{
		result[i] = line_buff[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static char	*remove_line_read_from_line_buff(char *line_buff)
{
	char	*line_rest;
	int		i;
	int		j;

	i = 0;
	while (line_buff[i] && line_buff[i] != '\n')
		i++;
	if (!line_buff[i])
	{
		free(line_buff);
		return (NULL);
	}
	line_rest = (char *)malloc(sizeof(char) * (ft_strlen(line_buff) - i + 1));
	if (!line_rest)
		return (NULL);
	i++;
	j = 0;
	while (line_buff[i])
		line_rest[j++] = line_buff[i++];
	line_rest[j] = '\0';
	free(line_buff);
	return (line_rest);
}

char	*get_next_line(int fd)
{
	static char	*line_buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line_buff = read_line_from_file(fd, line_buff);
	if (!line_buff)
		return (NULL);
	line = extract_line_from_line_buff(line_buff);
	line_buff = remove_line_read_from_line_buff(line_buff);
	return (line);
}
