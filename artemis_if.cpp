#include "SRTX/Scheduler.h"
#include "SCALE/Scale_if.h"
#include "tasks/Logger_lua.h"
#include "tasks/SMD_lua.h"
#include "base/XPRINTF.h"


int fsw_init(const char* const script)
{
    SRTX::Scheduler& sched = SRTX::Scheduler::get_instance();
    SCALE::Scale_if& scale = SCALE::Scale_if::get_instance();

    /* Set the scheduler to be trigger by an external timing source.
     */
    sched.use_external_trigger(true);

    /* Register my tasks with with the Lua executive.
     */
    task::Logger_lua::register_class(scale.state());
    task::SMD_lua::register_class(scale.state());

    /* Call the Lua init code.
     */
    lua_State* L = scale.state();
    luaL_dofile(L, script);
    lua_getfield(L, LUA_GLOBALSINDEX, "init");
    lua_call(L, 0, 0);

    return 0;
}


int fsw_execute()
{
    SRTX::Scheduler& sched = SRTX::Scheduler::get_instance();
    SCALE::Scale_if& scale = SCALE::Scale_if::get_instance();

    /* Call the Lua init code.
     */
    lua_State* L = scale.state();
    //luaL_dofile(L, script);
    lua_getfield(L, LUA_GLOBALSINDEX, "hello");
    lua_call(L, 0, 0);

    sched.lock();
    sched.trigger();
    sched.unlock();

    return 0;
}


int fsw_terminate()
{
    SCALE::Scale_if& scale = SCALE::Scale_if::get_instance();

    /* Call the Lua terminate code.
     */
    lua_State* L = scale.state();
    lua_getfield(L, LUA_GLOBALSINDEX, "terminate");
    lua_call(L, 0, 0);

    return 0;
}
