/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:28:41 by odana             #+#    #+#             */
/*   Updated: 2025/06/24 23:11:31 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

t_node	*create_node(t_node_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = NULL;
	node->args = NULL;
	node->next = NULL;
	return (node);
}

t_node	*parse_cmd_node(t_node *current, char **argv, int *i)
{
	char	**cmd_args;
	t_node	*cmd_node;

	if (!argv[*i] || !*argv[*i])
		return (NULL);
	cmd_args = ft_split(argv[*i], ' ');
	if (!cmd_args || !*cmd_args || !**cmd_args)
	{
		if (cmd_args)
			free_split(cmd_args);
		return (NULL);
	}
	cmd_node = create_node(NODE_CMD);
	if (!cmd_node)
		return (free_split(cmd_args), NULL);
	return (cmd_node->args = cmd_args, current->next = cmd_node,
		(*i)++, cmd_node);
}

t_node	*parse_pipe_node(t_node *current)
{
	t_node	*pipe_node;

	pipe_node = create_node(NODE_PIPE);
	if (!pipe_node)
		return (NULL);
	current->next = pipe_node;
	return (pipe_node);
}

t_node	*create_infile_node(char **argv)
{
	t_node	*head;

	head = create_node(NODE_INFILE);
	if (!head)
		return (NULL);
	head->value = ft_strdup(argv[1]);
	if (!head->value)
		return (free_node_list(head), NULL);
	return (head);
}
