/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amfarrej <amfarrej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 17:03:48 by amfarrej          #+#    #+#             */
/*   Updated: 2026/11/23 21:03:44 by amfarrej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

char	*ft_strchr(char *s, int c);
char	*join_free(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s);
char	*get_next_line(int fd);

#endif
