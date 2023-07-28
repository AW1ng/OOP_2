#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <time.h>
#include "getrandomint.h"
#define VERBOSE false

using namespace std;

string Names[10] = { "None", "Alex", "Nazar", "Nick", "Kate", "Mike", "Peter", "Olga", "Paul", "Mary" };
int len = sizeof(Names) / sizeof(Names[1]);

template <typename T>
std::string to_string( const T& value )
{
  std::ostringstream ss;
  ss << value;
  return ss.str();
}


class Branch {
	protected:
		static bool RandomInited;
		static int IDCounter;
		Random R;
		int ID;
		int Level;
		int NChildren;
		Branch *Parent;
		Branch **Children;
		string Name;
		void DeepCounter( string Value, int *Counter ) {
			if( Value == Name ) (*Counter)++;
			for( int i = 0; i < NChildren; i++ ) { Children[i]->DeepCounter( Value, Counter ); }
		}
		void DeepPositions( string Value, Branch*** Positions, int *cursor ) {
			if( Value == Name ) {
				(*Positions)[ *cursor ] = this;
				(*cursor)++;
			}
			for( int i = 0; i < NChildren; i++ ) { Children[i]->DeepPositions( Value, Positions, cursor ); }
		}
				
	public:
		const Branch *const* GetChildren() { return Children; } 
		int GetNChildren() { return NChildren; }
		Branch( int level = 0, int max_level = 2, Branch* parent = nullptr ) {
			if( !RandomInited )  {
				R.get_random(0, 1);
				RandomInited = true;
			}
			if( VERBOSE )cout << "\nBranch C- tor is here...";
			ID = IDCounter++;
			Parent = parent;
			Name = "";
			Level = level;
			if( !level ) {
				if( VERBOSE ) cout << "Creating tree...\n";
				NChildren = R.get_random(3, 5);
				if( VERBOSE ) cout << "With " << NChildren << " big branches...";
				Children = new Branch*[ NChildren ]; //  Children = массив указателей из нчилдрен
				for( int i = 0; i < NChildren; i++ ) {
					Children[i] = new Branch( level + 1, max_level, this );
				}
			}
			else if( level > max_level ) cout << "Max level reached\n";
			else if( level == 1 ) {
				if( VERBOSE ) cout << "Creating medium branch...\n";
				NChildren = R.get_random(2, 3);
				if( VERBOSE ) cout << "With " << NChildren << " small branches...";
				Children = new Branch*[ NChildren ]; //  Children = массив указателей из нчилдрен
				for( int i = 0; i < NChildren; i++ ) {
					Children[i] = new Branch( level + 1, max_level, this );
				}
			}
			else if( level == 2 ) {
				if( VERBOSE ) cout << "Creating samall branch...\n";
				NChildren = 0;
				if( VERBOSE ) cout << "With no sub-branches...";
				Children = nullptr; //  Children = массив указателей из нчилдрен
			}
		}
		
			
		~Branch() {
			if( VERBOSE ) for( int j = 0; j <= Level; j++ ){ cout << "   "; }
			if( VERBOSE ) cout << "Branch D-tor is here...\n";
			if( Children ) {	
				for( int i  = 0; i < NChildren; i++ ) {
					if( VERBOSE ) for( int j = 0; j <= Level; j++ ){ cout << "   "; }
					if( VERBOSE ) cout << "Deliting child " << i << endl;
					delete Children[i];
				}
			}
			else{
				if( VERBOSE ) for( int j = 0; j <= Level; j++ ) cout << "   ";
				if( VERBOSE ) cout << "No Children \n";
			} 
		}
		void SetName ( string name ) { Name = name; }
		
		string GetNameID() const { return GetName() + " " + to_string( ID ); }
		
		string GetName() const { 
			if(Name == "") return "None";
			else return Name;
		}
		
		void SetNames() {
			string name = Names[R.get_random(0, 9)] ;
			cout<< Level;
			if( Level && name != "None") SetName( name ); // no elves on the floor
			for( int i = 0; i < NChildren; i++ ) {
				Children[i]->SetNames();
			}
			
		}
		
		string ToString() {
			string result = "";
			if( Level > 0 ) result += " (" + to_string(Level) + ")";
			return result;
		}
		
		int ValueCounter( string Value ) {
			int Counter = 0;
			DeepCounter( Value, &Counter );
			return Counter;
		}
		
		int FoundValue( string Value, Branch*** Positions ) { //
			int NFound = ValueCounter( Value );
			if( NFound ) {
				int cursor = 0;
				if ( *Positions == nullptr )
				*Positions = new Branch*[ NFound ];
				DeepPositions( Value, Positions, &cursor );
			}
			return NFound;
		}
		
		int NNeighbours() {
			int counter = 0;
			if( !Parent ) return 0;
			if( Parent->GetName() != "None" ) counter++;
			if( Level > 1 ) {
				int NCoChilds = Parent->GetNChildren();
				const Branch *const* CoChilds = Parent->GetChildren();
				for( int i = 0; i < NCoChilds; i++ ) {
					if( CoChilds[i]->GetName() != "None" ) counter++;
				}
			}
			else {
				for( int i = 0; i < NChildren; i++ ) {
					if( Children[i]->GetName() != "None" ) { counter++; }
				}
				counter++;
			}
			return counter;
		}
//		Branch** () { // массив в котором указны места где лежат эльфы с этти именем
//			
//		}
		
/*		void FindName( const string &ame ) {
			Branch *Seeker;
			
			cout << "\n\nSearching...\n";
			cout << NChildren << " " << Level <<"\n";
			if( this->Name == ame ) return;
			for( int i  = 0; i < NChildren; i++ ) {
				for(int j = 0; j < Level; j++ ) {
//					cout << "Name ";  cout << Name;
					if( Level == 2 ) cout << Name;
				}
				return Children[i]->FindName( ame );
			}
		} */


/*		void FindName( string name ) {
			int i;
			for( i  = 0; i < NChildren; i++ ) {
				for( int j = 0; j <= Level; j++ ) { cout << "   "; 
					if( this->Name == name ) cout << Name;
				}
				return Children[i]->FindName(Name);
			}
			
		} */


		void Print(  ) {
			for( int j = 0; j <= Level; j++ ) cout << "    ";
			/*if( Name == "" ) cout << "\n    None"<< endl;
			else cout << Name;
			cout << endl; */
			cout << GetNameID() << endl;
			for( int i = 0; i < NChildren; i++ ) {
				Children[i]->Print();
			} 
		}
};


bool Branch::RandomInited = false;
int Branch::IDCounter = 0;
class Forest {
	protected:
		Branch **Data;
		int NTrees;
//		vector<Branch> Trees;
	public:
		Forest( int NTrees = 5 ) {
			this->NTrees = NTrees;
			Data = new Branch*[ NTrees ];
			for( int i = 0; i < NTrees; i++ ) {
				Data[i] = new Branch;
			}
		}
		~Forest() { for( int i = 0; i < NTrees; i++ ) delete Data[i]; delete Data; }
		
		void SetNames() {
			for( int i = 0; i < NTrees; i++ ) Data[i]->SetNames();	
		}
		
		void Print() {
			for( int i = 0; i < NTrees; i++ ) {
				cout << "Tree number " << i << endl;
				Data[i]->Print();
			}
		}
		
		int ValueCounter( string Value, int **TreeCounters ) {
			int counter = 0;
			*TreeCounters = new int [ NTrees ];
			for( int i = 0; i < NTrees; i++) {
				(*TreeCounters )[i] = Data[i]->ValueCounter( Value ); // сколько всего "Pete" сидит на каждом дереве
			}
			return NTrees;
		} 
		
		int FoundValues( string Value, Branch ***Positions ) {
			int *Counters;
			ValueCounter( Value, &Counters );
			int counter = 0;
			for( int i = 0; i < NTrees; i++ ) counter += Counters[i];	
			*Positions = new Branch*[ counter ];
			Branch** cursor = *Positions;
			for( int i = 0; i < NTrees; i++ ) {
				Data[i]->FoundValue( Value, &cursor ) ;
				cursor += Counters[i];
			}
			//TODO: Fill these positions // массив указателей на все вершины деревьев.
			return counter;
		}
};


main() {
	Forest *Village = new Forest;
	Village->SetNames();
	Village->Print();
	Branch **Petes;
	int NameCounter = Village->FoundValues( "Peter", &Petes );
	for( int i = 0; i < NameCounter; i++ ) cout << "( " << i + 1 << " ; " << Petes[i]->GetNameID() + " " + to_string(Petes[i]->NNeighbours() ) << " ) ";
	
	/*int *NameCounters;
	int NCounter = Village->ValueCounter( "Peter", &NameCounters );
	for( int i = 0; i < NCounter; i++ ) {
		cout << "( " << i << " ; " << NameCounters[i] << " ) ";
	}
	cout << endl;
	delete Village; */
	
/*	Branch* Tree = new Branch;
	Tree->SetNames();
	cout << "\n";
	Tree->Print();
	cout << endl;
	cout << "Alex found" <<" " << Tree->ValueCounter("Alex") << " times";
	Branch** Positions;
	int NFound = Tree->FoundValue("Alex", &Positions );
	cout << "\n\n";
	for( int i = 0; i < NFound; i++ ) {
		int NNeigh = Positions[i]->NNeighbours();
		cout << Positions[i]->GetName() << " " <<NNeigh <<  endl;
	}
	
	if( Positions ) delete Positions;
	int NChilds = Tree->GetNChildren();
	const Branch *const* BigBranches = Tree->GetChildren();
	cout << "Big Branches:\n";
	for( int i = 0; i < NChilds; i++ ) {
		cout << BigBranches[i]->GetName() << endl;
	}
	delete Tree; */
	
	return 0;
}
