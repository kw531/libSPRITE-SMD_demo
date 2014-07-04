
#ifndef __QUEUES_SMD_QUEUE_H__
#define __QUEUES_SMD_QUEUE_H__

#include "SRTX/Ring_buffer.h"
#include "telem/SMD_msg.h"

namespace queues
{

    /**
     * Define some constants.
     */
    namespace
    {
        /**
         * Depth of the SMD telemetry queue.
         */
        const unsigned int SMD_QUEUE_DEPTH = 200;
    }


    /**
     * This class is defines the SMD message queue.
     * This class is a singleton defining a queue that stores SMD telemetry
     * messages.
     */
    class SMD_queue: public SRTX::Ring_buffer<telem::SMD_msg_t>
    {
        public:

            /**
             * Accessor to a get a reference to the SMD_queue class.
             * @return a Reference to the SMD queue.
             */
            static SMD_queue& get_instance()
            {
                static SMD_queue instance;
                return instance;
            }

        private:

            /**
             * Constructor.
             * The constructor is made private as part of the singleton
             * pattern.
             */
            SMD_queue() :
                SRTX::Ring_buffer<telem::SMD_msg_t>(SMD_QUEUE_DEPTH)
        {
        }

            /**
             * Copy constructor.
             * The copy constructor is made private as part of the singleton
             * pattern.
             */
            SMD_queue(const SMD_queue&);

            /**
             * Assignment operator.
             * The assignment operator is made private as part of the singleton
             * pattern.
             */
            SMD_queue& operator=(const SMD_queue&);

    };

} // namespace

#endif // __QUEUES_SMD_QUEUE_H__
