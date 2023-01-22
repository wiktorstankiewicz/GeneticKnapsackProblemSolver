#pragma once
#include<iostream>

class RefCounter {
public:
	RefCounter() { count = 0; };
	int increment() { return ++count; };
	int decrement() { return --count; };
	int get() { return count; };

private:
	int count;
};

template<typename T>
class Pointer
{
public:

	Pointer(T* pcPointer);
	Pointer(const Pointer& other);
	Pointer();
	~Pointer();
	T& operator*() { return(*dataPointer); }
	T* operator->() { return(dataPointer); }
	bool operator==(Pointer& other);
	bool operator==(T* other);
	Pointer<T>& operator=(const Pointer& other);
private:
	RefCounter* refCounter;
	T* dataPointer;
};//class CMySmartPointer


template<typename T>
bool Pointer<T>::operator==(Pointer& other) {
	return dataPointer == other.dataPointer;
}

template<typename T>
bool Pointer<T>::operator==(T* other) {
	return dataPointer == other;
}

template<typename T>
Pointer<T>& Pointer<T>::operator=(const Pointer& other) {
	refCounter->decrement();
	if (refCounter->get() == 0) {
		if (dataPointer != nullptr) {
			delete dataPointer;
		}
		delete refCounter;
	}
	dataPointer = other.dataPointer;
	refCounter = other.refCounter;
	other.refCounter->increment();

	return *this;
}

template<typename T>
Pointer<T>::Pointer(T* pcPointer)
{
	dataPointer = pcPointer;
	refCounter = new RefCounter();
	refCounter->increment();
}//CMySmartPointer(CSellData *pcPointer)

template<typename T>
Pointer<T>::Pointer(const Pointer& other)
{
	dataPointer = other.dataPointer;
	refCounter = other.refCounter;
	refCounter->increment();
}
template<typename T>
inline Pointer<T>::Pointer()
{
	dataPointer = nullptr;
	refCounter = new RefCounter();
	refCounter->increment();
}
//CMySmartPointer(const CMySmartPointer &pcOther)

template<typename T>
Pointer<T>::~Pointer()
{
	if (refCounter->decrement() == 0)
	{
		if (dataPointer != nullptr) {

			delete dataPointer;
		}
		delete refCounter;
	}
}//~CMySmartPointer()

