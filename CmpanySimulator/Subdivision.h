#pragma once
#include "Acolyte.h"
class Acolyte;


class Subdivision{
	protected:
		Acolyte *Boss;
		Acolyte **Workers;
		int NWorkers;
	public:
		Subdivision( int NWorkers, Acolyte *Boss, char Rights );
		Acolyte *FindFreeWorker();
		~Subdivision(); 
		void Print();
		int Fork();
};
