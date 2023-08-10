#pragma once
#include <iostream>
#include <string>
#include "getrandomint.h"
#include "Task.h"
using namespace std;

//class Task;

class Worker {
	protected:
		inline static int IDCounter = 0;
//		inline static string const PossibleNames[3] = {"Eat", "Sleep", "Pray"}; // C++ 17
		inline static string const PossibleNames[10] = {"John", "Vlad", "Kira", "Lera", "Alex", "Kirill", "Mary", "Dan", "Leon", "Paul"};
		int ID;
		string Name;
		Task *BusyWith;
	public:
		Worker() : BusyWith(nullptr) {
			Random *RGenerator = new Random;
			int maxName = sizeof( PossibleNames ) / sizeof( string ) - 1;
			Name = PossibleNames[ RGenerator->get_random( maxName ) ];
			ID = IDCounter++;
		}
		
		virtual string ToString() {
			string result =  Name + "_" + to_string( ID );
			if( IsBusy() ) result += "busy with " + BusyWith->ToString();
			else result += " not busy";
			return result;
		}
		bool IsBusy() { return BusyWith != nullptr; }
				
};