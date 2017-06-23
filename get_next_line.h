/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 21:45:24 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/23 05:43:06 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/uio.h>
# include <sys/types.h>
# include "libft/libft.h"
# define BUFF_SIZE 1024

<<<<<<< HEAD
typedef struct	s_gnl
{
	int			fd;
	char		*file_content;
}				t_gnl;
=======
# define BUFF_SIZE 4096
>>>>>>> 93618e1fe34bfca77f01d7c9727615369dd80fd4

int				get_next_line(const int fd, char **line);

#endif
