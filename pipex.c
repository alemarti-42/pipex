#include "pipex.h"

//envp takes environment variables as a third argument for the main.
char    **get_path(char *envp[])
{
    while (*envp)
    {
        if (ft_strncmp(*envp, "PATH=", 5) == 0)
            return (ft_split(*envp + 5, ':'));        
        envp++;
    }
    return (NULL);
}

int main(int argc, char *argv[], char *envp[])
{
    int a = argc;
    char **str = argv;
    int     x = 4;
    int     i = 0;
    int     pid;
    char    **paths;

    // if (argc != 5)
    //     return (1);

    paths = get_path(envp);
    while (paths[i])
    {
        printf("\t%d->%s\n", i, *paths);
        printf("\t----->>%s\n", path_join(paths[i], "testing"));
        i++;
    }
    printf("\tplc----->>%s\n", path_join(paths[0], "testing"));
    printf("\tplc----->>%s\n", which_bin(paths, "ls"));



    


    return (0);

}
    // a = a;
    // str += 0;

    // pid = fork();
    // while (i < x)
    // {
    //     if ( pid > 0)
    //     {
    //         printf("Hello from Parent! i = %d\n", i);
    //         waitpid(pid);
    //         pid = fork();
    //     }
    //     else
    //         printf("Hello from Child! i = %d\n", i);

    //     i++;
    // }


    // for (int i = 0; i < x; i++)
    //     pid = fork();

    // if (pid == 0) {
    // a = a + 5;
    // printf("%d, %p\n", a, &a);
    // }
    // else {
    //     a = a - 5;
    //     printf("%d, %p\n", a, &a);
    // }


    // if (pid == 0)
    //     printf("Hello from Child! pid = %d\n", pid);
    // else
    //     printf("Hello from Parent pid = %d\n", pid);