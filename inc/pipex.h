/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:23:36 by odana             #+#    #+#             */
/*   Updated: 2025/06/24 21:00:46 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:23:36 by odana             #+#    #+#             */
/*   Updated: 2025/06/22 12:49:43 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

# include "../lib/inc/libft.h"
# include "../lib/inc/get_next_line.h"

typedef enum e_node_type
{
	NODE_INFILE,
	NODE_HEREDOC,
	NODE_CMD,
	NODE_PIPE,
	NODE_OUTFILE,
}	t_node_type;

typedef struct s_node
{
	t_node_type		type;
	char			*value;
	char			**args;
	struct s_node	*next;
}	t_node;

typedef struct s_exec
{
	int		prev_fd;
	int		pipe_fd[2];
	pid_t	*pids;
	int		cmd_count;
	int		cmd_index;
}	t_exec;

// Parsing functions
t_node	*parse_args(int argc, char **argv);
t_node	*parse_sequence(t_node *head, int argc, char **argv, int i);
t_node	*parse_standard_args(int argc, char **argv);
t_node	*parse_heredoc_args(int argc, char **argv);
t_node	*create_node(t_node_type type);
t_node	*parse_cmd_node(t_node *current, char **argv, int *i);
t_node	*parse_pipe_node(t_node *current);
t_node	*create_infile_node(char **argv);
int		parsing_mode(int argc, char **argv);

// Execution functions
int		execute_pipeline(t_node *head, char **envp);
void	setup_heredoc(t_node *heredoc_node);
void	setup_input(t_node *head);
int		setup_output(t_node *tail, t_node *head);
void	execute_command(t_node *cmd_node, char **envp, t_node *head);
int		count_commands(t_node *head);
char	*find_path(char *cmd, char **envp);
t_node	*find_tail(t_node *head);
void	handle_child_process(t_exec *exec, t_node *cmd,
			t_node *head, char **envp);
void	handle_sigpipe(t_node *head);
void	process_command(t_exec *exec, t_node *cmd, t_node *head, char **envp);
int		wait_for_children(t_exec *exec);

// Utility functions
void	free_split(char **split);
void	free_node_list(t_node *head);
void	perror_exit(char *msg, int exit_code, t_node *head);

#endif
