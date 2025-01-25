#include "minishell.h"

void	close_all_pipes(int pipefd[2][2])
{
	close (pipefd[0][0]);
	close (pipefd[0][1]);
	close (pipefd[1][0]);
	close (pipefd[1][1]);
}

void	close_child_pipes(t_command *lst_cmd, int pipefd[2][2])
{
	close(pipefd[1 - (lst_cmd->id + 1) % 2][0]);
	close(pipefd[(lst_cmd->id + 1) % 2][1]);
	close(pipefd[(lst_cmd->id + 1) % 2][0]);
}

void	close_parent_pipes(t_command *lst_cmd, int pipefd[2][2])
{
	close (pipefd[1 - (lst_cmd->id + 1) % 2][0]);
	close (pipefd[1 - (lst_cmd->id + 1) % 2][1]);
	close (pipefd[(lst_cmd->id + 1) % 2][1]);
}
