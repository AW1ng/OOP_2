#include <iostream>
#include "getrandomint.h"
#include "Subdivision.cpp"
//#include "Worker.cpp"
#include "Acolyte.cpp"
#include "Task.cpp"
using namespace std;


class ISubdivision {
	public:
		virtual void Print() = 0;
};

class Acolyte;
class Worker;



class Slave : public Worker {
	protected:
		inline static int IDCounter = 0;
		Worker *BusyWith;
	public:
		Slave() : Worker() {
			Random *RGenerator = new Random;
			int maxName = sizeof( PossibleNames ) / sizeof( PossibleNames[0] ) - 1 ;
			Name = PossibleNames[ RGenerator->get_random( maxName ) ];
			ID = IDCounter++;
			BusyWith = nullptr;
		}
		bool GetTask( Worker *ToDo ) {
			if( BusyWith ) return false; 
			else BusyWith = ToDo;
		}

};


// TODO 
class Boss : public Slave {
	public:
		bool SetTask( Slave *W , Worker *ToDo ) {
			return true;
		}
		
		
};



int main() {
	Acolyte great_boss( nullptr, 2 );
//	Acolyte boss( &great_boss );
	cout <<"created great_boss " + great_boss.ToString();
	great_boss.CreateSubdivisions(2);
	cout << "Created subdivision \n";
	great_boss.GetMySuvdiv()->Print();
	cout << "Forking subdiv\n";
	great_boss.ForkMySubdiv();
	great_boss.GetMySuvdiv()->Print();
//	Subdivision Managment( 5, &great_boss, 2 );
//	Managment.Fork();
//	Subdivision Div( 3, &boss );
//	Managment.Print();
//	cout << ""
	for( int i = 0; i < 15; i++ ) {
		great_boss.GenerateIdea();
		great_boss.GetMySuvdiv()->Print();
		cout << "----------------------------------------------->\n";
	}
	
//	Task deeds[5];
//	for( int i = 0; i < 5; i++ ) {
//		cout << deeds[i].ToString() << " ";
//	}
//	cout << endl;
//	
//	Worker doers[5];
//	for( int i = 0; i < 5; i++ ) {
//		cout << doers[i].ToString() << " ";
//	}
	cout << endl;
	
/*	Random *RGenerator = new Random;
	Random *RGenerator2 = new Random;
	*/
	
//	Task *workers = new Worker[10];
//	for( int i = 0; i < 10; i++ ) {
//		cout << sometask[ i ].ToString() << '\n';
//	} 
//	cout << endl;
	
	
	return 0;
}


