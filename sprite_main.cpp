#include "SCALE/Scale_if.h"
#include "tasks/Logger_lua.h"
#include "tasks/SMD_lua.h"
#include "tasks/Feeder_lua.h"
#include "base/XPRINTF.h"


int main(int arc, char* argv[])
{
    SCALE::Scale_if& scale = SCALE::Scale_if::get_instance();

    /* Register my tasks with with the Lua executive.
     */

    task::Logger_lua::register_class(scale.state());
    task::SMD_lua::register_class(scale.state());
    task::Feeder_lua::register_class(scale.state());

    /* Execute the main script that drives the simulation.
     */
    if(false == scale.run_script(argv[1]))
    {
        EPRINTF("Failed executing script: %s\n", argv[1]);
        return -1;
    }

    return 0;
}
