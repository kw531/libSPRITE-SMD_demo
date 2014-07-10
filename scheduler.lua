--------------------------------------------------------------------------------
-- Define some common functions.
--------------------------------------------------------------------------------

-- Convert number of HZ to a period that can be used to schedule a task.
function HZ_to_period(hz)
    return 1/hz
end

--------------------------------------------------------------------------------
-- Set some constants.
--------------------------------------------------------------------------------

FASTEST_PERIOD = HZ_to_period(FASTEST_RATE)

--------------------------------------------------------------------------------
-- Create the scheduler
--------------------------------------------------------------------------------
function create_scheduler(tp, task_prio)
    scheduler = Scheduler.new()
    tp:set_period(FASTEST_PERIOD)
    tp:set_prio(task_prio)
    scheduler:set_properties(tp)

    return scheduler
end


--------------------------------------------------------------------------------
-- Set task properties.
--------------------------------------------------------------------------------
function set_task_properties(task, tp, period, priority)
    tp:set_period(period)
    tp:set_prio(priority)
    priority = priority - 1
    task:set_properties(tp)
end
