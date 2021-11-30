/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 04:26:10 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/30 21:33:40 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_strsave(int fd, char **line, char **store)
{
	int		i;
	char	*temp;

	i = 0;
	while (store[fd][i] != '\n' && store[fd][i] != '\0')
		i++;
	if (store[fd][i] == '\n')
	{
		*line = ft_substr(store[fd], 0, i);
		temp = ft_substr(store[fd], i + 1, ft_strlen(store[fd]) - i);
		free(store[fd]);
		store[fd] = temp;
		return (1);
	}
	else
	{
		*line = ft_strdup(store[fd]);
		free(store[fd]);
		store[fd] = NULL;
		return (0);
	}
}

static int	ft_returns(int fd, char **line, char **store, int readcount)
{
	if (readcount == -1)
		return (-1);
	if (!(readcount) && store[fd] == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	return (ft_strsave(fd, line, store));
}

int	get_next_line(int fd, char **line)
{
	static char	*store[100000];
	char		buff[BUFFER_SIZE + 1];
	t_read		st;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	st.ret = read(fd, buff, BUFFER_SIZE);
	while (st.ret > 0)
	{
		buff[st.ret] = '\0';
		if (!store[fd])
			store[fd] = ft_strdup("");
		st.temp = ft_strjoin(store[fd], buff);
		free(store[fd]);
		store[fd] = st.temp;
		if (ft_strchr(store[fd], '\n'))
			break ;
		st.ret = read(fd, buff, BUFFER_SIZE);
	}
	return (ft_returns(fd, line, store, st.ret));
}
