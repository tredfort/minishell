/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:15:13 by tredfort          #+#    #+#             */
/*   Updated: 2021/03/16 21:55:40 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

//t_2list	*ft_2lstnew(void *content)
//{
//	t_2list	*new;
//
//	new = (t_2list *)malloc(sizeof(t_2list));
//	if (!new)
//		return NULL;
//	new->content = content;
//	new->next = NULL;
//	new->prev = NULL;
//	return (new);
//}
//
//void	ft_2lstadd_front(t_2list **lst, t_2list *new)
//{
//	t_2list	*tmp;
//
//	if (new)
//	{
//		new->next = *lst;
//		if (*lst)
//		{
//			tmp = *lst;
//			tmp->prev = new;
//		}
//		*lst = new;
//	}
//}
//
//int		init_history(char *file, t_2list **list)
//{
//	char	*line;
//	int		fd;
//
//	fd = open(file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
//	if (fd > 0)
//	{
//		while (get_next_line(fd, &line) > 0)
//			ft_2lstadd_front(list, ft_2lstnew(line));
//	}
//	return fd;
//}

#include <stdio.h>

char	*hello(int i)
{
	if (i)
		return (0);
	return ("Hello");
}

int main(int argc, char **argv)
{
	char	*s;

	s = hello(0);
	if (s)
		printf("%s\n", s);
	return 0;
}
