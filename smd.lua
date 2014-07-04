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

-- Create task properties and set an initial priority.
tp = Task_properties.new()
priority = tp:MAX_USER_TASK_PRIO()

-- Create the scheduler.
s = create_scheduler(tp, priority)
priority = priority - 1

-- Create task that manages the SMD serial port.
smd = SMD.new("SMD", k, B, mass)
set_task_properties(smd, tp, FASTEST_PERIOD, priority)
priority = priority - 1

-- Create a data logger task.
logger = Logger.new("Logger", LOGFILE)
set_task_properties(logger, tp, HZ_to_period(1), priority)
priority = priority - 1

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
