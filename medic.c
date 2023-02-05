/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:39:19 by htam              #+#    #+#             */
/*   Updated: 2023/02/03 20:39:20 by htam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	get_input_child(int *fd, t_arg arg)
{
	int		limiter_len;
	char	*str;

	limiter_len = ft_strlen(arg.v[2]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error("dup2 error");
	close(fd[0]);
	while (1)
	{
		str = get_next_line(0);
		if (ft_strncmp(arg.v[2], str, limiter_len) == 0
			&& str[limiter_len] == '\n')
		{
			free(str);
			exit(1);
		}
		write(fd[1], str, ft_strlen(str));
		free(str);
	}
	ft_error("something goes wrong");
}

void	get_input_parent(int child_id, int *fd)
{
	waitpid(child_id, NULL, 0);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_error("dup2 failed");
	close(fd[1]);
}

void	medic_childfactory(int	*fd, char *fullcmd, char **envp)
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

void	medic_parentlabour(t_arg arg)
{
	int		outfile_fd;
	char	**cmd;

	outfile_fd = open (arg.v[arg.c - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (outfile_fd == -1)
		ft_error("open outfile failed");
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		ft_error("dup2 failed");
	cmd = ft_split(arg.v[arg.c - 2], ' ');
	execve(get_path(cmd[0], arg.envp), cmd, NULL);
	ft_error("parent survived");
}

void	medic(t_arg arg)
{
	int		fd[2];
	int		child_id;
	int		n;

	if (pipe(fd) == -1)
		ft_error("pipe failed");
	child_id = fork();
	if (child_id == -1)
		ft_error("fork failed");
	if (child_id == 0)
		get_input_child(fd, arg);
	else
		get_input_parent(child_id, fd);
	n = 3;
	while (n < arg.c - 2)
	{
		if (pipe(fd) == -1)
			ft_error("pipe failed");
		medic_childfactory(fd, arg.v[n], arg.envp);
		n++;
	}
	medic_parentlabour(arg);
}
