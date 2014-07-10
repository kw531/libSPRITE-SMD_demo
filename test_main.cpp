#include "artemis_if.h"

int main(int arc, char* argv[])
{
    fsw_init(argv[1]);

    for(unsigned int i = 0; i < 1000; ++i)
    {
        fsw_execute();
    }

    fsw_terminate();

    return 0;
}
