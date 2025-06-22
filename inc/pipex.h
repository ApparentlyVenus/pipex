/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:12:09 by odana             #+#    #+#             */
/*   Updated: 2025/06/22 00:58:36 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

# include "../lib/inc/libft.h"
# include "../lib/inc/get_next_line.h"

char	*find_path(char *cmd, char **envp);
void	free_split(char **split);
void	execute_cmd(char *argv, char **envp);
void	perror_exit(char *msg);
void	child1(char **argv, char **envp, int *fd);
void	child2(char **argv, char **envp, int *fd);

#endif