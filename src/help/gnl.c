/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:28:47 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/10 17:54:16 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_create_last(char *text, char **line, char *buf)
{
	char	*pos;

	free(buf);
	pos = gnl_strchr(text, '\0');
	*line = malloc((pos - text + 1) * sizeof(**line));
	if (*line == NULL)
	{
		free(text);
		return (NULL);
	}
	gnl_strlcpy(*line, text, pos - text + 1);
	free(text);
	return (NULL);
}

static int	ft_create_line(char *text, char **line, char *buf)
{
	char	*pos;
	int		i;

	free(buf);
	pos = gnl_strchr(text, '\n');
	if (pos != NULL)
	{
		*line = malloc((pos - text + 1) * sizeof(**line));
		if (*line == NULL)
		{
			free(text);
			return (-1);
		}
		gnl_strlcpy(*line, text, pos - text + 1);
		i = 0;
		while (pos[i + 1] != '\0')
		{
			text[i] = pos[i + 1];
			i++;
		}
		text[i] = '\0';
	}
	return (1);
}

static int	ft_rd_zero(char **text, char **line, char *buf)
{
	*text = ft_create_last(*text, line, buf);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int			rd;
	static char	*text;
	char		*buf;

	if (fd < 0 || line == NULL)
		return (-1);
	buf = malloc(sizeof(*buf) * 2);
	if (buf == NULL)
		return (-1);
	rd = 1;
	while (rd > 0 && gnl_strchr(text, '\n') == NULL)
	{
		rd = read(fd, buf, 1);
		if (rd < 0)
		{
			free(buf);
			return (-1);
		}
		buf[rd] = '\0';
		text = gnl_strjoin(text, buf);
	}
	if (rd == 0)
		return (ft_rd_zero(&text, line, buf));
	ft_create_line(text, line, buf);
	return (1);
}
