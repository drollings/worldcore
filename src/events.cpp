/*************************************************************************
*   File: event.c++                  Part of Aliens vs Predator: The MUD *
*  Usage: Primary code for events                                        *
*************************************************************************/

#include "typedefs.hpp"
#include "events.hpp"
#include "stringfunctions.hpp"


// New Event System

namespace Events
{
	Queue EventQueue;

	void Event::ProcessEvents(void) {
		Event *				pEvent;
		unsigned int		newTime;
		
		while (pulse >= EventQueue.QueueKey()) {
			if (!(pEvent = (Event *)EventQueue.QueueHead())) {
				return;
			}
			if ((newTime = pEvent->Execute()) != 0)
				pEvent->m_pQueue = EventQueue.Enqueue(pEvent, newTime + pulse);
			else
				delete pEvent;
		}
	}
	
	
	Event::Event(unsigned int when) :
		m_pQueue(NULL),
		m_bRunning(false)
	{
		if (when < 1)
			when = 1;
		
		m_pQueue = EventQueue.Enqueue(this, when + pulse);
	}
	
	
	unsigned int Event::GetTimeRemaining() const
	{
		return (m_pQueue->key - pulse);
	}
	
	
	time_t Event::Execute()
	{
		unsigned int result;
		
		m_bRunning = true;
		result = Run();
		m_bRunning = false;
		
		return result;
	}
	
	
	void Event::Cancel(void) {
		if (m_bRunning)
			return;
		
		EventQueue.Dequeue(m_pQueue);
		delete this;
	}
	
	
	void Event::Reschedule(time_t when)
	{
		EventQueue.Dequeue(m_pQueue);
		m_pQueue = EventQueue.Enqueue(this, when + pulse);
	}
	
	
	Event *Event::FindEvent(EventList &list, const char *type) {
		Event *event = NULL;
		EventList::iterator iter;
	
		iter = list.begin();
		
		while (iter != list.end()) {
			event = *iter;
			if (event->GetType() == type || !str_cmp(event->GetType(), type))
				break;
		}
		return event;
	}


}
	
