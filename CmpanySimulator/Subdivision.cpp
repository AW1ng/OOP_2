
#include "Subdivision.h"
//#include "Acolyte.h"
//class Acolyte;


Subdivision::Subdivision( int NWorkers, Acolyte *Boss, char Rights = 1 ) : NWorkers(NWorkers), Boss(Boss) {
	Workers = new Acolyte*[NWorkers];	
	for( int i = 0; i < NWorkers; i++ ) {
		Workers[ i ] = new Acolyte( Boss, Rights ); // << '\n';
	} 
	}
		
Subdivision::~Subdivision() {
//	cout << "Subdivbision d-tor is here...\n";
	delete[] Workers;
	}
	
void Subdivision::Print() {
	for( int i = 0; i < NWorkers; i++ ) {
		cout << Workers[ i ]->ToString() << '\n';
		if( Workers[i]->GetSubdiv() ) Workers[i]->GetSubdiv()->Print();
	} 
	cout << endl;
	}
	
int Subdivision::Fork() {
	int result = 0;
	for( int i = 0; i < NWorkers; i++ ) {
		if( Workers[i]->CreateSubdivisions() ) result++;
	}
	return result;
	}
	
Acolyte *Subdivision::FindFreeWorker() {
	cout << "searching for free worker...\n";
	cout << NWorkers << endl;
	for( int i = 0; i <NWorkers; i++ ){
		cout << i << " ";
		if( !Workers[i]->IsBusy() ) return Workers[i];
	}
	return nullptr;
}