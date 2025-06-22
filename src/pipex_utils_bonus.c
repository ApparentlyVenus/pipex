/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:15:27 by odana             #+#    #+#             */
/*   Updated: 2025/06/22 13:19:23 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	setup_heredoc(t_node *heredoc_node)
{
	int		pipe_fd[2];
	char	*line;
	char	*value;

	if (pipe(pipe_fd) == -1)
		perror_exit("heredoc pipe");
	value = heredoc_node->value;
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, value, ft_strlen(value)) == 0
			&& line[ft_strlen(value)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
}

void	setup_input(t_node *head)
{
	int	fd;

	if (head->type == NODE_HEREDOC)
		setup_heredoc(head);
	else if (head->type == NODE_INFILE)
	{
		fd = open(head->value, O_RDONLY);
		if (fd == -1)
			perror_exit("infile");
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	setup_output(t_node *tail)
{
	int	fd;

	if (tail->type == NODE_OUTFILE)
	{
		fd = open(tail->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			perror_exit("outfile");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
