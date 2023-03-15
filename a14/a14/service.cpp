#include "service.h"
#include <exception>
#include <iostream>

//using namespace std;

Service::Service()
{
	this->repo = EventVector{ 15 };
	this->repo.loadRepo();
	//this->repo.setRepoToFile("in.txt");
	this->repo.sortEvents();
	this->userRepo = EventVector{ 15 };
	this->userHTML = forHTML{};
	this->userCSV = CSV{};
}

Service::Service(const Service& e)
{
	this->repo = e.repo;
}

Service::~Service()
{
	return;
}

void Service::addEvent(std::string title, std::string description, std::string link, int numberOfPeople, int day, int month, int year, int hour, int minute)
{
	Date tmpDate = Date(day, month, year, hour, minute);
	Event tmp = Event(title, description, link, numberOfPeople, tmpDate);

	this->repo.addEvent(tmp);
	this->repo.sortEvents();

	/*std::unique_ptr<Action> ptr1 = std::make_unique<ActionAdd>(tmp, this->repo);
	this->actions_undo.push_back(move(ptr1));*/

	//this->repo + tmp;
}

void Service::deleteEvent(std::string title, int day, int month, int year, int hour, int minute)
{
	Date tmpDate = Date(day, month, year, hour, minute);

	this->repo.deleteEvent(title, tmpDate);
	this->repo.sortEvents();

	/*std::unique_ptr<Action> ptr1 = std::make_unique<ActionAdd>(Event{title, "", "", 0, tmpDate}, this->repo);
	this->actions_undo.push_back(move(ptr1));*/
}


EventVector Service::getData() const
{
	return this->repo;
}

EventVector Service::getUserRepo() const
{
	return this->userRepo;
}

CSV Service::getCSVUser() const
{
	return this->userCSV;
}

forHTML Service::getHTMLUser() const
{
	return this->userHTML;
}

void Service::updateTitle(std::string title, int day, int month, int year, int hour, int minute, std::string newTitle)
{
	Date tmpDate = Date(day, month, year, hour, minute);

	this->repo.updateEventTitle(title, tmpDate, newTitle);
	this->repo.sortEvents();
}

void Service::updateDesc(std::string title, int day, int month, int year, int hour, int minute, std::string newDesc)
{
	Date tmpDate = Date(day, month, year, hour, minute);

	this->repo.updateEventDesc(title, tmpDate, newDesc);
	this->repo.sortEvents();
}

void Service::updateLink(std::string title, int day, int month, int year, int hour, int minute, std::string newLink)
{
	Date tmpDate = Date(day, month, year, hour, minute);

	this->repo.updateEventLink(title, tmpDate, newLink);
	this->repo.sortEvents();
}

void Service::updateNrOfPeople(std::string title, int day, int month, int year, int hour, int minute, int newNrOfPeople)
{
	Date tmpDate = Date(day, month, year, hour, minute);

	this->repo.updateEventNrOfPeople(title, tmpDate, newNrOfPeople);
	this->repo.sortEvents();
}

void Service::updateDate(std::string title, int day, int month, int year, int hour, int minute, int newDay, int newMonth, int newYear, int newHour, int newMinute)
{
	Date tmpDate = Date(day, month, year, hour, minute);
	Date newDate = Date{ newDay, newMonth, newYear, newHour, newMinute };

	this->repo.updateEventDate(title, tmpDate, newDate);
	this->repo.sortEvents();
}

void Service::getEvents(int& startIndex, int& endIndex, int month)
{
	if (month == 0)
	{
		startIndex = 0;
		endIndex = this->repo.getEventLen();
		return;
	}

	bool ok = 0;

	for (int i = 0; i < this->repo.getEventLen(); i++)
	{
		if (this->repo.getEvent(i).getDate().getMonth() == month)
		{
			if (!ok)
			{
				startIndex = i;
				ok = 1;
			}
		}
		else
		{
			if (ok)
			{
				endIndex = i;
				return;
			}
		}
	}

}

Event Service::getEvent(int index)
{
	return this->repo.getEvent(index);
}

void Service::addUserEvent(int index, int repoNR)
{
	Event tmp = this->repo.getEvent(index);
	Date d{ this->repo.getEvent(index).getDate().getDay(), this->repo.getEvent(index).getDate().getMonth(), this->repo.getEvent(index).getDate().getYear(), this->repo.getEvent(index).getDate().getHour(), this->repo.getEvent(index).getDate().getMinute() };
	this->repo.deleteEvent(this->repo.getEvent(index).getTitle(), d);
	this->addEvent(tmp.getTitle(), tmp.getDescription(), tmp.getLink(), tmp.getNumberOfPeople() + 1, tmp.getDate().getDay(), tmp.getDate().getMonth(), tmp.getDate().getYear(), tmp.getDate().getHour(), tmp.getDate().getMinute());
	
	if (repoNR == 1)
	{
		this->userCSV.addEvent(this->getEvent(index));
	}
	else
	if (repoNR == 2)
	{
		this->userHTML.addEvent(this->getEvent(index));
	}
	else this->userRepo.addEvent(this->getEvent(index));
}

void Service::deleteUserEvent(int index, int repoNR)
{
	if (repoNR == 1)
	{
		if (index > this->userCSV.getEventLen())
			throw Exception("Not a valid index");

		Event tmp = this->userCSV.getEvent(index - 1);
		Date d{ tmp.getDate().getDay(), tmp.getDate().getMonth(), tmp.getDate().getYear(), tmp.getDate().getHour(), tmp.getDate().getMinute() };
		this->userCSV.deleteEvent(tmp.getTitle(), d);
		this->repo.deleteEvent(tmp.getTitle(), d);
		this->addEvent(tmp.getTitle(), tmp.getDescription(), tmp.getLink(), tmp.getNumberOfPeople() - 1, tmp.getDate().getDay(), tmp.getDate().getMonth(), tmp.getDate().getYear(), tmp.getDate().getHour(), tmp.getDate().getMinute());

	}
	else
	if (repoNR == 2)
	{
		if (index > this->userHTML.getEventLen())
			throw Exception("Not a valid index");

		Event tmp = this->userHTML.getEvent(index - 1);
		Date d{ tmp.getDate().getDay(), tmp.getDate().getMonth(), tmp.getDate().getYear(), tmp.getDate().getHour(), tmp.getDate().getMinute() };
		this->userHTML.deleteEvent(tmp.getTitle(), d);
		this->repo.deleteEvent(tmp.getTitle(), d);
		this->addEvent(tmp.getTitle(), tmp.getDescription(), tmp.getLink(), tmp.getNumberOfPeople() - 1, tmp.getDate().getDay(), tmp.getDate().getMonth(), tmp.getDate().getYear(), tmp.getDate().getHour(), tmp.getDate().getMinute());

	}
	else
	{
		if (index > this->userRepo.getEventLen())
			throw std::invalid_argument("Not a valid index");

		Event tmp = this->userRepo.getEvent(index - 1);
		Date d{ tmp.getDate().getDay(), tmp.getDate().getMonth(), tmp.getDate().getYear(), tmp.getDate().getHour(), tmp.getDate().getMinute() };
		this->userRepo.deleteEvent(tmp.getTitle(), d);
		this->repo.deleteEvent(tmp.getTitle(), d);
		this->addEvent(tmp.getTitle(), tmp.getDescription(), tmp.getLink(), tmp.getNumberOfPeople() - 1, tmp.getDate().getDay(), tmp.getDate().getMonth(), tmp.getDate().getYear(), tmp.getDate().getHour(), tmp.getDate().getMinute());

	}
	
}
void Service::setRepoFromFile(std::string FileName)
{
	this->repo.setRepoToFile(FileName);
}

int Service::undo()
{

	/*if (actions_undo.size() == 0)
		return 0;
	

	auto pt1 = move(this->actions_undo[this->actions_undo.size() - 1]);
	pt1->executeUndo();

	this->actions_redo.push_back(move(pt1));

	this->actions_undo.pop_back();*/
	return 1;

}

int Service::redo()
{

	/*if (this->actions_redo.size() == 0)
		return 0;
	
	
	auto pt1 = move(this->actions_redo[this->actions_redo.size() - 1]);
	pt1->executeRedo();

	this->actions_undo.push_back(move(pt1));

	this->actions_redo.pop_back();*/
	return 1;
}

