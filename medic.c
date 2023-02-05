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

void	medic(t_arg arg)
{
	int		fd[2];
	char	*str;
	int		child_id;
	int		limiter_len;
	int		outfile_fd;
	int		n;
	char	**cmd;

	if (arg.c < 6)
		ft_error("argc error");
	n = 3;
	
	limiter_len = ft_strlen(arg.v[2]);
	pipe(fd);
	child_id = fork();
	if (child_id == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		while (1)
		{
			str = get_next_line(0);
			if (ft_strncmp(arg.v[2], str, limiter_len) == 0 && str[limiter_len] == '\n')
			{
				free(str);
				exit(1) ;
			}
			write(fd[1], str, ft_strlen(str));
			free(str);
		}
	}
	else
	{
		waitpid(child_id, NULL, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
	}
	while (n < arg.c - 2)
	{
		pipe(fd);
		child_id = fork();
		if (child_id == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			cmd = ft_split(arg.v[n], ' ');
			execve(get_path(cmd[0], arg.envp), cmd, NULL);
		}
		else
		{
			waitpid(child_id, NULL, 0);
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
		}
		n++;
	}
	write(2, "here\n", 5);
	outfile_fd = open (arg.v[arg.c - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	dup2(outfile_fd, STDOUT_FILENO);
	cmd = ft_split(arg.v[arg.c - 2], ' ');
	execve(get_path(cmd[0], arg.envp), cmd, NULL);
}