#include "artemis_if.h"
#include <SRTX/RTC.h>

int main(int arc, char* argv[])
{
    fsw_init(argv[1]);

    SRTX::sleep(units::Nanoseconds(10 * units::MSEC));
    for(unsigned int i = 0; i < 1000; ++i)
    {
        fsw_execute();
        SRTX::sleep(units::Nanoseconds(5 * units::MSEC));
    }

    fsw_terminate();

    return 0;
}
