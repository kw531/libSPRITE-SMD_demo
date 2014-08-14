package.path = '/usr/local/lib/SPRITE/?.lua;' .. package.path
s = require 'scheduler'

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

-- Create the scheduler.
SCHEDULER_PERIOD = s.HZ_to_period(10)
scheduler = s.create(tp, SCHEDULER_PERIOD)

-- Create task properties and set an initial priority.
tp = Task_properties.new()
priority = tp:MAX_USER_TASK_PRIO()

-- Create task that manages the SMD serial port.
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

-- Use debug to pause the script and let the tasks run.
print "Use control-D to cleanly terminate execution."
debug:debug()

-- Halt the task
smd:stop()

-- Let the logger run until it has had time to flush all data.
os.execute("sleep " .. tonumber(2))
logger:stop()
scheduler:stop()

print "...Exiting"
