/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:02:13 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/01 15:03:23 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//creates a new list by applying function f to each element of lst,
//with del handling cleanup on error.
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	new_list = NULL;
	new_node = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
// #include <stdio.h>

// void	*doubleup(void *content)
// {
// 	*(int *)content *= 2;
// 	return (content);
// }

// void	del(void *content)
// {
// 	(void)content;
// }

// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*second;
// 	t_list	*new;
// 	int 	value1 = 1;
// 	int		value2 = 2;
// 	int		value1n;
// 	int		value2n;

// 	head = ft_lstnew(&value1);
// 	second = ft_lstnew(&value2);

// 	ft_lstadd_back(&head, second);
// 	new = ft_lstmap(head, &doubleup, del);
// 	value1n = *(int *)new->content;
// 	value2n = *(int *)new->next->content;
// 	printf("value 1n = %d\nvalue 2n = %d\n", value1n, value2n);
// 	ft_lstclear(&head, del);
// 	ft_lstclear(&new, del);
// 	return (0);
// }
