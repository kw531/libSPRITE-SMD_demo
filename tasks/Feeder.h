
#ifndef __TASK_FEEDER_H__
#define __TASK_FEEDER_H__

#include <stdio.h>
#include "SRTX/Task.h"
#include "SRTX/Subscription.h"
#include "telem/SMD_msg.h"



namespace task
{

    /**
     * This class manages interactions with the SMD receiver.
     */
    class Feeder: public SRTX::Task
    {

        public:

            /**
             * Constructor.
             * @param name Task name.

             */
            Feeder(const char* const name);

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
             * SMD telemetry data publication.
             */
            SRTX::Subscription<telem::SMD_msg_t>* m_smd_telem;

    };

} // namespace

#endif // __TASK_FEEDER_H__
