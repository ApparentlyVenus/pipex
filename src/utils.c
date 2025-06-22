/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:14:15 by odana             #+#    #+#             */
/*   Updated: 2025/06/22 10:47:42 by odana            ###   ########.fr       */
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

void	perror_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
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

void	execute_cmd(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	if (!argv || !*argv)
		perror_exit("empty command");
	cmd = ft_split(argv, ' ');
	if (!cmd || !*cmd || !**cmd)
		perror_exit("invalid command");
	path = find_path(cmd[0], envp);
	if (!path)
	{
		free_split(cmd);
		perror("error finding path");
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
		perror("error executing cmd");
}
