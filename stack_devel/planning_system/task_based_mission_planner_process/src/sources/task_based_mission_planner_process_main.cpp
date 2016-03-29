#include "task_based_mission_planner_process.h"
int main(int argc, char **argv)
{
  TaskBasedMissionPlanner MyTaskBasedMissionPlanner(argc, argv);
  MyTaskBasedMissionPlanner.open();
  MyTaskBasedMissionPlanner.start();
  return 0;
}