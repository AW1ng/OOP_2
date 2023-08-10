#pragma once

#include "Worker.cpp"
#include "Subdivision.h"

using namespace std;
class Subdivision;

class Acolyte : public Worker {
	protected:
		char Rights;
		Acolyte *MyBoss;
		Subdivision *MySubdivs;
		bool CanOrder();
		bool SetTaskFor( Acolyte *Subordinate, Task *Work );
		bool SetTaskFrom( Acolyte *Boss, Task* Work );
		void ProceedTask();
	public:
		Subdivision* GetMySuvdiv() { return MySubdivs; }
		int ForkMySubdiv();
		void Say( string Phrase );
		Subdivision *GetSubdiv();
		Acolyte( Acolyte *MyBoss = nullptr, char Rights = 1 ); 
		bool GenerateIdea();
		bool CreateSubdivisions( char SubordRights = 1, int NSubords = 0 ); 
		
		string ToString(); 
};
