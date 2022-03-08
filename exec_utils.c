#include"pipex.h"

int exec_cmd(char *cmd, char **paths)
{

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

char    *which_bin(char *cmd, char **paths)
{
    char    *bin;

    while (*paths)
    {

    }
}