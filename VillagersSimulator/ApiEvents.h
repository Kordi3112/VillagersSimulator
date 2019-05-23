#pragma once
#include <vector>
class ApiEvents
{
public:
	enum Type
	{
		GENERATE_MAP,
		//
		BUTTON_CLICKED,

	};

	class Event
	{
	public:
		Type type;
		int value1;
		int value2;

		Event();
		Event(Type type, int val1, int val2);
		~Event();
	};
	//
	ApiEvents();
	~ApiEvents();
	bool poolEvent();//returns true if there is some event in container 
	bool next();//next event
	int	addEvent(Event event); // return actual number of elements in container
	Event getTopEvent() const; //return event at the top of the list
	int getEventsCounter() const;
private:
	std::vector<Event> m_eventsContainer;
};

