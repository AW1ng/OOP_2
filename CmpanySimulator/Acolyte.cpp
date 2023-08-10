
#include "getrandomint.h"
#include "Acolyte.h"
//#include "Worker.cpp"


using namespace std;


Acolyte::Acolyte( Acolyte *MyBoss, char Rights ): MyBoss(MyBoss), Rights(Rights){
//	cout << "Acolyte c-tor is here...\n";
	MySubdivs = nullptr;
}
		
bool Acolyte::CreateSubdivisions( char SubordRights, int NSubords) { 
	if( NSubords <= 0 ) {
		Random RGenerator;
		NSubords = RGenerator.get_random(2, 5);
	}
	if( CanOrder() ) {
		MySubdivs = new Subdivision( NSubords, this, SubordRights );
		return true;
	}
	else return false;
}

int Acolyte::ForkMySubdiv() {
	return MySubdivs->Fork();
}
		
string Acolyte::ToString()  {
	string Boss = "God";
	string Position = "[Worker]";
	if( MyBoss ) Boss = MyBoss->ToString();
	if( Rights & 2 ) Position = "[Manager]";
	return Worker::ToString() + Position + " under " + Boss;
} 


Subdivision *Acolyte::GetSubdiv() {
	return MySubdivs;
}


bool Acolyte::SetTaskFor( Acolyte *Subordinate, Task *Work ) {
	cout << "setting " << Work->ToString() << " to do for " << Subordinate->ToString();
	return Subordinate->SetTaskFrom( this, Work );
}


bool Acolyte::SetTaskFrom( Acolyte *Boss, Task* Work ) {
	if( MyBoss == Boss && !IsBusy() ) {
		BusyWith = Work;
		if( CanOrder() ) ProceedTask();
		return true;
	}
	else{
		Say( ToString() + " Cannot do " + Work->ToString() ); 
		return false;
	} 
}


void Acolyte::ProceedTask() {
	if( !BusyWith ) return;
	Random RGenerator;
	int NSubTasks = RGenerator.get_random(1, 4);
	Say("Decomposing " + BusyWith->ToString() + " into " + to_string(NSubTasks) + "tasks.");
//	cout << "Decomposing " + BusyWith->Task() + " into " << NSubTasks << " tasks.\n";
	Task **SubTasks = new Task*[ NSubTasks ];
	string RootName = BusyWith->ToString() + "__";
	for( int i = 0; i < NSubTasks; i++ ) {
		SubTasks[i] = new Task( RootName );
	}
	int TasksCursor = 0;
	Acolyte *Subordinate;
	while( TasksCursor < NSubTasks  && ( Subordinate =  MySubdivs->FindFreeWorker() ) ) {
		if( Subordinate->SetTaskFrom( this, SubTasks[ TasksCursor ] ) ) {
			TasksCursor++;
		} 
		else {
			Say( "Its enoght tasks!\n" );
			break;
		}
	}
	if( TasksCursor == NSubTasks ) {
		Say("All subtasks placed. Deleting " + BusyWith->ToString() );
		delete BusyWith;
		BusyWith = nullptr;
	}
	
	else {
		Say( " insufficient subordinates! Still busy with " +  BusyWith->ToString() );
	}
		
	
	
}

void Acolyte::Say( string Phrase = "") {
	string Output = ToString() + ": ";
	cout << Output + Phrase + "\n";
}

bool Acolyte::GenerateIdea() {
	if( BusyWith ){
		Say("Already busy. Cannot generate idea.\n" );
		return false;	
	} 
	else {
		BusyWith = new Task;
		Say("Generated new idea " + BusyWith->ToString() ) ;
		Acolyte *FreeSubordinate;
		if( !MySubdivs  ) {
		 	Say(" Have no subdivision!"); return false; 
		}
		if( FreeSubordinate = MySubdivs->FindFreeWorker() ) {
			Say( "FOund Free subordinate " + FreeSubordinate->ToString() );
			if( FreeSubordinate->SetTaskFrom( this, BusyWith ) )
			{
				BusyWith = nullptr;
				Say( "New idea placed to subordinate.\n");
//				FreeSubordinate->ProceedTask();
				return true;
			}
			else {
				Say("Strike found. Saty busy.");
				return false;
			}
		 }
		 else {
		 	Say( "No free subordinate. stay Busy.\n" );
		 	return false;
		 }
	}
}


bool Acolyte::CanOrder() {
	return Rights & 2;
}

