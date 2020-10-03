// Executing ping -c 5 google.com| grep rtt
#include "my_template.c"
#include "Commands.c"

int main(int argc, char const *argv[])
{
    Command cmds[2];
    strcpy(cmds[0].cmd_str, "ping");
    strcpy(cmds[0].path, "/usr/bin/ping");
    cmds[0]. = "/usr/bin/ping";
    cmds[0].cmd_str = "ping";
    cmds[0].cmd_str = "ping";
    char ***args_list = {{"ping", "-c", "5", "google.com", NULL}, {"grep", "rtt", NULL}};
    char **path_list = {"/usr/bin/ping", "/usr/bin/grep"};
    int fd[2];
    pipe(fd);
    loopi(2)
    {
        if (!fork())
        {
            dup2(fd[1], 1);
            close(fd[0]);
            close(fd[1]);
            char **args = ;
            execv(path_list[i], args);
        }
    }
    // if (!fork())
    // {
    //     dup2(fd[0], 0);
    //     close(fd[0]);
    //     close(fd[1]);
    //     execle(, );
    // }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    psuccess("EXECUTED SUCCESSFULLY !!!\n");
    return 0;
}
