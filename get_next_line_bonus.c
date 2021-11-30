/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:13:00 by oouazize          #+#    #+#             */
/*   Updated: 2021/11/29 20:01:45 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_free(char **frfr)
{
	free(*frfr);
	*frfr = NULL;
}

void	ft_line(char **line, char **save, char **tmp)
{
	if (ft_strchr(*save, '\n') == -1)
	{
		*line = ft_strdup(*save);
		ft_free(save);
	}
	else
	{
		*line = ft_substr(*save, 0, ft_strchr(*save, '\n') + 1);
		*tmp = *save;
		*save = ft_strdup(*save + ft_strchr(*save, '\n') + 1);
		ft_free(tmp);
	}
}

int	ft_alloc(char **buff, int fd)
{
	*buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff || fd < 0)
	{
		free(*buff);
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;
	char		*buff;
	char		*tmp;
	int			ret;

	if (ft_alloc(&buff, fd) == 0)
		return (0);
	if (!save[fd])
		save[fd] = ft_strdup("");
	ret = BUFFER_SIZE;
	while (ret > 0 && ft_strchr(save[fd], '\n') == -1)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
			break ;
		buff[ret] = 0;
		save[fd] = ft_strjoin(save[fd], buff);
	}
	ft_free(&buff);
	ft_line(&line, &save[fd], &tmp);
	if (*line == '\0')
		ft_free(&line);
	return (line);
}
// int main()
// {
// 	int fd1 = open("file1", O_RDONLY);
// 	int fd2 = open("file2", O_RDONLY);
// 	int fd3 = open("file3", O_RDONLY);

// 	for(int i = 0; i < 3;i++)
// 	{
// 		printf("%s", get_next_line(fd1));
// 		printf("%s", get_next_line(fd2));
// 		printf("%s", get_next_line(fd3));
// 	}
// }
