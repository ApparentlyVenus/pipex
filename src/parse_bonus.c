/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:15:31 by odana             #+#    #+#             */
/*   Updated: 2025/06/22 00:59:02 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	parsing_mode(int argc, char **argv)
{
	if (argc < 5)
		return (0);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			return (0);
		return (2);
	}
	else
		return (1);
}

t_node	*parse_args(int argc, char **argv)
{
	int	mode;

	mode = parsing_mode(argc, argv);
	if (mode == 1)
		return (parse_standard_args(argc, argv));
	else if (mode == 2)
		return (parse_heredoc_args(argc, argv));
	else
		return (NULL);
}

t_node	*parse_standard_args(int argc, char **argv)
{
	t_node	*current;
	t_node	*head;
	t_node	*out_node;

	head = create_infile_node(argv);
	if (!head)
		return (NULL);
	current = parse_sequence(head, argc, argv, 2);
	if (!current)
		return (NULL);
	out_node = create_node(NODE_OUTFILE);
	if (!out_node)
		return (free_node_list(head), NULL);
	out_node->value = ft_strdup(argv[argc - 1]);
	if (!out_node->value)
		return (free_node_list(head), NULL);
	current->next = out_node;
	return (head);
}

t_node	*parse_heredoc_args(int argc, char **argv)
{
	t_node	*head;
	t_node	*current;
	t_node	*out_node;

	head = create_node(NODE_HEREDOC);
	if (!head)
		return (NULL);
	head->value = ft_strdup(argv[2]);
	if (!head->value)
		return (free_node_list(head), NULL);
	current = parse_sequence(head, argc, argv, 3);
	if (!current)
		return (NULL);
	out_node = create_node(NODE_OUTFILE);
	if (!out_node)
		return (free_node_list(head), NULL);
	out_node->value = ft_strdup(argv[argc - 1]);
	if (!out_node->value)
		return (free_node_list(head), NULL);
	return (current->next = out_node, head);
}

t_node	*parse_sequence(t_node *head, int argc, char **argv, int i)
{
	t_node	*current;
	t_node	*new_node;
	int		cmd;

	current = head;
	cmd = 1;
	while (i < argc - 1)
	{
		new_node = NULL;
		if (cmd)
			new_node = parse_cmd_node(current, argv, &i, &cmd);
		else
			new_node = parse_pipe_node(current, argv, &i, &cmd);
		if (!new_node)
			return (free_node_list(head), NULL);
		current = new_node;
	}
	if (cmd)
		return (free_node_list(head), NULL);
	return (current);
}
