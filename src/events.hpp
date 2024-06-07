#ifndef __EVENTS_HPP__
#define __EVENTS_HPP__

#include "typedefs.hpp"
#include "queue.hpp"

//	The NEW event system

namespace Events
{
	class Event
	{
	public:
							Event(unsigned int when);
		virtual				~Event(void) {}
		virtual time_t		Run(void) = 0;
		virtual void		Cancel(void);
		time_t				Time(void) const;

		virtual time_t		Execute(void);

		virtual const char *GetType() const = 0;
		unsigned int		GetTimeRemaining() const;
		void				Reschedule(time_t when);
	
	protected:
		QueueElement		*m_pQueue;
		bool				m_bRunning;

	private:	
							Event(const Event &);
		void				operator=(const Event &);
	
	public:
		static void			Initialize(void);
		static void			Shutdown(void);
		static void			ProcessEvents(void);
		static Event *		FindEvent(EventList & list, const char * type);

		friend class		QueueElement;
	};
}	
	
#endif
