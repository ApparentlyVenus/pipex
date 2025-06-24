/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:37:07 by odana             #+#    #+#             */
/*   Updated: 2025/06/24 21:17:06 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	execute_command(t_node *cmd_node, char **envp, t_node *head)
{
	char	*path;

	if (!cmd_node->args || !*cmd_node->args || !**cmd_node->args)
		perror_exit("empty command", 127, head);
	path = find_path(cmd_node->args[0], envp);
	if (!path)
		perror_exit("command not found", 127, head);
	if (execve(path, cmd_node->args, envp) == -1)
	{
		free(path);
		perror_exit("execve", 127, head);
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

void	handle_child_process(t_exec *exec, t_node *cmd,
	t_node *head, char **envp)
{
	free(exec->pids);
	exec->pids = NULL;
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
		handle_sigpipe(head);
	execute_command(cmd, envp, head);
}

void	handle_sigpipe(t_node *head)
{
	char	*line;
	t_node	*tail;
	int		output;

	tail = find_tail(head);
	output = setup_output(tail, head);
	if (output != 0)
	{
		line = get_next_line(STDIN_FILENO);
		while (line)
		{
			free(line);
			line = get_next_line(STDIN_FILENO);
		}
		free_node_list(head);
		exit(output);
	}
}

void	process_command(t_exec *exec, t_node *cmd,
	t_node *head, char **envp)
{
	if (exec->cmd_index < exec->cmd_count - 1)
	{
		if (pipe(exec->pipe_fd) == -1)
			perror_exit("pipe", 1, NULL);
	}
	exec->pids[exec->cmd_index] = fork();
	if (exec->pids[exec->cmd_index] == -1)
		perror_exit("fork", 1, NULL);
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
