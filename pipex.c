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

void check_leaks()
{
	system("leaks pipex");
}
//input format: "infile" "cmd1" "cmd2" "outfile"

int main(int argc, char *argv[], char *envp[])
{
    int 		a = argc;
    char		**str = argv;
    int			x = 4;
    int			i = 0;
    int			pid;
    char		**paths;
    char		*bin;
    char		**cmd_args;
	int			fd_out;
	int			fd_in;
	int			fd_pipe[2];
	t_environ	*environ;

	//atexit(check_leaks);
    //open infile and outfile
	pipe(fd_pipe);
	if (argc < 4)
		return(0);
	environ = init_environ(argv[1], argv[argc - 1], envp);
	// Comprobar con access que se puede acceder a lso ficheros
	// La apertura de los ficheros se hara en los hijos
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error creando procesos\n", 2);
	}
	else if (pid == 0)
		reader_child(fd_pipe, argv[2], environ);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("Error creando procesos\n", 2);
		}
		else if (pid == 0)
			writer_child(fd_pipe, argv[3], environ);
	}
	//waitpid(pid, NULL, 0);

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