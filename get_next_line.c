/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:22:46 by youngcho          #+#    #+#             */
/*   Updated: 2022/05/11 15:39:42 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*split_nl(char *str, char **backup_str)
{
	char	*tmp_str;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			break;
		i++;
	}
	if (str[i] == '\0')
		return (NULL);
	tmp_str = str;
	if (str[i + 1] != '\0')
	{
		*backup_str = ft_strdup(&str[i + 1]);
		str[i + 1] = '\0';
	}
	str = ft_strdup(str);
	free(tmp_str);
	return (str);
}

void	ft_lstadd_back(t_list **lst, int fd, char *str, char **backup_str)
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
	tmp_str = split_nl(*backup_str, backup_str);
	printf("tmp_str:%s\nbackup_str:%s\n", tmp_str, *backup_str);
	if (tmp_str == NULL)
		new->backup_str = *backup_str;
	else
		ft_lstadd_back(&new, fd, tmp_str, backup_str);
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

	backup_str = get_backup_str_from_lst(node, fd);
	str = NULL;
	while (node)
	{
		if (node->fd == fd && node->str)
		{
			str = ft_strdup(node->str);
			free(node->str);
			node->str = NULL;
			break;
		}
		node = node->next;
	}
	char	*final_str = ft_strjoin(backup_str, str);
	if (str != NULL)
		free(str);
	return (final_str);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	char			*str;
	char			*backup_str;

	if (head == NULL)
		ft_lstadd_back(&head, -1, NULL, NULL);
	// str = get_str_from_lst(head, fd);
	// if (str != NULL)
	// 	return (str);
	backup_str = NULL;
	str = read_one_cycle(fd, &backup_str);
	// printf("153\nstr:%s\nbackup_str:%s", str, backup_str);
	if (str != NULL)
		ft_lstadd_back(&head, fd, str, &backup_str);
	printf("154\n");
	t_list	*node = head;
	while (node)
	{
		if (node->fd != -1)
			printf("str:%s\nbackup_str:%s\n", node->str, node->backup_str);
		node = node->next;
	}
	printf("162\n");
	return (get_str_from_lst(head, fd));
}
