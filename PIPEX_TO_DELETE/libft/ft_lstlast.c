/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:02:13 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/10 12:45:19 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Returns the last node of the list.
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
// #include <stdlib.h>
// #include <stdio.h>
// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*new;
// 	t_list	*last;
// 	int		value1 = 1;
// 	int		value2 = 2;
// 	int		value3;

// 	head = ft_lstnew(&value1);
// 	new = ft_lstnew(&value2);
// 	ft_lstadd_back(&head, new);
// 	last = ft_lstlast(head);
// 	value3 = *(int *)last->content;
// 	printf("%d", value3);
// 	free(head);
// 	free(new);
// 	return (0);
// }
