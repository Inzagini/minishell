#include "minishell.h"

int	main(void)
{
	char	*test;
	test = readline("Test prompt:");
	printf("%s\n", test);
}
