/*!*********************************************************************************
 *  \file       self_localization_selector.cpp
 *  \brief      SelfLocalizationSelector main file.
 *  \details    This file implements the main function of the SelfLocalizationSelector.
 *  \authors    Alberto Camporredondo.
 *  \copyright  Copyright 2017 Universidad Politecnica de Madrid (UPM)
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program. If not, see http://www.gnu.org/licenses/.
 ********************************************************************************/

#include "../include/self_localization_selector_process.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, ros::this_node::getName());
  std::cout << ros::this_node::getName() << std::endl;

  SelfLocalizationSelector self_localization_selector;
  self_localization_selector.setUp();

  /* try
  {
    self_localization_selector.start();
  }
  catch(std::exception &exception)
  {
    self_localization_selector.notifyError(self_localization_selector.SafeguardRecoverableError, 0, "ownStart()", exception.what());
    self_localization_selector.stop();
    }*/

  ros::Rate rate(30);
  while(ros::ok())
  {
    ros::spinOnce();
    self_localization_selector.run();
    rate.sleep();
  }

  return 0;
}
