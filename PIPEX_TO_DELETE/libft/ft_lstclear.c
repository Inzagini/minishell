/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:49:27 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:08:27 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*temp2;

	if (!lst || !del)
		return ;
	temp = *lst;
	while (temp)
	{
		temp2 = temp->next;
		del(temp->content);
		free(temp);
		temp = temp2;
	}
	*lst = NULL;
}
// #include <stdio.h>
// #include "libft.h"
// #include <stdlib.h>

// void	del(void *content)
// {
// 	(void)content;
// }

// int main(void)
// {
// 	int value1 = 1;
// 	int	value2 = 2;
// 	t_list *head = ft_lstnew(&value1);
// 	t_list *new_node = ft_lstnew(&value2);

// 	ft_lstadd_front(&head, new_node);
// 	ft_lstclear(&head, del);
// 	if (head == NULL)
// 		printf("Successful deletion");
// 	return(0);
// }
