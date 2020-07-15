# A behavior event informs about the execution result of a behavior

Header header                   # Message header
string name                     # Behavior name
float64 uid                      # UID of the behavior
string failed_belief            # belief expression of the behavior preconditions that is not satisfied
string belief_conflict          # belief that generates the failure of the preconditions
string behavior_event_code      # code of the behavior event

# Possible values for behavior_event_code
string GOAL_ACHIEVED            = GOAL_ACHIEVED
string TIME_OUT                 = TIME_OUT
string WRONG_PROGRESS           = WRONG_PROGRESS
string ASSUMPTION_CONFLICT      = ASSUMPTION_CONFLICT
string INTERRUPTED              = INTERRUPTED
