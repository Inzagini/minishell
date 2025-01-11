/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:50:04 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/10 13:00:50 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Counts the number of nodes in a list.
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
// #include <stdio.h>
// #include <stdlib.h>
// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*new;
// 	int		value1 = 1;
// 	int		value2 = 2;
// 	int		count;

// 	head = ft_lstnew(&value1);
// 	new = ft_lstnew(&value2);
// 	ft_lstadd_back(&head, new);
// 	count = ft_lstsize(head);
// 	printf("%d\n", count);
// 	free (head);
// 	free (new);
// 	return (0);
// }
