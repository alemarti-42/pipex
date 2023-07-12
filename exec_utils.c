/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:25 by alemarti          #+#    #+#             */
/*   Updated: 2023/07/12 11:56:22 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

static char	*path_join(char *paths, char *cmd)
{
	char	*res;
	int		i;
	int		j;

	i = -1;
	res = (char *)malloc(ft_strlen(paths) + ft_strlen(cmd) + 2);
	while (paths[++i])
		res[i] = paths[i];
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

static char	*which_bin(char **paths, char *cmd)
{
	char	*bin;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (!paths)
		return (NULL);
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

int	exec_cmd(char **cmd_args, char **paths, char *envp[])
{
	char	*bin;

	bin = which_bin(paths, cmd_args[0]);
	if (!bin)
	{
		put_error("command not found: ", cmd_args[0]);
		exit (127);
	}
	if (execve(bin, cmd_args, envp) < 0)
	{
		put_error("command execution error: ", cmd_args[0]);
		free(bin);
		exit (1);
	}
	return (0);
}
