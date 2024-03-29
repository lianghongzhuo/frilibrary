//  ---------------------- Doxygen info ----------------------
//! \file LWRJointPositionControlExample.cpp
//!
//! \brief
//! Sample application for the class LWRJointPositionController
//!
//! \details
//! This simple application feature a sample of how to use the
//! joint position controller of the KUKA Fast Research Interface
//! for the Light-Weight Robot IV. For details about the actual
//! interface class (i.e., class LWRJointPositionController), please
//! refer to the file LWRJointPositionController.h.
//!
//! \date December 2014
//!
//! \version 1.2
//!
//!	\author Torsten Kroeger, tkr@stanford.edu\n
//! \n
//! Stanford University\n
//! Department of Computer Science\n
//! Artificial Intelligence Laboratory\n
//! Gates Computer Science Building 1A\n
//! 353 Serra Mall\n
//! Stanford, CA 94305-9010\n
//! USA\n
//! \n
//! http://cs.stanford.edu/groups/manips\n
//! \n
//! \n
//! \copyright Copyright 2014 Stanford University\n
//! \n
//! Licensed under the Apache License, Version 2.0 (the "License");\n
//! you may not use this file except in compliance with the License.\n
//! You may obtain a copy of the License at\n
//! \n
//! http://www.apache.org/licenses/LICENSE-2.0\n
//! \n
//! Unless required by applicable law or agreed to in writing, software\n
//! distributed under the License is distributed on an "AS IS" BASIS,\n
//! WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n
//! See the License for the specific language governing permissions and\n
//! limitations under the License.\n
//!
//  ----------------------------------------------------------
//   For a convenient reading of this file's source code,
//   please use a tab width of four characters.
//  ----------------------------------------------------------

#include <frilibrary/LWRJointPositionController.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

//*******************************************************************************************
// main()
//
int main(int argc, char* argv[])
{
    int ResultValue = 0, i = 0;

    float FunctionValue = 0.0, LoopVariable = 0.0, JointValuesInRad[NUMBER_OF_JOINTS],
          InitialJointValuesInRad[NUMBER_OF_JOINTS];

    LWRJointPositionController* Robot;

    Robot = new LWRJointPositionController("/opt/FRILibrary/etc/980039-FRI-Driver.init");

    fprintf(stdout, "RobotJointPositionController object created. Starting the robot...\n");

    ResultValue = Robot->StartRobot();

    if (ResultValue == EOK)
    {
        fprintf(stdout, "Robot successfully started.\n");
    }
    else
    {
        fprintf(stderr, "ERROR, could not start robot: %s\n", strerror(ResultValue));
    }

    fprintf(stdout, "Current system state:\n%s\n", Robot->GetCompleteRobotStateAndInformation());

    Robot->GetMeasuredJointPositions(InitialJointValuesInRad);

    while (LoopVariable < 5.0 * PI)
    {
        Robot->WaitForKRCTick();

        if (!Robot->IsMachineOK())
        {
            fprintf(stderr, "ERROR, the machine is not ready anymore.\n");
            break;
        }

        FunctionValue = (float)(0.3 * sin(LoopVariable));
        FunctionValue *= (float)FunctionValue;

        for (i = 0; i < NUMBER_OF_JOINTS; i++)
        {
            JointValuesInRad[i] = InitialJointValuesInRad[i] + FunctionValue;
        }

        Robot->SetCommandedJointPositions(JointValuesInRad);

        LoopVariable += (float)0.001;
    }

    fprintf(stdout, "Stopping the robot...\n");
    ResultValue = Robot->StopRobot();

    if (ResultValue != EOK)
    {
        fprintf(stderr, "An error occurred during stopping the robot...\n");
    }
    else
    {
        fprintf(stdout, "Robot successfully stopped.\n");
    }

    fprintf(stdout, "Deleting the object...\n");
    delete Robot;
    fprintf(stdout, "Object deleted...\n");

    return (EXIT_SUCCESS);
}
