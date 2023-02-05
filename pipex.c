/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:23:18 by htam              #+#    #+#             */
/*   Updated: 2023/01/24 11:23:20 by htam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *str)
{
	write(2, "\033[0;31m", 8);
	write(2, str, ft_strlen(str));
	write(2, "\033[0;39m", 8);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	childlabour(int *fd, char **argv, char **envp)
{
	int		infile_fd;
	char	**cmd;

	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
		ft_error("open infile failed");
	cmd = ft_split(argv[2], ' ');
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		ft_error("dup2 failed");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error("dup2 failed");
	close(fd[0]);
	execve(get_path(cmd[0], envp), cmd, NULL);
	ft_error("ERROR! child survived");
}

void	parentlabour(int *fd, char **argv, char **envp)
{
	int		outfile_fd;
	char	**cmd;

	outfile_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (outfile_fd == -1)
		ft_error("open outfile failed");
	cmd = ft_split(argv[3], ' ');
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		ft_error("dup2 failed");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_error("dup2 failed");
	close(fd[1]);
	execve(get_path(cmd[0], envp), cmd, NULL);
	ft_error("ERROR");
}

void	pipex(char **argv, char **envp)
{
	int		fd[2];
	int		child_id;

	if (pipe(fd) == -1)
		ft_error("pipe failed");
	child_id = fork();
	if (child_id == -1)
		ft_error("fork failed");
	if (child_id == 0)
		childlabour(fd, argv, envp);
	else
	{
		waitpid(child_id, NULL, 0);
		parentlabour(fd, argv, envp);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
		ft_error("argc error");
	pipex(argv, envp);
	return (0);
}
