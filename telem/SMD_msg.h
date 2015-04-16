
#ifndef __TELEM_SMD_MSG_H__
#define __TELEM_SMD_MSG_H__

#include "telem/Telem_msg.h"
#include <units/Seconds.h>
#include <units/Meters.h>
#include <units/Meterspersecond.h>
#include <units/Meterspersecondpersecond.h>

namespace telem
{

    /**
     * This is the SMD telemetry message type.
     */
    typedef struct : public Telem_msg_t
    {
        /**
         * The body of the telemetry message.
         */
        units::Seconds time;
        units::Meters position;
        units::Meterspersecond velocity;
        units::Meterspersecondpersecond acceleration;
    } SMD_msg_t;

} // namespace

#endif // __TELEM_SMD_MSG_H__
