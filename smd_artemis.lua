package.path = '/usr/local/lib/SPRITE/?.lua;' .. package.path
local s = require 'scheduler'

--------------------------------------------------------------------------------
-- Set some constants.
--------------------------------------------------------------------------------

k = 0.1  -- Spring constant
B = 0.25 -- Damper constant
mass = 1.0 -- in grams.

LOGFILE = "./smd.csv"

--------------------------------------------------------------------------------
-- Start programming
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
-- Init function
--------------------------------------------------------------------------------
function init()

    -- Create task properties and set an initial priority.
    tp = Task_properties.new()

    -- Create the scheduler.
    SCHEDULER_PERIOD = s.HZ_to_period(10)
    scheduler = s.create(tp, SCHEDULER_PERIOD)
    scheduler:use_external_trigger(true)

    print "Creating tasks"
    priority = tp:MAX_USER_TASK_PRIO()

    -- Create task calculates a spring-mass-damper system..
    smd = SMD.new("SMD", k, B, mass)
    s.set_task_properties(smd, tp, SCHEDULER_PERIOD, priority)
    priority = priority - 1

    -- Create a data logger task.
    logger = Logger.new("Logger", LOGFILE)
    s.set_task_properties(logger, tp, s.HZ_to_period(1), priority)
    priority = priority - 1

    -- Start everything up.
    print "Starting tasks..."
    scheduler:start()
    logger:start()
    smd:start()
end


--------------------------------------------------------------------------------
-- Terminate function
--------------------------------------------------------------------------------
function terminate()
    print "...Exiting"

    -- Halt the tasks
    smd:stop()

    -- Let the logger run until it has had time to flush all data.
    --scheduler:use_external_trigger(false)
    --scheduler:trigger()
    os.execute("sleep " .. tonumber(2))
    logger:stop()
    scheduler:stop()
end


--------------------------------------------------------------------------------
-- Test function function
----------------------------------------------------------------
function hello()
    print "Hello world!"
end
