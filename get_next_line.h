/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 21:45:24 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/24 23:41:35 by gguiulfo         ###   ########.fr       */
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
# define GNL_CHK(a) if(1){if(a){return(-1);}}

typedef struct	s_gnl
{
	int			fd;
	char		*file_content;
}				t_gnl;

int				get_next_line(const int fd, char **line);
void			ft_gnl_free(void *content, size_t size);
t_list			**ft_gnl_list(void);

#endif
