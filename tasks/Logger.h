
#ifndef __TASK_LOGGER_H__
#define __TASK_LOGGER_H__

#include <stdio.h>
#include "SRTX/Task.h"

namespace task
{

    /**
     * This class manages interactions with the Logger receiver.
     */
    class Logger: public SRTX::Task
    {

        public:

            /**
             * Constructor.
             * @param name Task name.
             */
            Logger(const char* const name, const char* const logfile);

            /**
             * Initialization routine.
             * @return true on success or false on failure.
             */
            bool init();

            /**
             * This the the function that gets executed on a periodic basis
             * each time this task is scheduler to run.
             * @return Return true to continue execution or false to terminate
             * the task.
             */
            bool execute();

            /**
             * Terminate routine.
             */
            void terminate();

        private:

            /**
             * Logfile name.
             */
            const char* const m_filename;

            /**
             * File pointer.
             */
            FILE* m_ofp;
    };

} // namespace

#endif // __TASK_LOGGER_H__
