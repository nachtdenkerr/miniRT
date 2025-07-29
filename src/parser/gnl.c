/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:40:38 by jmutschl          #+#    #+#             */
/*   Updated: 2025/07/29 20:12:53 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	delete_line_from_buf(char *buffer, int num_char)
{
	int	i;

	if (!buffer || num_char == 0)
		return ;
	ft_memmove_gnl(buffer, buffer + num_char, BUFFER_SIZE - num_char);
	i = BUFFER_SIZE - num_char;
	while (i < BUFFER_SIZE)
	{
		buffer[i] = '\0';
		i++;
	}
}

int	create_line(char **line, char *buffer)
{
	ssize_t	num_char;
	char	*part_buffer;
	char	*temp;

	if (*buffer == '\0')
		return (-1);
	num_char = 0;
	while (buffer[num_char] != '\n' && buffer[num_char] != '\0')
		num_char++;
	if (ft_strchr_gnl(buffer, '\n'))
		num_char++;
	part_buffer = malloc ((num_char + 1) * sizeof(char));
	if (!part_buffer)
		return (free (*line), -1);
	part_buffer[num_char] = '\0';
	part_buffer = ft_memmove_gnl(part_buffer, buffer, num_char);
	temp = ft_strjoin_gnl(*line, part_buffer);
	free (*line);
	free (part_buffer);
	if (!temp)
		return (-1);
	*line = temp;
	delete_line_from_buf(buffer, num_char);
	return (0);
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	char			*line;
	ssize_t			bytes_read;
	int				err;

	line = NULL;
	if (fd == -1 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	while (1)
	{
		if (buffer[0] == '\0')
			bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(line), NULL);
		if ((bytes_read == 0 && buffer[0] == '\0') || ft_strchr_gnl(line, '\n'))
			return (line);
		buffer[BUFFER_SIZE] = '\0';
		err = create_line(&line, buffer);
		if (err == -1)
			return (NULL);
	}
}
