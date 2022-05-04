/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:17:09 by youngcho          #+#    #+#             */
/*   Updated: 2022/05/04 18:53:46 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i + 1 < dstsize && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*dst;
	int		i;

	len = ft_strlen(s1);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *old_str, char const *buf)
{
	char	*new_str;
	size_t	len_old;
	size_t	len_buf;

	if (old_str == NULL && buf == NULL)
		return (NULL);
	if (old_str == NULL)
		return (ft_strdup(buf));
	if (buf == NULL)
		return (ft_strdup(old_str));
	len_old = ft_strlen(old_str);
	len_buf = ft_strlen(buf);
	new_str = (char *)malloc(sizeof(char) * (len_old + len_buf + 1));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, old_str, len_old + 1);
	ft_strlcpy(new_str + len_old, buf, len_buf + 1);
	free((void *)old_str);
	return (new_str);
}

void	ft_lstadd_back(t_list **lst, int fd, char *str, char *backup_str)
{
	t_list	*new;
	t_list	*node;

	if (lst == NULL)
		return ;
	new = malloc(sizeof(t_list));
	if (new == NULL)
		return ;
	new->fd = fd;
	if (fd == -1)
	{
		*lst = new;
		return ;
	}
	new->str = str;
	new->backup_str = backup_str;
	node = *lst;
	while (node->next)
		node = node->next;
	node->next = new;
	new->prev = node;
}
