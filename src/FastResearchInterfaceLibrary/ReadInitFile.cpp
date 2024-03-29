//  ---------------------- Doxygen info ----------------------
//! \file ReadInitFile.cpp
//!
//! \brief
//! Implementation file for the method ReadInitFile() of the class FastResearchInterface
//!
//! \details
//! The class FastResearchInterface provides a basic low-level interface
//! to the KUKA Light-Weight Robot IV For details, please refer to the file
//! FastResearchInterface.h.
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

#include <frilibrary/FastResearchInterface.h>
#include <string.h>
#include <frilibrary/InitializationFileEntry.h>

#define stricmp strcasecmp
#define strnicmp strncasecmp

// ****************************************************************
// ReadInitFile()
//
int FastResearchInterface::ReadInitFile(const char* InitFileName)
{
    unsigned int ParameterCount = 0;

    InitializationFileEntry InitFileParser(InitFileName);

    if (InitFileName != NULL)
    {
        while (InitFileParser.NextEntry())
        {
            if (!stricmp(InitFileParser.GetSection(), "Priorities"))
            {
                if (!stricmp(InitFileParser.GetName(), "KRCCommunicationThread"))
                {
                    this->PriorityKRCCommunicationThread = atoi(InitFileParser.GetValue());
                    ParameterCount++;
                }
                if (!stricmp(InitFileParser.GetName(), "TimerThread"))
                {
                    this->PriorityTimerThread = atoi(InitFileParser.GetValue());
                    ParameterCount++;
                }
                if (!stricmp(InitFileParser.GetName(), "MainThread"))
                {
                    this->PriorityMainThread = atoi(InitFileParser.GetValue());
                    ParameterCount++;
                }
                if (!stricmp(InitFileParser.GetName(), "OutputConsoleThread"))
                {
                    this->PriorityOutputConsoleThread = atoi(InitFileParser.GetValue());
                    ParameterCount++;
                }
            }
            if (!stricmp(InitFileParser.GetSection(), "RobotName"))
            {
                if (!stricmp(InitFileParser.GetName(), "Name"))
                {
                    strcpy(this->RobotName, InitFileParser.GetValue());
                    ParameterCount++;
                }
            }

            if (!stricmp(InitFileParser.GetSection(), "ControlValues"))
            {
                if (!stricmp(InitFileParser.GetName(), "CycleTime"))
                {
                    this->CycleTime = atof(InitFileParser.GetValue());
                    ParameterCount++;
                }
            }

            if (!stricmp(InitFileParser.GetSection(), "Logging"))
            {
                if (!stricmp(InitFileParser.GetName(), "NumberOfLoggingFileEntries"))
                {
                    NumberOfLoggingFileEntries = atoi(InitFileParser.GetValue());
                    ParameterCount++;
                }
                if (!stricmp(InitFileParser.GetName(), "LoggingPath"))
                {
                    strcpy(this->LoggingPath, InitFileParser.GetValue());
                    ParameterCount++;
                }
                if (!stricmp(InitFileParser.GetName(), "LoggingFileName"))
                {
                    strcpy(this->LoggingFileName, InitFileParser.GetValue());
                    ParameterCount++;
                }
            }
        }
    }
    else
    {
        return (-1);
    }

    return (ParameterCount);
}
