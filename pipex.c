/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:44 by alemarti          #+#    #+#             */
/*   Updated: 2023/06/20 12:42:42 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char *envp[])
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

void	put_error(char *text, char *element)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(text, 2);
	ft_putstr_fd(element, 2);
	ft_putstr_fd("\n", 2);
}

void	free_environ(t_environ *environ)
{
	if (environ->paths)
		free_split(environ->paths);
	free(environ);
}

int	init_pipes(int pipes[1024][2], int n_pipes)
{
	int	i;

	i = -1;
	while (++i < n_pipes)
	{
		if (pipe(pipes[i]))
		{
			return (-1);
		}
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int			fd_pipe[1024][2];
	t_environ	*environ;
	int			i;

	i = 0;
	if (argc < 5)
	{
		ft_putstr_fd("pipex: wrong number of arguments\n", 2);
		return (0);
	}
	environ = 0;
	environ = init_environ(argv[1], argv[argc - 1], envp);
	environ->n_cmd = argc - 3;
	if (open_files(environ) < 0)
		return (0);
	if (init_pipes(fd_pipe, argc - 4))
	{
		return (-1);
	}
	spawn_children(environ, argv, fd_pipe);
	free_environ(environ);
	return (0);
}
