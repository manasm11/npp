#include <stdio.h>

int main(int argc, char const *argv[])
{
    ppe("Testing info\n");
    return 0;
}
#define ppi         \
    printf("[#] "); \
    printf
#define ppd         \
    printf("[*] "); \
    printf
#define ppe         \
    printf("[-] "); \
    printf
#define pps         \
    printf("[+] "); \
    printf
#define ppdi(variable_name, variable) printf("[*] %s = %d\n", variable_name, variable)
#define ppds(variable_name, variable) printf("[*] %s = %s\n", variable_name, variable)
