/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:23:36 by odana             #+#    #+#             */
/*   Updated: 2025/06/22 01:16:31 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

// parsing logic + utils
t_node	*parse_args(int argc, char **argv);
t_node	*parse_sequence(t_node *head, int argc, char **argv, int i);
t_node	*parse_standard_args(int argc, char **argv);
t_node	*parse_heredoc_args(int argc, char **argv);
t_node	*create_node(t_node_type type);
t_node	*parse_cmd_node(t_node *current, char **argv, int *i, int *cmd);
t_node	*parse_pipe_node(t_node *current, char **argv, int *i, int *cmd);
t_node	*create_infile_node(char **argv);
int		parsing_mode(int argc, char **argv);
void	free_split(char **split);
void	free_node_list(t_node *head);

// execution logic
void	exec_pipeline(t_node *head, char **envp, int fd[2]);
void	process_infile(t_node *infile);
void	process_outfile(t_node *outfile);
void	process_child(t_node *node, int prev_fd, int fd[2], char **envp);
void	handle_heredoc(t_node	*heredoc);
void	exec_cmd(t_node *node, char **envp);
char	*find_path(char *cmd, char **envp);
void	perror_exit(char *msg);

#endif
