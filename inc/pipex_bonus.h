/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:23:36 by odana             #+#    #+#             */
/*   Updated: 2025/06/21 12:12:35 by odana            ###   ########.fr       */
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

/*
 * Parse command-line arguments into a linked list including NODE_PIPE nodes.
 * argv must include literal "|" tokens 
 * 	(quoted/escaped so shell doesn’t intercept).
 * Returns head of list on success, or NULL on error (syntax issues, OOM).
 *
 * Usage:
 *   Normal:   ./pipex infile cmd1_args... "|" cmd2_args... ... outfile
 *   Heredoc:  ./pipex here_doc LIMIT cmd1_args... "|" cmd2_args... ... outfile
 */
t_node	*parse_args_with_pipes(int argc, char **argv);

/*
 * Free the entire linked list, including strdup’d strings and args arrays.
 */
void	free_node_list(t_node *head);

/*
 * Execute the pipeline described by the linked list:
 *  - Opens infile or handles heredoc
 *  - Forks each NODE_CMD in sequence, wiring stdin/stdout via pipes or outfile
 *  - Closes FDs appropriately and waits for children
 * envp is passed through for exec.
 */
void	exec_pipeline(t_node *head, char **envp);

#endif
