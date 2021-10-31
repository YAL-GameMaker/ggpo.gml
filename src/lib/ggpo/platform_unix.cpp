/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#include "platform_unix.h"
#include <time.h>
#include <signal.h>
#include <sys/stat.h>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>

static void __attribute__((constructor)) DllMain() {
   srand(Platform::GetCurrentTimeMS() + Platform::GetProcessID());
}

Platform::ProcessID Platform::GetProcessID() 
{ 
    return getpid();
}

struct timespec start = { 0 };

uint32 Platform::GetCurrentTimeMS() 
{
    if (start.tv_sec == 0 && start.tv_nsec == 0) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        return 0;
    }
    struct timespec current;
    clock_gettime(CLOCK_MONOTONIC, &current);

    return ((current.tv_sec - start.tv_sec) * 1000) +
           ((current.tv_nsec  - start.tv_nsec ) / 1000 * 1000);
}

void Platform::SleepMS(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void Platform::AssertFailed(char *msg)
{
    std::cerr << msg;
    Platform::DebugBreak();
    // TODO(emoller)
}

void Platform::CreateDirectory(const char* pathname) {
  mkdir(pathname, -1);
  // TODO(emoller): -1 or 0755 ?
} 

int
Platform::GetConfigInt(const char* name)
{
    // TODO(emoller)
    return 0;
}

bool Platform::GetConfigBool(const char* name)
{
    // TODO(emoller)
    return false;
}

void Platform::DebugBreak()
{
    raise(SIGTRAP);
}
