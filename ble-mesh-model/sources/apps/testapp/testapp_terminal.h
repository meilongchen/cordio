/*************************************************************************************************/
/*!
 *  \file   testapp_terminal.h
 *
 *  \brief  Mesh Test Terminal handler.
 *
 *  Copyright (c) 2015-2018 Arm Ltd.
 *
 *  Copyright (c) 2019 Packetcraft, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
/*************************************************************************************************/

#ifndef TESTAPP_TERMINAL_H
#define TESTAPP_TERMINAL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mesh_prv_cl_api.h"

/**************************************************************************************************
  Global Variables
**************************************************************************************************/

extern char * const pTestAppLogo[];

/**************************************************************************************************
  Function Declarations
**************************************************************************************************/

void testAppTerminalInit(void);

#ifdef __cplusplus
}
#endif

#endif /* TESTAPP_TERMINAL_H */
