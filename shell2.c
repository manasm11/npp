#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#define assert(exp)                                                                                            \
    if (!(exp) && printf("[-] ERROR in file: %s at line: %d in function: %s\n", __FILE__, __LINE__, __func__)) \
        _exit(1);

#define newline printf("\n")
#define pinfo printf("[#] ") && printf
#define pdebug printf("[*] ") && printf
#define perror printf("[-] ") && printf
#define psuccess printf("[+] ") && printf
#define pdebug_int(variable_name, variable) printf("[*] %s = %d\n", variable_name, variable)
#define pdebug_string(variable_name, variable) printf("[*] %s = %s\n", variable_name, variable)

#define loopi(n) for (int i = 0; i < n; i++)
#define loopj(n) for (int i = 0; i < n; i++)
#define loops(str, temp) for (char *temp = str; *temp != '\0'; temp++)

int _str_len(char *string)
{
    int n = 0;
    while (string[n++] != '\0')
        ;
    return n;
}

void _trim(char *string)
{
    int i = _str_len(string) - 1;
    while (string[i] == ' ' || string[i] == '\t' || string[i] == '\n')
        string[i--] = '\0';
    char *temp = string;
    while (*temp == ' ' || *temp == '\t' || *temp == '\n')
        temp++;
    strcpy(string, temp);
}

#define PATH_SIZE 1024
#define CMD_STR_SIZE 1024
#define MAX_CMDS 16

typedef struct
{
    char path[PATH_SIZE];
    char cmd_str[CMD_STR_SIZE];
    char **args;
    int pid;
    int stat;
    // int multi_write;
} Command;

void _initialize_cmds(Command *cmds)
{
    loopi(MAX_CMDS)
    {
        strcpy(cmds[i].path, "");
        strcpy(cmds[i].cmd_str, "");
        cmds[i].args = NULL;
        cmds[i].pid = -1;
        cmds[i].stat = -1;
        // cmds[i].multi_write = 0;
    }
}
static int n_cmds = 0;
enum
{
    READ,
    WRITE
};

int take_cmd(char cmd_str[CMD_STR_SIZE])
{
    char cwd[PATH_SIZE];
    getcwd(cwd, PATH_SIZE);

    printf(" \e[7m%s\e[0m\n$$$ ", cwd);
    char test;
    scanf("%[^\n]s", cmd_str);
    getchar();
    fflush(stdin);
    return 1;
}

int print_cmds(Command cmds[MAX_CMDS])
{
    loopi(n_cmds)
    {
        printf("\e[92m[#] %-8s:\tpid = %d\t", cmds[i].cmd_str, cmds[i].pid);
        printf("stat = %d\e[0m\n", cmds[i].stat);
    }
    return 1;
}

void _parse_cmd(char *cmd_str_orig, Command *cmd)
{
    int first = 1;
    char *cmd_str = (char *)malloc(sizeof(char) * CMD_STR_SIZE);
    strcpy(cmd_str, cmd_str_orig);
    char *token = strtok(cmd_str, " \0");
    cmd->args = (char **)malloc(8 * sizeof(char *));
    int n_args = 0;
    while (token != NULL)
    {
        if (first)
            strcpy(cmd->cmd_str, token) && (first = 0);
        cmd->args[n_args++] = token;
        token = strtok(NULL, " ");
    }
    cmd->args[n_args] = NULL;
}

int parse_cmds(char cmd_str[CMD_STR_SIZE], Command cmds[MAX_CMDS])
{
    int n_pipes = 0;
    loops(cmd_str, temp)
    {
        if (*temp == '|')
        {
            *temp = '\0';
            n_pipes++;
        }
    }
    n_cmds = n_pipes + 1;
    char *temp = cmd_str;
    loopi(n_cmds)
    {
        _trim(temp);
        while (*temp == '\0')
            temp++;
        _parse_cmd(temp, &cmds[i]);
        temp += _str_len(temp);
    }
}

int _search_path_cmd(Command *cmd)
{
    char *opath = getenv("PATH");
    char paths[512];
    strcpy(paths, opath);
    char *dir;

    for (dir = strtok(paths, ":"); dir; dir = strtok(NULL, ":"))
    {
        strcpy(cmd->path, dir);
        strcat(cmd->path, "/");
        strcat(cmd->path, cmd->cmd_str);
        if (access(cmd->path, F_OK) != -1)
            return 0;
    }
    return -1;
}

int search_path_cmds(Command cmds[MAX_CMDS])
{
    loopi(n_cmds)
    {
        if (_search_path_cmd(cmds + i) < 0)
        {
            perror("Command: %s not found !!!\n", cmds[i].cmd_str);
            return -1;
        }
    }
    return 0;
}

int execute_cmds(Command *cmds)
{
    int fd[2];
    fd[0] = 0;
    fd[1] = 1;
    pid_t pid;
    int fdd = 0;
    Command *cmd = cmds;
    while (strcmp(cmd->path, ""))
    {
        pipe(fd);
        if ((pid = fork()) == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            dup2(fdd, 0);
            if (strcmp((cmd + 1)->path, ""))
            {
                dup2(fd[1], 1);
            }
            close(fd[0]);
            execv(cmd->path, cmd->args);
            exit(1);
        }
        else
        {
            cmd->pid = pid;
            wait(&(cmd->stat));
            close(fd[1]);
            fdd = fd[0];
            cmd++;
        }
    }
}

void _handler_quit(int sig)
{
    char continue_[4];
    printf("\nInterrupt received !!!\nDo you wish to continue ??? ");
    scanf("%s", continue_);
    if (!strcasecmp("y", continue_) || !strcasecmp("yes", continue_))
    {
        printf("HAVE A GREAT DAY !!!\n\n");
        exit(0);
    }
    else
    {
        printf("Press enter to continue.\n");
    }
}

int main(int argc, char const *argv[])
{
    signal(SIGQUIT, _handler_quit);
    signal(SIGINT, _handler_quit);
    do
    {
        Command cmds[MAX_CMDS];
        _initialize_cmds(cmds);
        char cmd_str[CMD_STR_SIZE];
        take_cmd(cmd_str);
        parse_cmds(cmd_str, cmds);
        if (search_path_cmds(cmds) == -1)
            continue;
        execute_cmds(cmds);
        print_cmds(cmds);
    } while (1);

    return 0;
}
