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

int	ft_getchar_fd(int fd)
{
	static char buf[BUFF_SIZE + 1];
	static char *bufp = buf;
	static int n = 0;
	static int i = -1;

	if (n == 0) /* buffer is empty */
	{
		//printf("getting here???\n");
		if ((n = read(fd, buf, BUFF_SIZE)) == 0)
		{
			//printf("Ever getting here\n");
			//i = -1;
			//n = 0;
		}
		else if (n < 0)
			return (-7);
		bufp = buf;
		i = -1;
	}
	//printf("This is n: %d and this is i: %d\n", n, i);
	//return (--n >= 0) ? (unsigned char) bufp[++i] : EOF;
	if (--n >= 0)
	{
		return (unsigned char) bufp[++i];
	}
	else
	{
		n = 0;
		return EOF;
	}
}

/*
** Return values of get_next_line()
** 1 : Line has been read
** 0 : Reading has been completed: EOF reached
** -1: Error has happend
*/

char *ft_ctos(char c)
{
	char *str;

	str = (char *)malloc(sizeof(char) + 1);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int get_next_line(const int fd, char **line)
{
	//static char chr
	char chr;
	char *tmp2;
	char *str;
	char *tmp = "";
	size_t i = 0;
	chr = 0;
	str = ft_strnew(0);

	// if (chr == EOF)
	// {
	// 	printf("First EOF\n");
	// 	// chr = 'a';
	// 	return (0);
	// }

	if (fd < 0 || !line)
		return (-1);
	while ((chr = ft_getchar_fd(fd)) != EOF)
	{
		if (chr == -7)
			return (-1);
		if (chr == '\n')
			break;
		tmp2 = ft_ctos(chr);
		str = ft_strjoin(tmp, tmp2);
		tmp = str;
		//printf("%c", chr);

			i++;
	}

	if (chr == EOF)
	{

		if (ft_strlen(str) > 0)
		{
			*line = str;
			return (1);
		}
		//printf("Last EOF\n");
		// chr = 'a';
		return (0);
	}

	//printf("%s\n", str);
	*line = str;
	return (1);

}

// int	main(int argc, char **argv)
// {
// 	if (argc == 1) return 0;
// 	char *str;
// 	//char *str2;
// 	//char *str3;
// 	char **arr;
// 	argv[30] = 0;
// 	arr = (char **)malloc(sizeof(char *) * 10);
// 	//int i = 0;
// 	int fd = open(argv[1], O_RDONLY, S_IRUSR);
// 	//fd = 99;
// 	//printf("%d\n", get_next_line(99, (void*)0));
// 	while (get_next_line(fd, &str))
// 	{
// 		printf("%s\n", str);
// 		free(str);
// 		//i++;
// 	}
// 	close(fd);
// 	// printf("---File 2---\n");
// 	// int fd2 = open(argv[2], O_RDONLY, S_IRUSR);
// 	// while (get_next_line(fd2, &str2))
// 	// {
// 	// 	printf("%s\n", str2);
// 	// 	free(str2);
// 	// 	i++;
// 	// }
// 	// 	printf("---File 3---\n");
// 	// while (get_next_line(fd, &str3))
// 	// {
// 	// 	printf("%s\n", str3);
// 	// 	free(str3);
// 	// 	i++;
// 	// }
// 	// while (get_next_line(fd, &str3))
// 	// {
// 	// 	arr[i] = str;
// 	// 	free(str);
// 	// 	i++;
// 	// }
//
// 	return (0);
// }

#include <assert.h>

int main()
{
	char 	*line;
	int		out;
	int		p[2];
	char 	*str;
	int		len = 50;

	str = (char *)malloc(1000 * 1000);
	*str = '\0';
	while (len--)
		strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	out = dup(1);
	pipe(p);
	dup2(p[1], 1);

	if (str)
		write(1, str, strlen(str));
	close(p[1]);
	dup2(out, 1);
	printf("%d", get_next_line(p[0], &line));
	printf("%s\n", line);
	assert(strcmp(line, str) == 0);
}
