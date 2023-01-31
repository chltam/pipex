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
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "./libft/libft.h"
#include "pipex.h"

void	ft_error(char *str)
{
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
}

char	*get_path(char *cmd, char *envp[])
{
	char	**allpath;
	char	*tempcmd;
	char	*path;

	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		*envp++;
	*envp += 5;
	allpath = ft_split(*envp, ':');
	tempcmd = ft_strjoin("/", cmd);
	while (*allpath)
	{
		path = ft_strjoin(*allpath, tempcmd);
		if (access(path, F_OK) == 0)
		{
			free(tempcmd);
			return (path);
		}
		else
		{
			free(path);
			*allpath++;
		}
	}
	free(tempcmd);
	ft_error("No such command");
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

void	pipex(char **argv, char **envp)
{
	int		fd[2];
	int		outfile_fd;
	char	**cmd;
	int		child_id;
	int		infile_fd;

	if (pipe(fd) == -1)
		ft_error("pipe failed");
	child_id = fork();
	if (child_id == -1)
		ft_error("fork failed");
	if (child_id == 0)
	{
		// infile_fd = open(argv[1], O_RDONLY);
		// cmd = ft_split(argv[2], ' ');
		// dup2(infile_fd, STDIN_FILENO);
		// dup2(fd[1], STDOUT_FILENO);
		// close(fd[0]);
		// execve(get_path(cmd[0], envp), cmd, NULL);
		childlabour(fd, argv, envp);
	}
	else
	{
		waitpid(child_id, NULL, 0);
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
	//ft_error("ERROR");
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
		ft_error("argc ERROR");
	pipex(argv, envp);
	return (0);
}
