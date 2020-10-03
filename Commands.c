#define PATH_SIZE 256
#define CMD_STR_SIZE 256
#define MAX_CMDS 16

typedef struct
{
    char path[PATH_SIZE];
    char cmd_str[CMD_STR_SIZE];
    char **args;
    int pid;
    int stat;
    int multi_write;
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
        cmds[i].multi_write = 0;
    }
}