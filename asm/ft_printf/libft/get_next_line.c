/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:48:46 by akorzhak          #+#    #+#             */
/*   Updated: 2017/11/29 14:48:49 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_realloc(void *arr, size_t size)
{
	void			*new;

	if ((ft_strlen(arr) + 1) == size)
		return (arr);
	if (!(new = ft_memalloc(size)))
		return (0);
	if (arr)
	{
		if (ft_strlen(arr) > size)
			ft_memcpy(new, arr, size - 1);
		else
			ft_memcpy(new, arr, ft_strlen(arr));
		free(arr);
		arr = 0;
	}
	return (new);
}

int					get_line(char *buff, char **line)
{
	size_t			i;
	size_t			len;
	char			*n;

	n = ft_memchr(buff, '\n', ft_strlen(buff));
	i = n - buff;
	if (!(*line = ft_realloc(*line, (ft_strlen(*line) + i + 1))))
		return (-1);
	ft_strncat(*line, buff, i);
	len = ft_strlen(buff);
	ft_bzero(buff, ++i);
	n++;
	ft_memmove(buff, n, ft_strlen(n));
	ft_bzero(&buff[len - i], i);
	return (1);
}

int					read_write(int fd, char *buff, char **line)
{
	int				c;

	while (!ft_memchr(buff, '\n', BUFF_SIZE))
	{
		ft_bzero(buff, ft_strlen(buff));
		if ((c = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		if (!c && **line)
		{
			ft_bzero(buff, ft_strlen(buff));
			return (1);
		}
		if (!c && !**line)
		{
			ft_strdel(line);
			return (0);
		}
		if (!ft_memchr(buff, '\n', BUFF_SIZE))
		{
			if (!(*line = ft_realloc(*line, (ft_strlen(*line) + c + 1))))
				return (-1);
			ft_strcat(*line, buff);
		}
	}
	return ('+');
}

int					get_next_line(const int fd, char **line)
{
	static char		*buff;
	int				ret;

	if (BUFF_SIZE < 1 || fd == -1 || !line)
		return (-1);
	if (!buff)
	{
		if (!(buff = ft_strnew(BUFF_SIZE)))
			return (-1);
	}
	if ((*buff) && !ft_memchr(buff, '\n', ft_strlen(buff)))
	{
		*line = ft_strnew(ft_strlen(buff));
		ft_strcpy(*line, buff);
	}
	else
		*line = ft_strnew(1);
	ret = read_write(fd, buff, line);
	if (ret != '+')
	{
		ft_strdel(&buff);
		return (ret);
	}
	ret = get_line(buff, line);
	return (ret);
}
