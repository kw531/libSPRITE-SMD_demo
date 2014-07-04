
#ifndef __TASK_SMD_H__
#define __TASK_SMD_H__

#include "SRTX/Task.h"
#include "SRTX/Publication.h"
#include "telem/SMD_msg.h"
#include <units/Grams.h>


/**
 *   <------ x ------>
 *
 *     k     |--------|
 *-@@@@@@@@@-|        |
 *           |    m   | <---- F
 *_|------|__|        |
 * |______|  |________|
 *
 *    B
 */

namespace task
{

    /**
     * This class manages interactions with the SMD receiver.
     */
    class SMD: public SRTX::Task
    {

        public:

            /**
             * Constructor.
             * @param name Task name.
             * @param spring_constant Spring constant (k)
             * @param damper_constant Damper constant (B)
             * @param mass Mass (m)
             */
            SMD(const char* const name, const double spring_constant,
            const double damper_constant, units::Grams mass);

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
            SRTX::Publication<telem::SMD_msg_t>* m_smd_telem;

            /**
             * Spring constant.
             */
            double m_k;

            /**
             * Damper constant.
             */
            double m_B;

            /**
             * Mass.
             */
            units::Grams m_mass;
    };

} // namespace

#endif // __TASK_SMD_H__
