/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#include "types.h"

static FILE *logfile = NULL;

void LogFlush()
{
   if (logfile) {
      fflush(logfile);
   }
}

static char logbuf[4 * 1024 * 1024];

void Log(const char *fmt, ...)
{
   va_list args;
   va_start(args, fmt);
   Logv(fmt, args);
   va_end(args);
}

void Logv(const char *fmt, va_list args)
{
   if (!Platform::GetConfigBool("ggpo.log") || Platform::GetConfigBool("ggpo.log.ignore")) {
      return;
   }
   #ifndef WASM
   if (!logfile) {
      snprintf(logbuf, ARRAY_SIZE(logbuf), "log-%d.log", Platform::GetProcessID());
      logfile = fopen(logbuf, "w");
   }
   #endif
   Logv(logfile, fmt, args);
}

void Logv(FILE *fp, const char *fmt, va_list args)
{
   if (Platform::GetConfigBool("ggpo.log.timestamps")) {
      static int start = 0;
      int t = 0;
      if (!start) {
         start = Platform::GetCurrentTimeMS();
      } else {
         t = Platform::GetCurrentTimeMS() - start;
      }
      #ifdef WASM
      printf("%d.%03d : ", t / 1000, t % 1000);
      #else
      fprintf(fp, "%d.%03d : ", t / 1000, t % 1000);
      #endif
   }

   #ifdef WASM
   vprintf(fmt, args);
   #else
   vfprintf(fp, fmt, args);
   fflush(fp);
   
   vsnprintf(logbuf, ARRAY_SIZE(logbuf), fmt, args);
   #endif
}

