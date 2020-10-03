#include "my_template.c"
void test()
{
    assert(3 > 4);
}
int main(int argc, char const *argv[])
{
    // assert(5 < 3);
    test();
    return 0;
}
