#include "ApiEvents.h"



ApiEvents::ApiEvents()
{
}


ApiEvents::~ApiEvents()
{
}

bool ApiEvents::poolEvent()
{
	if (m_eventsContainer.size() > 0)return true;
	else return false;
}

bool ApiEvents::next()
{
	if (ApiEvents::m_eventsContainer.size() == 0)return false;

	ApiEvents::m_eventsContainer.pop_back();

	return true;
}

int ApiEvents::addEvent(Event event)
{
	ApiEvents::m_eventsContainer.push_back(event);

	return ApiEvents::m_eventsContainer.size();
}

ApiEvents::Event ApiEvents::getTopEvent() const
{
	return ApiEvents::m_eventsContainer.back();
}

int ApiEvents::getEventsCounter() const
{
	return ApiEvents::m_eventsContainer.size();
}

ApiEvents::Event::Event()
{

}

ApiEvents::Event::Event(Type type, int val1, int val2)
{
	Event::type = type;
	Event::value1 = val1;
	Event::value2 = val2;
}

ApiEvents::Event::~Event()
{
}
