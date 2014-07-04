
#include "Logger.h"
#include "queues/SMD_queue.h"
#include "base/XPRINTF.h"


namespace task
{

    Logger::Logger(const char* const name, const char* const logfile) :
        SRTX::Task(name),
        m_filename(logfile),
        m_ofp(NULL)
    {
    }


    bool Logger::init()
    {
        if (NULL == (m_ofp = fopen(m_filename, "wb+")))
        {
            EPRINTF("Error opening log file: %s\n", m_filename);
            return false;
        }

        /* Header for debug print.
        */
        fprintf(m_ofp, "time, position, velocity, acceleration\n");

        return true;
    }


    bool Logger::execute()
    {
        static queues::SMD_queue& smd_q = queues::SMD_queue::get_instance();
        static telem::SMD_msg_t smd_msg;

        while(false == smd_q.is_empty())
        {
            if(false == smd_q.read(smd_msg))
            {
                EPRINTF("Error reading data from SMD queue\n");
            }
            fprintf(m_ofp, "%g,%g,%g,%g\n",
                    double(smd_msg.time),
                    double(smd_msg.position),
                    double(smd_msg.velocity),
                    double(smd_msg.acceleration));
        }

        return true;
    }


    void Logger::terminate()
    {
        fclose(m_ofp);
    }

} // namespace
