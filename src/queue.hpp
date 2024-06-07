
#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include "typedefs.hpp"

#define NUM_EVENT_QUEUES	10

namespace Events
{
	static UInt32 			pulse;

	class QueueElement {
	public:
		QueueElement(Ptr data, int key);
		
		Ptr		data;
		int	key;
		QueueElement *prev, *next;
	};
	
	class Queue {
	public:
		Queue(void);
		~Queue(void);
		QueueElement *	Enqueue(Ptr data, int key);
		void			Dequeue(QueueElement *qe);
		Ptr				QueueHead(void);
		long			QueueKey(void);
		int				Count(void);
		
		QueueElement *head[NUM_EVENT_QUEUES], *tail[NUM_EVENT_QUEUES];
	};
}
	
#endif
