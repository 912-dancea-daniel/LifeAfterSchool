#pragma once

#include "repo.h"
#include "forCSV.h"
#include "forHTML.h"
#include "undoRedo.h"
#include <memory.h>

class Service
{
public:
	Service();
	Service(const Service& e);
	~Service();

	//adds event
	void addEvent(std::string title = "", std::string description = "", std::string link = "", int numberOfPeople = 0, int day = 0, int month = 0, int year = 0, int hour = 0, int minute = 0);

	//delete event
	void deleteEvent(std::string title = "", int day = 0, int month = 0, int year = 0, int hour = 0, int minute = 0);

	//get the repo data
	EventVector getData() const;

	//get the userRepoData
	EventVector getUserRepo() const;

	CSV getCSVUser() const;

	forHTML getHTMLUser() const;

	//update the event title
	void updateTitle(std::string title = "", int day = 0, int month = 0, int year = 0, int hour = 0, int minute = 0, std::string newTitle = "");

	//update the event description
	void updateDesc(std::string title = "", int day = 0, int month = 0, int year = 0, int hour = 0, int minute = 0, std::string newDesc = "");

	//update the event link
	void updateLink(std::string title = "", int day = 0, int month = 0, int year = 0, int hour = 0, int minute = 0, std::string newLink = "");
	
	//update the event number of people going to the event
	void updateNrOfPeople(std::string title = "", int day = 0, int month = 0, int year = 0, int hour = 0, int minute = 0, int newNrOfPeople = 0);

	//update the event Date
	void updateDate(std::string title = "", int day = 0, int month = 0, int year = 0, int hour = 0, int minute = 0, int newDay = 0, int newMonth = 0, int newYear = 0, int newHour = 0, int newMinute = 0);

	//get the events from a month, returns the startIndex and the endIndex
	void getEvents(int& startIndex, int& endIndex, int month);

	//returns the event with the specific index
	Event getEvent(int index);

	//adds event to the userRepo
	void addUserEvent(int index, int repoNR);

	//delete event from the UserRepo
	void deleteUserEvent(int index, int repoNR);

	void setRepoFromFile(std::string FileName = "in.txt");

	int undo();

	int redo();

	EventVector repo;
private:
	
	EventVector userRepo;

	forHTML userHTML;
	CSV userCSV;


	/*std::vector<std::unique_ptr<Action>> actions_undo;
	std::vector<std::unique_ptr<Action>> actions_redo;*/
};


