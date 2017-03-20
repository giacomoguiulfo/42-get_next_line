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

static t_list	*ft_getnode(t_list **lst, int fd)
{
	char *tmp;
	t_list *tempnode;
	int temporal;

	tempnode = *lst;
	if ((*lst) == NULL)
	{
		(*lst) = ft_lstnew("\0", sizeof(char));
		(*lst)->content_size = fd;
		return ((*lst));
	}
	if (tempnode->content_size == (size_t)fd)
	{
		if (ft_strchr(tempnode->content, '\n'))
		{
			temporal = ft_strlen(ft_strchr(tempnode->content, '\n') + 1);
			tmp = ft_strsub(tempnode->content, ft_linlen(tempnode->content) + 1, temporal);
			free(tempnode->content);
			tempnode->content = ft_strnew(ft_strlen(tmp));
			tempnode->content = ft_strcpy(tempnode->content, tmp);
			free(tmp);
		}
		else
			free(tempnode->content);
		return (tempnode);
	}
	while (tempnode->next)
	{
		tempnode = tempnode->next;
		if (tempnode->content_size == (size_t)fd)
		{
			if (ft_strchr(tempnode->content, '\n'))
			{
				temporal = ft_strlen(ft_strchr(tempnode->content, '\n') + 1);
				tmp = ft_strsub(tempnode->content, ft_linlen(tempnode->content) + 1, temporal);
				free(tempnode->content);
				tempnode->content = ft_strnew(ft_strlen(tmp));
				tempnode->content = ft_strcpy(tempnode->content, tmp);
				free(tmp);
			}
			else
				free(tempnode->content);
			return (tempnode);
		}
	}
	ft_lstadd(lst, ft_lstnew("\0", sizeof(char)));
	(*lst)->content_size = fd;
	return ((*lst));
}

// static void ft_del(void *content, size_t content_size)
// {
// 	char *str;
//
// 	str = (char *)content;
// 	content_size = 0;
// 	free(str);
// 	str = NULL;
// }

int get_next_line(const int fd, char **line)
{
	static	t_list *node = NULL;
	t_list *temp;
	char	buf[BUFF_SIZE + 1];
	int		ret;
	int		len;

	if (fd < 0 || read(fd, buf, 0) < 0 || !line)
		return (-1);

	temp = ft_getnode(&node, fd);
	//node = ft_lstnew("\0", fd);

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		temp->content = ft_strjoin(temp->content, buf);
		//printf("temp Content: %s\n", temp->content);
		if (ft_strchr(temp->content, '\n') != NULL)
			break;
	}
	if (temp->content)
	{
		len = ft_linlen(temp->content);
		*line = ft_strnew(len);
		*line = ft_strncpy(*line, temp->content, len);
	}
	if (ret == 0 && ft_strlen(temp->content) == 0)
	{
		//ft_lstdel(&node, &ft_del);
		free(*line);
		return (0);
	}
	return (1);
}

// int main(int argc, char **argv)
// {
// 	if (argc == 1) return (0);
// 	char *line;
// 	int fd;
// 	// int fd2;
// 	// int fd3;
//
// 	fd = open(argv[1], O_RDONLY);
// 	// fd2 = open(argv[2], O_RDONLY);
// 	// fd3 = open(argv[3], O_RDONLY);
// 	// while (get_next_line(fd, &line))
// 	// {
// 	// 	printf("%s\n", line);
// 	// 	free(line);
// 	// }
// 	printf("%d - fd: %s\n", get_next_line(fd, &line), line);
// 	printf("------------\n");
// 	printf("%d - fd: %s\n", get_next_line(fd, &line), line);
// 	//printf("%d - fd: %s\n", get_next_line(fd, &line), line);
// 	// printf("%d - fd: %s\n", get_next_line(fd, &line), line);
// 	// printf("%d - fd: %s\n", get_next_line(fd, &line), line);
// 	// printf("%d - fd: %s\n", get_next_line(fd, &line), line);
// 	// printf("%d - fd: %s\n", get_next_line(fd, &line), line);
// 	// get_next_line(fd2, &line);
// 	// printf("fd2: %s\n", line);
// 	// get_next_line(fd3, &line);
// 	// printf("fd3: %s\n", line);
// 	// get_next_line(fd, &line);
// 	// printf("fd: %s\n", line);
// 	// get_next_line(fd2, &line);
// 	// printf("fd2: %s\n", line);
// 	// get_next_line(fd3, &line);
// 	// printf("fd3: %s\n", line);
// 	// get_next_line(fd, &line);
// 	// printf("fd: %s\n", line);
// 	// get_next_line(fd2, &line);
// 	// printf("fd2: %s\n", line);
// 	// get_next_line(fd3, &line);
// 	// printf("fd3: %s\n", line);
// 	close(fd);
// 	// close(fd2);
// 	// close(fd3);
// 	return (0);
// }
