import executive_engine_api as api
import time

def runMission():
    time.sleep(2)

    print "Starting mission..."
    print "Activating loclization..."
    api.activateBehavior('SELF_LOCALIZE_BY_ODOMETRY')

    print "Taking off..."
    result = api.executeBehavior('TAKE_OFF')

    print "Activating loclization..."
    api.activateBehavior('SELF_LOCALIZE_BY_VISUAL_MARKER')

    print "Move to a higher position"
    result = api.executeBehavior('GO_TO_POINT', relative_coordinates=[0, 0, 0.5])
    print "Go to point finished with status: %s" % result

    print "Moving to desired point... 0,1,0"
    result = api.executeBehavior('GO_TO_POINT', relative_coordinates=[0, -3, 0])
    print "Go to point finished with status: %s" % result

    print "Moving to desired point... 0,1,0"
    result = api.executeBehavior('GO_TO_POINT', relative_coordinates=[-1, 0, 0])
    print "Go to point finished with status: %s" % result

    print "Moving to desired point... 0,1,0"
    result = api.executeBehavior('GO_TO_POINT', relative_coordinates=[0, 3, 0])
    print "Go to point finished with status: %s" % result


    print "Going back to initial point..."
    result = api.executeBehavior('GO_TO_POINT', relative_coordinates=[1,0,0])
    print "Go to point ended with status: %s" % result

    print "Landing..."
    result = api.executeBehavior('LAND')
    print "Landed with status: %s" % result


    print "Mission ended"
