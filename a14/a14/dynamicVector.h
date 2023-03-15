#pragma once

#include "domain.h"

template <typename T>
class DynamicVector
{
public:
	DynamicVector(int capacity = 10);

	~DynamicVector();

	DynamicVector(const DynamicVector& e);

	T& operator[](int pos);

	void operator+(const T& e);

	void add(T newEvent);

	void deleteEvent(int index);

	int getEventLen() const;

	int getCapacity() const;

	void resize(int factor = 2);


private:
	T* events;
	int nrEvents, capacity;
};


template <typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
	this->capacity = capacity;
	this->nrEvents = 0;
	this->events = new T[capacity];
}


template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& v)
{
	this->capacity = v.capacity;
	this->nrEvents = v.nrEvents;

	this->events = new T[v.capacity];

	for (int i = 0; i < v.nrEvents; i++)
	{
		this->events[i] = T{ v.events[i].getTitle(), v.events[i].getDescription(), v.events[i].getLink(), v.events[i].getNumberOfPeople(), v.events[i].getDate() };
	}
}

template <typename T>
DynamicVector<T>::~DynamicVector()
{
	return;
	//delete[] this->events;
}

template <typename T>
T& DynamicVector<T>::operator[](int pos)
{
	return this->events[pos];
}

template<typename T>
void DynamicVector<T>::operator+(const T& e)
{
	if (this->nrEvents == this->capacity)
	{
		this->resize();
	}
	this->events[this->nrEvents++] = e;
}

template<typename T>
inline void DynamicVector<T>::add(T newEvent)
{
	if (this->nrEvents == this->capacity)
	{
		this->resize();
	}
	this->events[this->nrEvents++] = newEvent;
}


template<typename T>
void DynamicVector<T>::resize(int factor)
{
	this->capacity *= factor;

	T* aux = new T[this->capacity];

	for (int i = 0; i < this->nrEvents; i++)
	{
		aux[i] = this->events[i];
	}

	delete[] this->events;
	this->events = aux;

}

template<typename T>
void DynamicVector<T>::deleteEvent(int index)
{
	this->events[index] = this->events[this->nrEvents - 1];
	this->nrEvents--;
	return;
}


template <typename T>
int DynamicVector<T>::getEventLen() const
{
	return this->nrEvents;
}


template<typename T>
inline int DynamicVector<T>::getCapacity() const
{
	return this->capacity;
}
