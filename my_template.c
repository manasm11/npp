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

int exitt(int status)
{
    _exit(status);
}

// int main(int argc, char const *argv[])
// {
//     pinfo("Do you get this info ???\n");
//     perror("Error message test\n")  && exitt(0);
//     pdebug("Does this gets printed ???\n");
//     return 0;
// }
