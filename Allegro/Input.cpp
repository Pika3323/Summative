#include "Input.h"

template <class cl>
InputHandle::InputHandle(int k, void(*f)()){
	key = k;
	func = f;
	obj = NULL;
}

template <type cl>
InputHandle::InputHandle(int k,cl, *c, void(*cl::f)()){
	key = k;
	func = f;
	obj = c;
}

template <type T>
void Input::bindInputKey(int k, void(*f)()){
	funcs[handleIndex] = InputHandle<void>(k, f);
	handleIndex++;
}

template <type T>
void Input::bindInputKey(int k, T *c, void(*T::f)()){
	funcs[handleIndex] = InputHandle<T>(k, c, f);
	handleIndex++;
}
template <type T>
void Input::callInput(int k){
	for (int i = 0; i < handleIndex; i++){
		if (funcs[i].key == k){
			if (funcs[i].obj){
				funcs[i].obj->funcs[i].func;
			}
			else{
				funcs[i].func();
			}
		}
	}
}