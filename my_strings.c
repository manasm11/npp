
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
