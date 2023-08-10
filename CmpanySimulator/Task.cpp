#include "Task.h"
//#include "Worker.cpp"
#include "getrandomint.h"
#include <string>
#include <iostream>
//Task::Task() {
//	
//}

Task::Task( std::string MainName ) {
//	std::cout << "Task C-tor is here...\n";
	Random *RGenerator = new Random;
	int maxName = sizeof( PossibleNames ) / sizeof( std::string ) - 1 ;
	
	Name = MainName + PossibleNames[ RGenerator->get_random( maxName ) ];
	ID = IDCounter++;
}


Task::~Task() {}


std::string Task::ToString() {
	 return Name + "_" + std::to_string( ID );
}