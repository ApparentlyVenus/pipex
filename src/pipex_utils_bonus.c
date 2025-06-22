/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 01:03:14 by odana             #+#    #+#             */
/*   Updated: 2025/06/22 01:15:24 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	process_infile(t_node *infile)
{
	int	fdin;

	fdin = open(infile->value, O_RDONLY);
	if (fdin < 0)
		perror_exit("infile open");
	dup2(fdin, STDIN_FILENO);
	close(fdin);
}

void	process_outfile(t_node *outfile)
{
	int	fdout;

	fdout = open(outfile->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout < 0)
		perror_exit("outfile open");
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
}

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
	i = 0;
	while (split[i])
	{
		part_path = ft_strjoin(split[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free_split(split);
	return (NULL);
}

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

void	perror_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
