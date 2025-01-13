#include "minishell.h"

int	lst_len(t_command *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

void	print_error(char *prefix, char *msg, char *name)
{
	if (prefix)
	{
		write(2, prefix, ft_strlen(prefix));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	if (name)
	{
		write(2, ": ", 2);
		write(2, name, ft_strlen(name));
	}
	write(2, "\n", 1);
}
