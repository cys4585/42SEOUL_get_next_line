/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:22:46 by youngcho          #+#    #+#             */
/*   Updated: 2022/05/04 18:57:33 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*split_i(char *str, int i, char **backup_str)
{
	char	*tmp_str;

	tmp_str = str;
	*backup_str = ft_strdup(&str[i + 1]);
	str[i + 1] = '\0';
	str = ft_strdup(str);
	free(tmp_str);
	return (str);
}

char	*read_one_cycle(int fd, char **backup_str)
{
	char	buf[BUFFER_SIZE + 1];
	int		read_bytes;
	char	*str;
	int		i;

	str = NULL;
	i = -1;
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
		while (str[++i])
			if (str[i] == '\n')
				return (split_i(str, i, backup_str));
	}
}

char	*get_one_line(t_list *node, int fd)
{
	t_list	*backup_node;
	char	*str;
	char	*tmp;

	str = NULL;
	while (node)
	{
		printf("	63\n");
		printf("	str:%s\nbackup_str:%s\n", node->str, node->backup_str);
		if (node->fd == fd && node->str)
		{
			str = ft_strdup(node->str);
			free(node->str);
			node->str = NULL;
			backup_node = node->prev;
			while (backup_node)
			{
				if (backup_node->fd == fd && backup_node->backup_str)
				{
					tmp = str;
					str = ft_strjoin(backup_node->backup_str, str);
					free(tmp);
					backup_node->backup_str = NULL;
				}
				backup_node = backup_node->prev;
			}
		}
		node = node->next;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	char			*str;
	char			*backup_str;

	printf("92\n");
	if (head == NULL)
		ft_lstadd_back(&head, -1, NULL, NULL);
	printf("95\n");
	str = get_one_line(head, fd);
	if (str != NULL)
		return (str);
	printf("99\n");
	str = read_one_cycle(fd, &backup_str);
	printf("101\n");
	if (str != NULL)
		ft_lstadd_back(&head, fd, str, backup_str);
	printf("104\n");
	return (get_one_line(head, fd));
}
