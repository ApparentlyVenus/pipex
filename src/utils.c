/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:15:27 by odana             #+#    #+#             */
/*   Updated: 2025/06/24 21:25:31 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	setup_heredoc(t_node *heredoc_node)
{
	int		pipe_fd[2];
	char	*l;
	char	*v;

	if (pipe(pipe_fd) == -1)
		perror_exit("heredoc pipe", 1, NULL);
	v = heredoc_node->value;
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		l = get_next_line(STDIN_FILENO);
		if (!l)
			break ;
		if (ft_strncmp(l, v, ft_strlen(v)) == 0 && l[ft_strlen(v)] == '\n')
		{
			free(l);
			break ;
		}
		write(pipe_fd[1], l, ft_strlen(l));
		free(l);
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
			perror_exit("infile", 1, head);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

int	setup_output(t_node *tail, t_node *head)
{
	int	fd;
	int	flags;

	if (tail->type == NODE_OUTFILE)
	{
		if (head->type == NODE_HEREDOC)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		fd = open(tail->value, flags, 0644);
		if (fd == -1)
		{
			perror("outfile");
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	wait_for_children(t_exec *exec)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < exec->cmd_count)
	{
		waitpid(exec->pids[i], &status, 0);
		if (i == exec->cmd_count - 1)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else
				exit_code = 1;
		}
		i++;
	}
	return (exit_code);
}
