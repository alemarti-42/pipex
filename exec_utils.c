#include"pipex.h"

int exec_cmd(char **cmd_args, char **paths, char *envp[])
{
    char	*bin;

    bin = which_bin(paths, cmd_args[0]);
	 if (!bin)
	 	return (-1);
    return (execve(bin, cmd_args, envp));

}

char    *path_join(char *path, char *cmd)
{
    char    *res;
    int     i;
    int     j;

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

char    *which_bin(char **paths, char *cmd)
{
    char    *bin;
    int     i;

    i = 0;
    while (paths[i])
    {
        bin = path_join(paths[i], cmd);
        if (access(bin, F_OK) == 0)
            return (bin);
        free(bin);
        i++;
    }
	return (NULL);
}
