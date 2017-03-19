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

t_list	*ft_getnode(t_list **lst, int fd)
{
	char *tmp;
	t_list *tempnode;

	tempnode = *lst;
	if ((*lst) == NULL)
	{
		(*lst) = ft_lstnew("\0", sizeof(char));
		(*lst)->content_size = fd;
		//printf("lst == NULL\n");
		return ((*lst));
	}
	if (tempnode->content_size == (size_t)fd)
	{
		//printf("\n---\nlst->content:\n%s$\n---\n", (*lst)->content);
		//printf("\n---\nStrchr:\n%s$\n---\n", ft_strchr((*lst)->content, '\n'));
		tmp = ft_strsub(tempnode->content, ft_linlen(tempnode->content) + 1, ft_strlen(ft_strchr(tempnode->content, '\n') + 1));
		free(tempnode->content);
		tempnode->content = (char *)malloc(sizeof(char) * ft_strlen(tmp));
		tempnode->content = ft_strcpy(tempnode->content, tmp);
		return (tempnode);
	}
	while (tempnode->next)
	{
		tempnode = tempnode->next;
		//printf("\n---\nlst->content:\n%s$\n---\n", tempnode->content);
		if (tempnode->content_size == (size_t)fd)
		{
			//printf("in the if of the loop\n");
			tmp = ft_strsub(tempnode->content, ft_linlen(tempnode->content) + 1, ft_strlen(ft_strchr(tempnode->content, '\n') + 1));
			free(tempnode->content);
			tempnode->content = (char *)malloc(sizeof(char) * ft_strlen(tmp));
			tempnode->content = ft_strcpy(tempnode->content, tmp);
			return (tempnode);
		}
	}
	ft_lstadd(lst, ft_lstnew("\0", sizeof(char)));
	(*lst)->content_size = fd;
	return ((*lst));
}

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
	//printf("\n---\nNode content in get_next_line:\n%s$\n---\n", node->content);
	len = ft_linlen(temp->content);
	//printf("\n---\nLen: '%d'$\n---\n", len);
	*line = ft_strnew(len);
	*line = ft_strncpy(*line, temp->content, len);
	return (1);
}

int main(int argc, char **argv)
{
	if (argc == 1) return (0);
	char *line;
	int fd;
	int fd2;
	int fd3;

	fd = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	fd3 = open(argv[3], O_RDONLY);
	get_next_line(fd, &line);
	printf("fd: %s\n", line);
	get_next_line(fd2, &line);
	printf("fd2: %s\n", line);
	get_next_line(fd3, &line);
	printf("fd3: %s\n", line);
	get_next_line(fd, &line);
	printf("fd: %s\n", line);
	get_next_line(fd2, &line);
	printf("fd2: %s\n", line);
	get_next_line(fd3, &line);
	printf("fd3: %s\n", line);
	get_next_line(fd, &line);
	printf("fd: %s\n", line);
	get_next_line(fd2, &line);
	printf("fd2: %s\n", line);
	get_next_line(fd3, &line);
	printf("fd3: %s\n", line);
	close(fd);
	close(fd2);
	close(fd3);
	return (0);
}
