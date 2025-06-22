/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:37:07 by odana             #+#    #+#             */
/*   Updated: 2025/06/22 13:27:04 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	execute_command(t_node *cmd_node, char **envp)
{
	char	*path;

	if (!cmd_node->args || !cmd_node->args[0])
		exit(127);
	path = find_path(cmd_node->args[0], envp);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd_node->args[0], STDERR_FILENO);
		exit(127);
	}
	if (execve(path, cmd_node->args, envp) == -1)
	{
		free(path);
		perror_exit("execve");
	}
}

int	count_commands(t_node *head)
{
	t_node	*current;
	int		count;

	count = 0;
	current = head;
	while (current)
	{
		if (current->type == NODE_CMD)
			count++;
		current = current->next;
	}
	return (count);
}

t_node	*find_tail(t_node *head)
{
	t_node	*current;

	current = head;
	while (current->next)
		current = current->next;
	return (current);
}

void	handle_child_process(t_exec *exec, t_node *cmd,
	t_node *head, char **envp)
{
	t_node	*tail;

	if (exec->cmd_index > 0)
	{
		dup2(exec->prev_fd, STDIN_FILENO);
		close(exec->prev_fd);
	}
	else
		setup_input(head);
	if (exec->cmd_index < exec->cmd_count - 1)
	{
		close(exec->pipe_fd[0]);
		dup2(exec->pipe_fd[1], STDOUT_FILENO);
		close(exec->pipe_fd[1]);
	}
	else
	{
		tail = find_tail(head);
		setup_output(tail);
	}
	execute_command(cmd, envp);
}

void	process_command(t_exec *exec, t_node *cmd,
	t_node *head, char **envp)
{
	if (exec->cmd_index < exec->cmd_count - 1)
	{
		if (pipe(exec->pipe_fd) == -1)
			perror_exit("pipe");
	}
	exec->pids[exec->cmd_index] = fork();
	if (exec->pids[exec->cmd_index] == -1)
		perror_exit("fork");
	if (exec->pids[exec->cmd_index] == 0)
		handle_child_process(exec, cmd, head, envp);
	if (exec->prev_fd != -1)
		close(exec->prev_fd);
	if (exec->cmd_index < exec->cmd_count - 1)
	{
		close(exec->pipe_fd[1]);
		exec->prev_fd = exec->pipe_fd[0];
	}
	exec->cmd_index++;
}
