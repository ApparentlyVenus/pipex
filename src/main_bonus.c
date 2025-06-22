/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:17:43 by odana             #+#    #+#             */
/*   Updated: 2025/06/22 13:28:59 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	free_node_list(t_node *head)
{
	t_node	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->value)
			free(head->value);
		if (head->args)
			free_split(head->args);
		free(head);
		head = tmp;
	}
}

void	execute_pipeline(t_node *head, char **envp)
{
	t_exec	exec;
	t_node	*current;

	exec.cmd_count = count_commands(head);
	if (exec.cmd_count == 0)
		return ;
	exec.pids = malloc(sizeof(pid_t) * exec.cmd_count);
	if (!exec.pids)
		perror_exit("malloc");
	exec.prev_fd = -1;
	exec.cmd_index = 0;
	current = head;
	while (current)
	{
		if (current->type == NODE_CMD)
			process_command(&exec, current, head, envp);
		current = current->next;
	}
	wait_for_children(&exec);
	free(exec.pids);
}

int	main(int argc, char **argv, char **envp)
{
	t_node	*head;

	head = parse_args(argc, argv);
	if (!head)
	{
		ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 2);
		ft_putendl_fd("   or: ./pipex here_doc LIMITER cmd1 cmd2 outfile", 2);
		return (1);
	}
	execute_pipeline(head, envp);
	free_node_list(head);
	return (0);
}
