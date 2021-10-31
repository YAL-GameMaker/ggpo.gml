/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#include "types.h"
#include "poll.h"

void
Poll::RegisterLoop(IPollSink *sink)
{
   _loop_sinks.push_back(sink);
}

bool
Poll::Pump()
{
   bool finished = false;

   for (int i = 0; i < _loop_sinks.size(); i++) {
      IPollSink* sink = _loop_sinks[i];
      finished = (sink && !sink->OnLoopPoll()) || finished;
   }
   return finished;
}
