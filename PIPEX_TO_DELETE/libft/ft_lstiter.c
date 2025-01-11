/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:03:36 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/10 12:37:35 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Iterates the list ’lst’ and applies the function ’f’ on the content
// of each node
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	if (!lst || !f)
		return ;
	temp = lst;
	while (temp)
	{
		f(temp->content);
		temp = temp->next;
	}
}
// #include <stdio.h>
// #include <stdlib.h>
// void	doubleup(void *content)
// {
// 	*(int*)content *= 2;
// }

// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*new;
// 	int		value1 = 1;
// 	int		value2 = 2;
// 	int		value1new;
// 	int		value2new;

// 	head = ft_lstnew(&value1);
// 	new = ft_lstnew(&value2);
// 	ft_lstadd_back(&head, new);
// 	ft_lstiter(head, doubleup);
// 	value1new = *(int *)head->content;
// 	value2new = *(int *)head->next->content;
// 	printf("%d\n", value1new);
// 	printf("%d\n", value2new);
// 	free(head);
// 	free(new);
// 	return (0);
// }
