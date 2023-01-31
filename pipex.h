/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:14:05 by htam              #+#    #+#             */
/*   Updated: 2023/01/26 21:14:07 by htam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
#define PIPEX_H

#include <sys/stat.h>
#include <fcntl.h>

typedef struct	s_pipex{
	int		i;
	char	**cmd;
	char	**path;
	
} t_pipex;














#endif
