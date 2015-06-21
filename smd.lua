package.path = '/usr/local/lib/SPRITE/?.lua;' .. package.path
local s = require 'scheduler'

--------------------------------------------------------------------------------
-- Set some constants.
--------------------------------------------------------------------------------

k = 0.1  -- Spring constant
B = 0.25 -- Damper constant
mass = 1.0 -- in grams.

LOGFILE = "./smd.csv"
print "Apply and external force? 0 for none. Postive pulls, negative pushes."
force_in=io.read()
--------------------------------------------------------------------------------
-- Initialize everything
--------------------------------------------------------------------------------

-- Create task properties and set an initial priority.
tp = Task_properties.new()
priority = tp:MAX_USER_TASK_PRIO()

-- Create the scheduler.
SCHEDULER_PERIOD = s.HZ_to_period(10)
scheduler = s.create(tp, SCHEDULER_PERIOD)

-- Create task that manages the SMD serial port.
smd = SMD.new("SMD", k, B, mass, force_in)
s.set_task_properties(smd, tp, SCHEDULER_PERIOD, priority)
priority = priority - 1

-- Create Feeder
feeder = Feeder.new("Feeder")
s.set_task_properties(feeder, tp, SCHEDULER_PERIOD, priority)



-- Create a data logger task.
logger = Logger.new("Logger", LOGFILE)
s.set_task_properties(logger, tp, s.HZ_to_period(1), priority)
priority = priority - 1

--------------------------------------------------------------------------------
-- Start up the tasks.
--------------------------------------------------------------------------------

-- Start everything up.
print "Starting tasks..."
scheduler:start()
logger:start()
smd:start()
feeder:start()

--- Use debug to pause the script and let the tasks run.
print "Use control-D to cleanly terminate execution."
debug:debug()

--------------------------------------------------------------------------------
-- Terminate the tasks.
--------------------------------------------------------------------------------

print "...Exiting"

-- Halt the task
feeder:stop()
smd:stop()
logger:stop()
scheduler:stop()
