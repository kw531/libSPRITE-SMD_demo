
#ifndef __TELEM_TELEM_MSG_H__
#define __TELEM_TELEM_MSG_H__

#include "units/Nanoseconds.h"

namespace telem
{

    /**
     * Define ids for telemetry sources.
     */
    typedef enum
    {
        TELEM_ID_SMD = 1,
    } Telem_source_id_t;


    /**
     * Define the head of a telemetry message.
     * It is expected that concrete telemetry message will inherit and extend this struct.
     */
    typedef struct
    {
        /**
         * Message timestamp.
         */
        units::Nanoseconds ref_time;
        /**
         * An identifier that uniquely indentifies the data source.
         */
        Telem_source_id_t source_id;
        /**
         * Number of bytes of data in the payload of the message.
         */
        uint8_t nbytes;
    } Telem_msg_t;

} // namespace

#endif // __TELEM_TELEM_MSG_H__
