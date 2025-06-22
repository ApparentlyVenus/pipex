/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:37:07 by odana             #+#    #+#             */
/*   Updated: 2025/06/22 01:15:18 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	exec_pipeline(t_node *head, char **envp, int fd[2])
{
	int		prev_fd;
	t_node	*node;

	prev_fd = -1;
	node = head;
	while (node)
	{
		if (node->type == NODE_INFILE)
			process_infile(node);
		else if (node->type == NODE_OUTFILE)
			process_outfile(node);
		else if (node->type == NODE_CMD)
		{
			pipe(fd);
			process_child(node, prev_fd, fd, envp);
			if (prev_fd != -1)
				close(prev_fd);
			prev_fd = fd[0];
			close(fd[1]);
		}
		node = node->next;
	}
	while (wait(NULL) > 0)
		;
	unlink(".heredoc");
}

void	handle_heredoc(t_node	*heredoc)
{
	char	*line;
	int		fd;

	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		perror_exit("heredoc open");
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, heredoc->value, ft_strlen(heredoc->value) == 0
				&& line[ft_strlen(heredoc->value)] == '\n'))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free (line);
	}
	close (fd);
	free(heredoc->value);
	heredoc->value = ft_strdup(".heredoc");
	heredoc->type = NODE_INFILE;
}

void	exec_cmd(t_node *node, char **envp)
{
	char	*path;

	if (!node || node->type != NODE_CMD || !node->args)
		perror_exit("invalid cmd");
	path = find_path(node->args[0], envp);
	if (!path)
	{
		free_split(node->args);
		perror("cmd not found");
		exit(127);
	}
	if (execve(path, node->args, envp) == -1)
		perror_exit("execve");
}

void	process_child(t_node *node, int prev_fd, int fd[2], char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror_exit("fork");
	if (pid == 0)
	{
		if (prev_fd != -1)
		{
			dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
		}
		if (node->next && node->next->type == NODE_PIPE)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
		}
		exec_cmd(node, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_node	*head;
	int		fd[2];

	head = parse_args(argc, argv);
	if (!head)
		perror_exit("parse failed");
	if (head->type == NODE_HEREDOC)
		handle_heredoc(head);
	exec_pipeline(head, envp, fd);
	free_node_list(head);
	return (0);
}
