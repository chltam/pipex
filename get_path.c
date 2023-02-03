/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:53:36 by htam              #+#    #+#             */
/*   Updated: 2023/02/03 16:53:38 by htam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*valid_path(char **allpath, char *cmd)
{
	char	*tempcmd;
	char	*path;

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
			allpath++;
		}
	}
	free(tempcmd);
	return (NULL);
}

char	*get_path(char *cmd, char *envp[])
{
	char	**allpath;
	char	*path;

	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	*envp += 5;
	allpath = ft_split(*envp, ':');
	path = valid_path(allpath, cmd);
	if (path)
	{
		free(allpath);
		return (path);
	}
	else
	{
		free(allpath);
		ft_error("No such command");
		return (NULL);
	}
}
