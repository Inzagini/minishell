#include "minishell.h"

int	pipe_handle(t_data *data, t_token **head)
{
	t_token	*new_token;

	printf("[PIPE]\n");
	new_token = create_token(NULL, PIPE);
	if (!new_token)
		return (1);
	append_token_lst(head, new_token);
	data->start = data->index;
	data->cmd_flag = 0;
	return (0);
}

int	rd_out_handle(t_data *data, t_token **head)
{
	t_token	*new_token;

	printf("[RD_OUT]\n");
	new_token = create_token(NULL, RD_OUT);
	if (!new_token)
		return (1);
	append_token_lst(head, new_token);
	data->start = data->index;
	data->rd_flag = 1;
	return (0);
}

int	rd_in_handle(t_data *data, t_token **head)
{
	t_token	*new_token;

	printf("[RD_IN]\n");
	new_token = create_token(NULL, RD_IN);
	if (!new_token)
		return (1);
	append_token_lst(head, new_token);
	data->start = data->index;
	data->rd_flag = 1;
	return (0);
}
int	rd_app_handle(t_data *data, t_token **head)
{
	t_token	*new_token;

	printf("[RD_APP]\n");
	new_token = create_token(NULL, RD_APP);
	if (!new_token)
		return (1);
	append_token_lst(head, new_token);
	data->start = data->index;
	data->rd_flag = 1;
	return (0);
}
int	rd_inin_handle(t_data *data, t_token **head)
{
	t_token	*new_token;

	printf("[RD_ININ]\n");
	new_token = create_token(NULL, RD_ININ);
	if (!new_token)
		return (1);
	append_token_lst(head, new_token);
	data->start = data->index;
	data->rd_flag = 1;
	return (0);
}
