
#ifndef __TASK_SMD_LUA_H__
#define __TASK_SMD_LUA_H__


#include "SCALE/LuaWrapper.h"
#include "tasks/SMD.h"


namespace task
{

    class SMD_lua
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
            static SMD* allocator(lua_State* L)
            {
                return new SMD(luaL_checkstring(L, 1), luaL_checknumber(L, 2),
                        luaL_checknumber(L, 3), units::Grams(luaL_checknumber(L, 4)));
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
                luaW_register<SMD>(L, "SMD", NULL, methods, allocator);
               luaW_extend<SMD, SRTX::Task>(L);
                return 0;
            }

    };

    const char SMD_lua::class_name[] = "SMD";

    luaL_Reg SMD_lua::methods[] =
    {
        {NULL, NULL}
    };

} //namespace

#endif // __TASK_SMD_LUA_H__
