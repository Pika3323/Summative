#include "Input.h"

void Input::onKeyDown(int key){
	for (int i = 0; i < 300; i++){
		if (funcs[i].key = key){
			funcs[i].func;
		}
	}
}
void Input::onKeyUp(int key){

}
void Input::onMouseDown(int button){

}
void Input::onMouseUp(int button){

}

void Input::bindInputfunction(int key, void(*f)()){
	funcs[EventIndex].func = f;
	funcs[EventIndex].key = key;
	EventIndex++;
}