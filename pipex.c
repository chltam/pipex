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

void	error(char *str)
{
	perror(str);
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
	return (0);	
				
}
int	pipex(char **argv, char **envp)
{
	int	fd[2];
	int	outfile_fd;
	char **cmd;
	int child_id;

	
	pipe(fd);
	child_id = fork();
	if (child_id == 0)
	{
		int	infile_fd = open(argv[1], O_RDONLY);
		cmd = ft_split(argv[2], ' ');
		dup2(infile_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execve(get_path(cmd[0], envp), cmd, NULL);

	}
	else
	{
		waitpid(child_id, NULL, 0);
		outfile_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		cmd = ft_split(argv[3], ' ');
		dup2(outfile_fd, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		execve(get_path(cmd[0], envp), cmd, NULL);
	}
	
	exit(0);
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
		error("ERROR");

	pipex(argv, envp);
	return (0);


}
