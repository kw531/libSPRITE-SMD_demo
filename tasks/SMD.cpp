
#include "tasks/SMD.h"
#include <string.h>
#include "SRTX/Reference_time.h"
#include "topics/SMD_topic.h"
#include "queues/SMD_queue.h"
#include "base/XPRINTF.h"
#include <units/Seconds.h>


namespace task
{

    /**
     * Integrate one step in the spring-mass-damper system.
     * @param smd_data Telemetry and log data.
     * @param B Damping constant.
     * @param k Spring constant.
     * @param m Mass.
     * @param dt Integration timestep.
     */
    static void smd_step(telem::SMD_msg_t& smd_data, const double B,
            const double k, const units::Grams m, const units::Seconds dt)
    {
        /* Calculate the acceleration.
         */
        smd_data.acceleration = units::Meterspersecondpersecond(
                (-B * double(smd_data.velocity) - k * double(smd_data.position)) / m);

        /* Integrate acceleration to get velocity.
         */
        smd_data.velocity += units::Meterspersecond(smd_data.acceleration * dt);

        /* Integrated velocity to get the position.
         */
        smd_data.position += units::Meters(smd_data.velocity * dt);

        return;
    }


    SMD::SMD(const char* const name, const double spring_constant,
            const double damper_constant, units::Grams mass) :
        SRTX::Task(name),
        m_smd_telem(NULL),
        m_k(spring_constant),
        m_B(damper_constant),
        m_mass(mass)
    {
    }


    bool SMD::init()
    {
        m_smd_telem = new SRTX::Publication<telem::SMD_msg_t>
            (topics::smd_topic, get_period());
        if((NULL == m_smd_telem) || (false == m_smd_telem->is_valid()))
        {
            EPRINTF("Error creating SMD publication\n");
            return false;
        }

        memset(&(m_smd_telem->content), 0, sizeof(m_smd_telem->content));

        /* Give the mass an initial position.
         */
        m_smd_telem->content.position = units::Meters(10.0);

        return true;
    }


    bool SMD::execute()
    {
        /* Set the step size to the period of the task for realtime. If
         * aperiodic, use the dt provide at initialization.
         */
        units::Seconds period(get_period());
        const units::Seconds default_dt(0.1);
        const units::Seconds dt((0.0 == double(period)) ? default_dt : period); // @todo: make configurable.
        static SRTX::Reference_time& ref_time = SRTX::Reference_time::get_instance();
        static queues::SMD_queue& smd_q = queues::SMD_queue::get_instance();

        static units::Seconds time(0.0);

        /* Use shorthand notation to reference the publication data.
        */
        telem::SMD_msg_t& msg = m_smd_telem->content;

        DPRINTF("%g,%g,%g,%g\n", double(time), double(msg.position),
                double(msg.velocity), double(msg.acceleration));

        /* Do the math.
         */
        smd_step(msg, m_B, m_k, m_mass, dt);

        /* Increment time.
         */
        msg.time = time;
        time += dt;

        /* Timestamp the message with the SRTX reference time.
        */
        msg.ref_time = ref_time.get_time();

        /* Set the message source id.
        */
        msg.source_id = telem::TELEM_ID_SMD;

	/* Put will publish the data 
	*/
	m_smd_telem->put();

        /* Put the data in the queue for the logger.
        */
        if(false == smd_q.write(msg))
        {
            EPRINTF("Error posting data to queue\n");
        }

        return true;
    }


    void SMD::terminate()
    {
    }

} // namespace
