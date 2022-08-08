/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:25 by alemarti          #+#    #+#             */
/*   Updated: 2022/08/08 12:39:37 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int	exec_cmd(char **cmd_args, char **paths, char *envp[])
{
	char	*bin;

	bin = which_bin(paths, cmd_args[0]);
	if (!bin)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	if (execve(bin, cmd_args, envp) <= -1)
	{
		ft_putstr_fd("pipex: command execution error: ", 2);
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	return (0);
}

char	*path_join(char *path, char *cmd)
{
	char	*res;
	int		i;
	int		j;

	i = -1;
	res = (char *)malloc(ft_strlen(path) + ft_strlen(cmd) + 2);
	while (path[++i])
		res[i] = path[i];
	res[i] = '/';
	j = i + 1;
	i = -1;
	while (cmd[++i])
	{
		res[j] = cmd[i];
		j++;
	}
	res[j] = 0;
	return (res);
}

char	*which_bin(char **paths, char *cmd)
{
	char	*bin;
	int		i;

	i = 0;
	while (paths[i])
	{
		bin = path_join(paths[i], cmd);
		if (access(bin, X_OK) == 0)
			return (bin);
		free(bin);
		i++;
	}
	return (NULL);
}
