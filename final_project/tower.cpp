#include "tower.hpp"
Tower::~Tower(){}

void Tower::push(int contain){
	stack[counter] = contain;
	counter++;
}

void Tower::pop(){
	counter--;
	stack[counter] = 0;
}

int Tower::getTower(int idx){
	return stack[idx];
}

int Tower::last_position(){
	return stack[counter-1];
}

