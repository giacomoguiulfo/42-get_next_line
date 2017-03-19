/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 21:44:34 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/03/12 20:27:55 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "libft/libft.h"
// Delete these for final version
#include <fcntl.h> // This one is for open
#include <stdio.h> // This one is for printf
// ---------------------------------

int get_next_line(const int fd, char **line)
{
	static	t_list *node;
	char	buf[BUFF_SIZE + 1];
	int		ret;
	int		len;

	if (fd < 0 || read(fd, buf, 0) < 0 || !line)
		return (-1);
	node = ft_lstnew("\0", fd);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		node->content = ft_strjoin(node->content, buf);
	}
	len = ft_linlen(node->content);
	*line = ft_strnew(len);
	*line = ft_strncpy(*line, node->content, len);
	return (1);
}

int main(int argc, char **argv)
{
	if (argc == 1) return (0);
	char *line;
	int fd;

	fd = open(argv[1], O_RDONLY);
	get_next_line(fd, &line);
	printf("%s", line);
	get_next_line(fd, &line);
	printf("%s", line);
	close(fd);
	return (0);
}
