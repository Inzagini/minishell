/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:34:19 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:08:31 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Takes as a parameter a node and frees the memory of
//the node’s content using the function ’del’ given
//as a parameter and free the node. The memory of
//’next’ must not be freed.
#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
// #include <stdio.h>
// void	del(void *content)
// {
// 	(void)content;
// }

// int	main(void)
// {
// 	t_list	*head;
// 	int	value1 = 1;
// 	head = ft_lstnew(&value1);
// 	if (head != NULL)
// 		printf("created\n");
// 	ft_lstdelone(head, del);
// 	if (head == NULL)
// 		printf("deleted\n");
// 	return (0);
// }
// test does not work as its accessing freed memory (which is not NULL)
