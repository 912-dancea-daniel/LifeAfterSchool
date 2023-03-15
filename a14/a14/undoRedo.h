#pragma once
#include "repo.h"

class Action
{
public:
	
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;

};



class ActionAdd : public Action
{
protected:
	Event eventToadd;
	EventVector& repo;

public:

	ActionAdd(Event e, EventVector& r) : eventToadd{ e }, repo{ r }{}


	ActionAdd(const ActionAdd&) = delete;
	ActionAdd& operator= (const ActionAdd&) = delete;

	void executeUndo() override
	{
		this->repo.deleteEvent(eventToadd.getTitle(), eventToadd.getDate());
	}

	void executeRedo() override
	{
		this->repo.addEvent(eventToadd);
	}

};

class ActionUpdateTitle : public Action
{
protected:
	Event eventToadd;
	EventVector& repo;
	std::string toUpdate;

public:

	ActionUpdateTitle(Event e, EventVector& r, std::string u) : eventToadd{ e }, repo{ r }, toUpdate{u}{}


	ActionUpdateTitle(const ActionAdd&) = delete;
	ActionUpdateTitle& operator= (const ActionAdd&) = delete;

	void executeUndo() override
	{
		this->repo.updateEventTitle(toUpdate, eventToadd.getDate(), eventToadd.getTitle());
	}

	void executeRedo() override
	{
		this->repo.updateEventTitle(eventToadd.getTitle(), eventToadd.getDate(), toUpdate);
	}

};


class ActionUpdateDesc : public Action
{
protected:
	Event eventToadd;
	EventVector& repo;
	std::string toUpdate;

public:

	ActionUpdateDesc(Event e, EventVector& r, std::string u) : eventToadd{ e }, repo{ r }, toUpdate{ u }{}


	ActionUpdateDesc(const ActionAdd&) = delete;
	ActionUpdateDesc& operator= (const ActionAdd&) = delete;

	void executeUndo() override
	{
		this->repo.updateEventDesc(eventToadd.getTitle(), eventToadd.getDate(), eventToadd.getDescription());
	}

	void executeRedo() override
	{
		this->repo.updateEventDesc(eventToadd.getTitle(), eventToadd.getDate(), toUpdate);
	}

};

class ActionUpdateLink : public Action
{
protected:
	Event eventToadd;
	EventVector& repo;
	std::string toUpdate;

public:

	ActionUpdateLink(Event e, EventVector& r, std::string u) : eventToadd{ e }, repo{ r }, toUpdate{ u }{}


	ActionUpdateLink(const ActionAdd&) = delete;
	ActionUpdateLink& operator= (const ActionAdd&) = delete;

	void executeUndo() override
	{
		this->repo.updateEventLink(eventToadd.getTitle(), eventToadd.getDate(), eventToadd.getLink());
	}

	void executeRedo() override
	{
		this->repo.updateEventLink(eventToadd.getTitle(), eventToadd.getDate(), toUpdate);
	}

};

class ActionUpdateNr : public Action
{
protected:
	Event eventToadd;
	EventVector& repo;
	int toUpdate;

public:

	ActionUpdateNr(Event e, EventVector& r, int u) : eventToadd{ e }, repo{ r }, toUpdate{ u }{}


	ActionUpdateNr(const ActionAdd&) = delete;
	ActionUpdateNr& operator= (const ActionAdd&) = delete;

	void executeUndo() override
	{
		this->repo.updateEventNrOfPeople(eventToadd.getTitle(), eventToadd.getDate(), eventToadd.getNumberOfPeople());
	}

	void executeRedo() override
	{
		this->repo.updateEventNrOfPeople(eventToadd.getTitle(), eventToadd.getDate(), toUpdate);
	}

};

class ActionUpdateDate : public Action
{
protected:
	Event eventToadd;
	EventVector& repo;
	Date toUpdate;

public:

	ActionUpdateDate(Event e, EventVector& r, Date u) : eventToadd{ e }, repo{ r }, toUpdate{ u }{}


	ActionUpdateDate(const ActionAdd&) = delete;
	ActionUpdateDate& operator= (const ActionAdd&) = delete;

	void executeUndo() override
	{
		this->repo.updateEventDate(eventToadd.getTitle(), eventToadd.getDate(), eventToadd.getDate());
	}

	void executeRedo() override
	{
		this->repo.updateEventDate(eventToadd.getTitle(), eventToadd.getDate(), toUpdate);
	}

};


class ActionRemove : public Action
{
protected:
	Event eventToadd;
	EventVector& repo;

public:

	ActionRemove(Event e, EventVector& r) : eventToadd{ e }, repo{ r }{}

	ActionRemove(const ActionRemove&) = delete;
	ActionRemove& operator= (const ActionRemove&) = delete;

	void executeUndo() override
	{
		this->repo.addEvent(eventToadd);
	}

	void executeRedo() override
	{
		this->repo.deleteEvent(eventToadd.getTitle(), eventToadd.getDate());
	}

};