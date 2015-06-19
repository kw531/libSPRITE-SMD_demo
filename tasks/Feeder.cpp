
#include "tasks/Feeder.h"
#include <string.h>
#include "SRTX/Reference_time.h"
#include "topics/SMD_topic.h"
#include "base/XPRINTF.h"
#include <units/Seconds.h>


namespace task
{

    Feeder::Feeder(const char* const name) :
        SRTX::Task(name),
        m_smd_telem(NULL)
    {
    }


    bool Feeder::init()
    {
        m_smd_telem = new SRTX::Subscription<telem::SMD_msg_t>
            (topics::smd_topic, get_period());

        if((NULL == m_smd_telem) || (false == m_smd_telem->is_valid()))
        {
            EPRINTF("Error creating SMD subscription\n");
            return false;
        }

        memset(&(m_smd_telem->content), 0, sizeof(m_smd_telem->content));

        return true;
    }


    bool Feeder::execute()
    {

        /* Use shorthand notation to reference the publication data.
        */
        telem::SMD_msg_t& msg = m_smd_telem->content;

	/* Get will subscribe to the data 
	*/
	m_smd_telem->get();

	/*Print the data on the screen as it is calculated, the data in the csv is of type g, therefore is more accurate
	the output here is of type float because of formatting
	*/

	IPRINTF("Time: %.1f, Position: %.5f, Velocity: %5.5f, Acceleration: %5.5f Ctrl-D to exit\n", double(msg.time), double(msg.position),
                double(msg.velocity), double(msg.acceleration));
	return true;
    }


    void Feeder::terminate()
    {
    }

} // namespace
