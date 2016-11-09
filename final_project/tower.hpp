#ifndef TOWER_HPP
#define TOWER_HPP

class Tower{
private:
	int stack[100];
public:
	~Tower();
	int counter=0;

	void push(int contain);
	void pop();
	
	int getTower(int idx);
	int last_position();
};

#endif

