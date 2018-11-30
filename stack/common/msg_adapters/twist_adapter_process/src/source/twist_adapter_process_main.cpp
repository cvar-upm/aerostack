/*!*********************************************************************************
 *  \file       twist_adapter.cpp
 *  \brief      TwistAdapter main file.
 *  \details    This file implements the main function of the TwistAdapter.
 *  \authors    Abraham Carrera.
 *  \copyright  Copyright 2018 Universidad Politecnica de Madrid (UPM)
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

#include "../include/twist_adapter_process.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, ros::this_node::getName());
  std::cout << ros::this_node::getName() << std::endl;

  TwistAdapter twist_adapter;
  twist_adapter.setUp();

   try
  {
    twist_adapter.start();
  }
  catch(std::exception &exception)
  {
    twist_adapter.notifyError(twist_adapter.SafeguardRecoverableError, 0, "ownStart()", exception.what());
    twist_adapter.stop();
    }

  ros::Rate rate(30);
  while(ros::ok())
  {
    ros::spinOnce();
    twist_adapter.run();
    rate.sleep();
  }

  return 0;
}

