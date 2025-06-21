/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:23:36 by odana             #+#    #+#             */
/*   Updated: 2025/06/21 22:59:11 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

/*
 * Node types for the linked list representing the pipeline:
 *  - NODE_INFILE:      input file
 *  - NODE_HEREDOC:     here-doc limiter
 *  - NODE_CMD:         a command with its args[]
 *  - NODE_PIPE:        explicit pipe delimiter
 *  - NODE_OUTFILE:     output file (truncate)
 *  - NODE_OUT_APPEND:  output file (append, e.g. in heredoc mode)
 */
typedef enum e_node_type
{
	NODE_INFILE,
	NODE_HEREDOC,
	NODE_CMD,
	NODE_PIPE,
	NODE_OUTFILE,
	NODE_OUT_APPEND
}	t_node_type;

/*
 * Linked-list node for each element/token in the pipeline description.
 *  - type: one of t_node_type
 *  - value: for infile/outfile filenames or heredoc limiter
 *  	(NULL for NODE_CMD and NODE_PIPE)
 *  - args: NULL-terminated array of strings for exec 
 * 		(only for NODE_CMD; NULL otherwise)
 *  - next: pointer to next node
 */
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

// execution logic
void	exec_pipeline(t_node *head, char **envp);

#endif
