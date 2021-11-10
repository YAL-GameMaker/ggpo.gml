/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#include "types.h"
#include "poll.h"

Poll::Poll(void) :
   _start_time(0)
{
   // OK!
}

void
Poll::RegisterMsgLoop(IPollSink* sink, void* cookie)
{
   _msg_sinks.push_back(PollSinkCb(sink, cookie));
}

void
Poll::RegisterLoop(IPollSink* sink, void* cookie)
{
   _loop_sinks.push_back(PollSinkCb(sink, cookie));
}

bool
Poll::Pump(int timeout)
{
   int i, res;
   bool finished = false;

   if (_start_time == 0) {
      _start_time = Platform::GetCurrentTimeMS();
   }
   int elapsed = Platform::GetCurrentTimeMS() - _start_time;

   for (i = 0; i < _msg_sinks.size(); i++) {
      PollSinkCb& cb = _msg_sinks[i];
      finished = !cb.sink->OnMsgPoll(cb.cookie) || finished;
   }

   for (i = 0; i < _loop_sinks.size(); i++) {
      PollSinkCb& cb = _loop_sinks[i];
      finished = !cb.sink->OnLoopPoll(cb.cookie) || finished;
   }
   return finished;
}
