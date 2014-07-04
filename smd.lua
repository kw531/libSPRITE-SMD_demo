require 'scheduler'

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

tp = Task_properties.new()
priority = tp:MAX_USER_TASK_PRIO()

s = create_scheduler(tp, priority)
priority = priority - 1

-- Create task that manages the SMD serial port.
smd = SMD.new("SMD", k, B, mass)
tp:set_period(FASTEST_PERIOD)
tp:set_prio(priority)
priority = priority - 1
smd:set_properties(tp)

-- Create a data logger task.
logger = Logger.new("Logger", LOGFILE)
tp:set_period(HZ_to_period(1))
tp:set_prio(priority)
priority = priority - 1
logger:set_properties(tp)

-- Start everything up.
print "Starting tasks..."
scheduler:start()
logger:start()
smd:start()

-- Use debug to pause the script and let the tasks run.
print "Use control-D to cleanly terminate execution."
debug:debug()

-- Halt the task
smd:stop()
logger:stop()

print "...Exiting"
