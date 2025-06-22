/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:14:09 by odana             #+#    #+#             */
/*   Updated: 2025/06/22 10:33:16 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	child1(char **argv, char **envp, int *fd)
{
	int	filein;

	filein = open(argv[1], O_RDONLY);
	if (filein < 0)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(filein, STDIN_FILENO) < 0)
		perror_exit("dup2 infile");
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		perror_exit("dup2 pipe write");
	close(filein);
	close(fd[0]);
	close(fd[1]);
	execute_cmd(argv[2], envp);
	perror("execute_cmd");
	exit(EXIT_FAILURE);
}

void	child2(char **argv, char **envp, int *fd)
{
	int	fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout < 0)
	{
		perror(argv[4]);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd[0], STDIN_FILENO) < 0)
		perror_exit("dup2 pipe read");
	if (dup2(fileout, STDOUT_FILENO) < 0)
		perror_exit("dup2 outfile");
	close(fileout);
	close(fd[0]);
	close(fd[1]);
	execute_cmd(argv[3], envp);
	perror("execute_cmd");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (argc != 5)
		perror_exit("incorrect number of args");
	if (pipe(fd) < 0)
		perror_exit("pipe");
	pid1 = fork();
	if (pid1 < 0)
		perror_exit("fork");
	if (pid1 == 0)
		child1(argv, envp, fd);
	pid2 = fork();
	if (pid2 < 0)
		perror_exit("fork");
	if (pid2 == 0)
		child2(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	exit(WEXITSTATUS(status));
}
