#pragma once
#include <string>
//#include "Worker.cpp"
//#include <iostream>
//using namesapce std;
//class Worker;


class Task {
	protected:
		inline static int IDCounter = 0;
		inline static std::string const PossibleNames[3] = {"Eat", "Sleep", "Pray"};
		int ID;
		std::string Name;
	public:
//		Task() {
//			
//		}
		Task ( std::string MainName  = ""); 
		~Task();
		std::string ToString();
};