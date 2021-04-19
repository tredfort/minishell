/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 19:41:53 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/19 16:50:26 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_2list	*ft_2lstnew(void *content)
{
	t_2list	*new;

	new = (t_2list *)malloc(sizeof(t_2list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_2lstadd_front(t_2list **lst, t_2list *new)
{
	t_2list	*tmp;

	if (new)
	{
		new->next = *lst;
		if (*lst)
		{
			tmp = *lst;
			tmp->prev = new;
		}
		*lst = new;
	}
}

char	*init_history(char *path, t_2list **lst)
{
	char	*line;
	char	*file;
	int		fd;

	*lst = NULL;
	if (!path)
		path = getenv("HOME");
	if (!path)
		path = "/tmp";
	file = ft_strjoin(path, "/.bash_history");
	if (!file)
		exit(1);
	fd = open(file, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd > 0)
	{
		while (get_next_line(fd, &line) > 0)
			ft_2lstadd_front(lst, ft_2lstnew(line));
		free(line);
		close(fd);
	}
	return (file);
}

void	save_history(char *file, t_2list **lst)
{
	int		fd;
	t_2list	*tail;
	t_2list	*tmp;

	if (!file)
		exit(1);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd > 0)
	{
		tail = *lst;
		while (tail->next)
			tail = tail->next;
		while (tail)
		{
			write(fd, (char *)tail->content, ft_strlen((char *)tail->content));
			free(tail->content);
			tmp = tail;
			tail = tail->prev;
			free(tmp);
		}
		close(fd);
	}
	free(file);
}
