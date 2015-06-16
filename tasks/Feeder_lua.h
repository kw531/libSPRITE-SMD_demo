
#ifndef __TASK_FEEDER_LUA_H__
#define __TASK_FEEDER_LUA_H__


#include "SCALE/LuaWrapper.h"
#include "tasks/Feeder.h"


namespace task
{

    class Feeder_lua
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
            static Feeder* allocator(lua_State* L)
            {
                return new Feeder(luaL_checkstring(L, 1));
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
               luaW_register<Feeder>(L, "Feeder", NULL, methods, allocator);
               luaW_extend<Feeder, SRTX::Task>(L);
                return 0;
            }

    };

    const char Feeder_lua::class_name[] = "Feeder";

    luaL_Reg Feeder_lua::methods[] =
    {
        {NULL, NULL}
    };

} //namespace

#endif // __TASK_FEEDER_LUA_H__
