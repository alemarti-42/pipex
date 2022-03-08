#include"pipex.h"

int open_infile(char *infile)
{
    if (access(infile, F_OK) == -1)
    {
        ft_putstr_fd("pipex:", 2);
        ft_putstr_fd(infile, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return (0);
    }
    return (open(infile, O_RDONLY));
}

void    redirection(char *cmd, char **env, int fdin)
{
    int     pid;
    int     pipefd[2];
}