#pragma once

#include "Engine.h"
template<type cl>
struct InputHandle{
	int key;
	void (*func)();
	cl* obj;
	InputHandle(){}
	InputHandle(int k, void(*f)());
	template <type T>
	InputHandle(int k,T *c, void(*f)());
};

class Input{
public:
	void bindInputKey(int k, void (*f)());
	template <type T>
	void binInputKey(int k, T *c, void(*f)());
	void callInput(int k);

	Input(){ handleIndex = 0; }
private:
	template <type cl>
	InputHandle funcs[300];
	int handleIndex;
};