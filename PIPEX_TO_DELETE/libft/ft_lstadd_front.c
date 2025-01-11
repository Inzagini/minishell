/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:37:31 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/10 13:23:04 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Adds the node ’new’ at the beginning of the list.
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL || lst == NULL)
		return ;
	new->next = *lst;
	*lst = new;
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
// 	ft_lstadd_front(&head, new_node);
// 	if (new_node == head && head->next != NULL
// 		&& head->next->content == &value1)
// 		printf("Test passed: New node added to the front.\n");
// 	else
// 		printf("Test failed: New node was not added correctly.\n");
// 	free(head->next);
// 	free(head);
// 	return(0);
// }
