#pragma once
#include <vector>
#include "domain.h"
#include <fstream>
#include "validator.h"

class EventVector
{

public:
	EventVector(int capacity = 1);

	~EventVector();

	EventVector(const EventVector& e);

	//ads event
	void addEvent(Event newEvent);

	//delete event
	void deleteEvent(std::string title, Date date);

	//gets the event by the index
	Event getEvent(int index);

	//get the list length
	int getEventLen();

	//update event title
	void updateEventTitle(std::string title, Date d, std::string newTitle);

	//update event description
	void updateEventDesc(std::string title, Date d, std::string newDesc);

	//update event link
	void updateEventLink(std::string title, Date d, std::string newLink);

	//update event number of people going
	void updateEventNrOfPeople(std::string title, Date d, int newNrOfPeople);

	//update event date
	void updateEventDate(std::string title, Date d, Date newDate);

	//preload the repo with 10 elements
	void loadRepo();

	//sort the events inside of the repo
	void sortEvents();

	//compare two dates
	bool dateCmp(Date d1, Date d2);

	void writeToFile(std::string fileName = "out.txt");

	void setRepoToFile(std::string fileName = "out.txt");

	static bool sortFunc(Event e1, Event e2);

	std::vector<Event> arr;
private:
};

