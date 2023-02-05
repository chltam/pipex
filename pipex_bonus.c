/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:19:19 by htam              #+#    #+#             */
/*   Updated: 2023/01/28 17:19:21 by htam             ###   ########.fr       */
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

void	childfactory(int *fd, char *fullcmd, char **envp)
{
	char	**cmd;
	int		child_id;

	child_id = fork();
	if (child_id == -1)
		ft_error("fork failed");
	if (child_id == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_error("dup2 failed(child)");
		cmd = ft_split(fullcmd, ' ');
		close(fd[0]);
		execve(get_path(cmd[0], envp), cmd, NULL);
		ft_error("child survived");
	}
	else
	{
		waitpid(child_id, NULL, 0);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_error("dup2 error");
		close(fd[1]);
	}
	return ;
}

void	parentlabour(t_arg arg)
{
	int		outfile_fd;
	char	**cmd;

	outfile_fd = open(arg.v[arg.c - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (outfile_fd == -1)
		ft_error("open outfile failed");
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		ft_error("dup2 failed");
	cmd = ft_split(arg.v[arg.c - 2], ' ');
	execve(get_path(cmd[0], arg.envp), cmd, NULL);
	ft_error("parent survived");
}

void	pipex(t_arg arg)
{
	int		fd[2];
	int		n;
	int		infile_fd;

	n = 2;
	infile_fd = open(arg.v[1], O_RDONLY);
	if (infile_fd == -1)
		ft_error("open infile failed");
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		ft_error("dup2 error");
	while (n < arg.c - 2)
	{
		if (pipe(fd) == -1)
			ft_error("pipe failed");
		childfactory(fd, arg.v[n], arg.envp);
		n++;
	}
	wait(NULL);
	parentlabour(arg);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_arg	arg;

	arg.c = argc;
	arg.v = argv;
	arg.envp = envp;
	if (argc < 5)
		ft_error("argc error");
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		medic(arg);
	else
		pipex(arg);
	return (0);
}
