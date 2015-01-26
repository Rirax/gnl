/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlechapt <rlechapt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 09:36:49 by rlechapt          #+#    #+#             */
/*   Updated: 2014/12/01 18:00:01 by rlechapt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_check_eof(char **str, char **line)
{
	*line = *str;
	*str = NULL;
	if (*line[0] == '\0')
	{
		ft_strdel(str);
		return (0);
	}
	return (1);
}

static char	*ft_stroinj(char *s1, char *s2)
{
	char	*s3;

	if ((s3 = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
	{
		ft_strcpy(s3, s1);
		free(s1);
		ft_strcat(s3, s2);
		free(s2);
		return (s3);
	}
	return (NULL);
}

static char	*ft_add_to_buf(int fd, char *str, int *ret)
{
	char	*tmp;
	char	*buf;

	if ((buf = ft_strnew(BUFF_SIZE)) == NULL)
		return (NULL);
	if ((*ret = read(fd, buf, BUFF_SIZE)) < 0)
		return (NULL);
	buf[*ret] = '\0';
	tmp = ft_stroinj(str, buf);
	return (tmp);
}

int			get_next_line(int const fd, char **line)
{
	int			ret;
	static char	*str = NULL;
	char		*ptr;

	ret = 1;
	if (fd < 0 || !line)
		return (-1);
	if (!str && (str = ft_strnew(0)) == NULL)
		return (-1);
	while (ret > 0)
	{
		while ((ptr = ft_strchr(str, '\n')))
		{
			*line = ft_strsub(str, 0, ptr - str);
			ft_memmove(str, ptr + 1, ft_strlen(ptr + 1) + 1);
			return (1);
		}
		if ((str = ft_add_to_buf(fd, str, &ret)) == NULL)
			return (-1);
	}
	if (ret == 0 && ((ft_strchr(str, '\n') == NULL)))
		return (ft_check_eof(&str, line));
	return (0);
}
