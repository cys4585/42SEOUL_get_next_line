/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:22:46 by youngcho          #+#    #+#             */
/*   Updated: 2022/05/02 19:08:32 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list  *ft_lstnew(int fd, char *str, char *backup_str)
{
    t_list  *new;

    new = (t_list *)malloc(sizeof(t_list *));
    if (new == NULL)
        return (NULL);
    new->fd = fd;
    new->str = str;
    new->backup_str = backup_str;
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

int get_nl_idx(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	if (s[i] == '\n')
		return (i);
	return (-1);
}

char    *read_one_cycle(int fd, int *nl_idx)
{
    char    buf[BUFFER_SIZE];
    int     read_bytes;
    char    *str;

    str = NULL;
    while (1)
    {
        read_bytes = read(fd, buf, BUFFER_SIZE);
        if (read_bytes < 0)
            return (NULL);
        if (read_bytes == 0)
            return (str);
        if (read_bytes < BUFFER_SIZE)
            buf[read_bytes] = '\0';
        str = ft_strjoin(str, buf);
        if (str == NULL)
            return (NULL);
        *nl_idx = get_nl_idx(str);
        if(*nl_idx != -1)
            return (str);
    }
}

char    *get_next_line(int fd)
{
    static t_list   *head;
    char            *str;
    int             nl_idx;

    if (head == NULL)
        ft_lstadd_back(&head, ft_lstnew(-1, NULL, NULL));
    str = read_one_cycle(fd, &nl_idx);
    if (str == NULL)
        return (NULL);
    return (str);
}