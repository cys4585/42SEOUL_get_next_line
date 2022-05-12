/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:22:46 by youngcho          #+#    #+#             */
/*   Updated: 2022/05/12 15:35:11 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	lstadd_back(t_list **lst, int fd, char *str, char **backup_str)
{
	t_list	*new;
	t_list	*node;
	char	*tmp_str;

	if (lst == NULL)
		return ;
	new = malloc(sizeof(t_list));
	if (new == NULL)
		return ;
	new->fd = fd;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	node = *lst;
	while (node->next)
		node = node->next;
	node->next = new;
	new->prev = node;
	new->str = str;
	new->next = NULL;
	new->backup_str = NULL;
	tmp_str = split_nl(*backup_str, backup_str);
	if (tmp_str == NULL)
		new->backup_str = *backup_str;
	else
		lstadd_back(&new, fd, tmp_str, backup_str);
}

char	*read_one_cycle(int fd, char **backup_str)
{
	char	buf[BUFFER_SIZE + 1];
	int		read_bytes;
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	while (1)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes < 0)
			return (NULL);
		else if (read_bytes == 0)
			return (str);
		buf[read_bytes] = '\0';
		str = ft_strjoin(str, buf);
		if (str == NULL)
			return (NULL);
		while (str[i])
			if (str[i++] == '\n')
				return (split_nl(str, backup_str));
	}
}

char	*get_backup_str_from_lst(t_list *node, int fd)
{
	char	*str;

	str = NULL;
	while (node)
	{
		if (node->fd == fd && !node->str && node->backup_str)
		{
			str = ft_strdup(node->backup_str);
			free(node->backup_str);
			node->backup_str = NULL;
			break ;
		}
		node = node->next;
	}
	return (str);
}

char	*get_str_from_lst(t_list *node, int fd)
{
	char	*str;
	char	*backup_str;
	char	*final_str;

	backup_str = get_backup_str_from_lst(node, fd);
	str = NULL;
	while (node)
	{
		if (node->fd == fd && node->str)
		{
			str = ft_strdup(node->str);
			free(node->str);
			node->str = NULL;
			break ;
		}
		node = node->next;
	}
	final_str = ft_strjoin(backup_str, str);
	if (str != NULL)
		free(str);
	return (final_str);
}
#include <stdio.h>
char	*get_next_line(int fd)
{
	static t_list	*head;
	char			*str;
	char			*backup_str;
	t_list			*node;

	if (head == NULL)
		lstadd_back(&head, -1, NULL, NULL);
	backup_str = NULL;
	str = read_one_cycle(fd, &backup_str);
	if (str != NULL)
		lstadd_back(&head, fd, str, &backup_str);
	free(str);
	str = get_str_from_lst(head, fd);
	node = head;
	while (node)
	{
		if (node->fd != -1 && node->str == NULL && node->backup_str == NULL && node->prev && node->next)
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
			free(node);
		}
		node = node->next;
	}
	printf("\n%p\n", head);
	return (str);
}
