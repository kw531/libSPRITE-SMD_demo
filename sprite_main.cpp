#include <SRTX/Scheduler.h>
#include <base/XPRINTF.h>
#include <signal.h>

#include "tasks/Logger.h"
#include "tasks/SMD.h"

static volatile bool done(false);

static void kill_me_now(int)
{
    done = true;
}

static units::Nanoseconds HZ_to_period(unsigned int hz)
{
    return units::Nanoseconds(1*units::SEC / hz);
}

int main(int arc, char *argv[])
{
    /* Define the constants.
     */
    double k = 0.1;         // Spring constant
    double B = 0.25;        // Damper constant
    units::Grams mass(1.0); // in grams.
    const char *LOGFILE = "./smd.csv";

    /* Set up the signal handler.
     */
    signal(SIGINT, kill_me_now);

    /* Declare the task properties.
     */
    SRTX::Task_properties tp;
    SRTX::priority_t priority = SRTX::MAX_PRIO;

    /* Create the scheduler
     */
    tp.prio = priority;
    tp.period = HZ_to_period(10);
    SRTX::Scheduler &s = SRTX::Scheduler::get_instance();
    s.set_properties(tp);

    /* Create the SMD task
     */
    --tp.prio;
    task::SMD smd("SMD", k, B, mass);
    smd.set_properties(tp);

    /* Create the logger task
     */
    --tp.prio;
    tp.period = HZ_to_period(1);
    task::Logger logger("Logger", LOGFILE);
    logger.set_properties(tp);

    s.start();
    logger.start();
    smd.start();

    while(!done)
    {
        ;
    }

    smd.stop();
    logger.stop();
    s.stop();

    return 0;
}
