/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:22:46 by youngcho          #+#    #+#             */
/*   Updated: 2022/05/03 20:11:44 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_list	*ft_lstnew(int fd, char **str)
{
	t_list	*new;
	char	*nl_str;
	int		nl_idx;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->str = NULL;
	new->next = NULL;
	new->prev = NULL;
	if (fd == -1)
		return (new);
	printf("####\n%s\n####\n", *str);
	nl_str = *str;
	if (nl_str == NULL)
		return (NULL);
	nl_idx = get_nl_idx(nl_str);
	if (nl_idx != -1)
	{
		*str = ft_strdup(nl_str + nl_idx + 1);
		nl_str[nl_idx + 1] = '\0';
	}
	new->str = ft_strdup(nl_str);
	free(nl_str);
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		node = *lst;
		while (node->next)
			node = node->next;
		node->next = new;
		new->prev = node;
	}
}

char	*read_one_cycle(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		read_bytes;
	char	*str;

	str = NULL;
	while (1)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes < 0)
			return (NULL);
		if (read_bytes == 0)
			return (str);
		buf[read_bytes] = '\0';
		str = ft_strjoin(str, buf);
		if (str == NULL)
			return (NULL);
		if (get_nl_idx(str) != -1)
			return (str);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*node;
	char			*tmp_str;
	char			*result_str;

	if (head == NULL)
		ft_lstadd_back(&head, ft_lstnew(-1, NULL));
	tmp_str = read_one_cycle(fd);
	if (tmp_str != NULL)
	{
		ft_lstadd_back(&head, ft_lstnew(fd, &tmp_str));
		printf("%s\n", tmp_str);
		while (get_nl_idx(tmp_str) != -1)
			ft_lstadd_back(&head, ft_lstnew(fd, &tmp_str));
	}
	node = head;
	result_str = NULL;
	while (node)
	{
		node = node->next;
		if (node->fd == fd && node->str)
		{
			result_str = ft_strdup(node->str);
			free((void *)node->str);
			node->str = NULL;
			break ;
		}
	}
	return (result_str);
}
