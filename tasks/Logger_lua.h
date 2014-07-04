
#ifndef __TASK_LOGGER_LUA_H__
#define __TASK_LOGGER_LUA_H__


#include "SCALE/LuaWrapper.h"
#include "tasks/Logger.h"


namespace task
{

    class Logger_lua
    {
        public:

            /**
             * The name regsitered with Lua to describe the class.
             */
            static const char class_name[];

            /**
             * The set of methods being exposed to Lua through the adapter
             * class.
             */
            static luaL_Reg methods[];

            /**
             * Because the SRTX::Scheduler is a Singleton, we cannot use the
             * default constructor to allocate a Scheduler. This function wraps
             * the Scheduler::get_instance function into a new allocator for
             * the Lua adapter.
             * @param L Pointer to the Lua state.
             * @return A pointer to the Task.
             */
            static Logger* allocator(lua_State* L)
            {
                return new Logger(luaL_checkstring(L, 1), luaL_checkstring(L, 2));
            }

            /**
             * Ragister the contents of this class as an adapter between Lua
             * and C++ representations of SRTX::Task.
             * @param L Pointer to the Lua state.
             * @return Number of elements being passed back through the Lua
             * stack.
             */
            static int register_class(lua_State* L)
            {
                SCALE::luaW_register<Logger>(L, "Logger", NULL, methods,
                        allocator);
                SCALE::luaW_extend<Logger, SRTX::Task>(L);
                return 0;
            }

    };

    const char Logger_lua::class_name[] = "Logger";

    luaL_Reg Logger_lua::methods[] =
    {
        {NULL, NULL}
    };

} //namespace

#endif // __TASK_LOGGER_LUA_H__
