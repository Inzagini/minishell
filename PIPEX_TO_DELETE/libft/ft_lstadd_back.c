/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:06:55 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/10 13:23:19 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
// #include <stdio.h>
// #include "libft.h"
// #include <stdlib.h>

// int main(void)
// {
// 	int value1 = 1;
// 	t_list *head = ft_lstnew(&value1);
// 	int	value2 = 2;
// 	t_list *new_node = ft_lstnew(&value2);
// 	ft_lstadd_back(&head, new_node);
// 	if (head->next == new_node)
// 		printf("Test passed: New node added to the back.\n");
// 	else
// 		printf("Test failed: New node was not added correctly.\n");
// 	free(head);
// 	free(new_node);
// 	return(0);
// }
