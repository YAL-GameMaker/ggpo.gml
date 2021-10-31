/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#ifndef _GGPO_LINUX_H_
#define _GGPO_LINUX_H_

#define __STDC_WANT_LIB_EXT1__ 1

#include <limits.h> // TODO(emoller): only for PATH_MAX
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "types.h"

typedef int HANDLE;     // TODO(emoller): only needed for Poll
#define MAX_PATH PATH_MAX

class Platform {
public:  // types
   typedef pid_t ProcessID;

public:  // functions
   static ProcessID GetProcessID();
   static void AssertFailed(char *msg);
   static uint32 GetCurrentTimeMS();
   static void SleepMS(int milliseconds);
   static void CreateDirectory(const char* pathname);
   static int GetConfigInt(const char* name);
   static bool GetConfigBool(const char* name);
   static void DebugBreak();
};

#endif
