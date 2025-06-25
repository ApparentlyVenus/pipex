/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:14:15 by odana             #+#    #+#             */
/*   Updated: 2025/06/24 21:56:52 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**split;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	split = ft_split(envp[i] + 5, ':');
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		part_path = ft_strjoin(split[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
			return (free_split(split), path);
		free(path);
		i++;
	}
	free_split(split);
	return (NULL);
}

void	perror_exit(char *msg, int exit_code, t_node *head)
{
	free_node_list(head);
	perror(msg);
	exit(exit_code);
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

void	free_node_list(t_node *head)
{
	t_node	*tmp;

	if (!head)
		return ;
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

t_node	*find_tail(t_node *head)
{
	t_node	*current;

	current = head;
	while (current->next)
		current = current->next;
	return (current);
}
//./pipex infile.txt "cat" "" ouuu
//./pipex infile.txt "cat" "cat" ouuu            000 ouuu
//./pipex infile.txt "cat" "catfff" ooo
//./pipex here_do ww "cat" "cat" ddd
//./pipex here_doc "  " " " "cat" ddd
//./pipex here_doc sss " " "cat" ddd 
//./pipex cat here_doc sss cat oooooo
//./pipex zsdughiuzshg cat cat ooooo 
 
 