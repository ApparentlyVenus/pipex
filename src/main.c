/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:17:43 by odana             #+#    #+#             */
/*   Updated: 2025/06/24 21:22:10 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	execute_pipeline(t_node *head, char **envp)
{
	t_exec	exec;
	t_node	*current;
	int		exit_code;

	exec.cmd_count = count_commands(head);
	if (exec.cmd_count == 0)
		return (1);
	exec.pids = malloc(sizeof(pid_t) * exec.cmd_count);
	if (!exec.pids)
		perror_exit("malloc", 1, head);
	exec.prev_fd = -1;
	exec.cmd_index = 0;
	current = head;
	while (current)
	{
		if (current->type == NODE_CMD)
			process_command(&exec, current, head, envp);
		current = current->next;
	}
	exit_code = wait_for_children(&exec);
	free(exec.pids);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_node	*head;
	int		exit_code;

	head = parse_args(argc, argv);
	if (!head)
	{
		ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 2);
		ft_putendl_fd("   or: ./pipex here_doc LIMITER cmd1 cmd2 outfile", 2);
		return (1);
	}
	exit_code = execute_pipeline(head, envp);
	free_node_list(head);
	return (exit_code);
}
