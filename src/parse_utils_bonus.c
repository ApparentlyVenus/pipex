/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:28:41 by odana             #+#    #+#             */
/*   Updated: 2025/06/21 22:55:29 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"
#include "../lib/inc/libft.h"

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

t_node	*parse_cmd_node(t_node *current, char **argv, int *i, int *cmd)
{
	char	**cmd_args;
	t_node	*cmd_node;

	if (ft_strcmp(argv[*i], "|") == 0)
		return (NULL);
	cmd_args = ft_split(argv[*i], ' ');
	if (!cmd_args)
		return (NULL);
	cmd_node = create_node(NODE_CMD);
	if (!cmd_node)
		return (free_split(cmd_args), NULL);
	return (cmd_node->args = cmd_args, current->next = cmd_node,
		*cmd = 0, (*i)++, cmd_node);
}

t_node	*parse_pipe_node(t_node *current, char **argv, int *i, int *cmd)
{
	t_node	*pipe_node;

	if (ft_strcmp(argv[*i], "|") != 0)
		return (NULL);
	pipe_node = create_node(NODE_PIPE);
	if (!pipe_node)
		return (NULL);
	current->next = pipe_node;
	return (*cmd = 1, (*i)++, pipe_node);
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

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
