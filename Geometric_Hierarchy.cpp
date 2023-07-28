#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;


class Figure {
	protected:
		double x, y;
		int Size = 4;
		vector<string> color{ "None", "Red", "Green", "Blue" };
	public:	
		Figure( double x, double y, string Color = "") {
			this->x = x;
			this->y = y;
			for( int i = 0; i < this->color.size(); i++ ) this->color[i] = GetColor(Color);
			cout << "Coords: " << "X: " << x << " Y: " << y << endl;
		}
		string GetColor( string Color = "" ) {
			for( int i = 0; i < color.size(); i++ ) {
				if( Color == color[i] ) { return color[i]; } 
			}
			return ""; 
		}

		virtual double Area() const = 0;
		
		virtual void Find_Bounds( double a, double b ) {
			cout << "b " << b << endl;
			a += 2;
    		b *= 2;
    		cout << "b " << b << endl;
    		for ( int i = 0; i < a; i++ ) {
        		for ( int j = 0; j < b; j++ ) {
            		if (( i == 0 && j >= 0 ) || ( i == a - 1 && j >= 0 )) {
                		std::cout << "-";
            		}
            		else if (j == 0 || j == b - 1) {
                		std::cout << "|";
            		}
            		else std::cout<<" ";
        		}
        		std::cout << std::endl;
    		}
    		cout << "External Rectangle size: " <<" side A: " << a << " side B: " << b << endl;
		}
		
		virtual void print() const { };
		void print_color() { 
			for( auto i : color ) {
				cout << i << endl;
				break;
			} 
		}
	};


class Circle: public Figure {
	protected:
		double Radius;
		const double Pi = 3.1415926535;
	public:
		Circle( double radius = 0.0, double x = 0, double y = 0, string color = "None" ) : Figure(x, y, color)  {
			cout << "Circle c- tor here...\n";
			Radius = radius;
			
		}
		double Area() const override {	
			cout << "Circle area is: ";
//			return (atan(1) * 4) * Radius * Radius;
			return Pi * ( Radius * Radius );
		}
		
		void print()  {
			double Diametr = Radius * Radius;
			if( this->color == color) cout << "Radius: " << Radius <<endl << Circle::Area() <<  "\nColor: "; 
			print_color();
			Find_Bounds( Radius, Radius );
		}
		
};

class Sqare: public Figure {
	protected:
		double EdgeLen;
	public:
		Sqare( double edgeLen, double x = 1, double y = 2, string color = "None" ) : Figure( x, y, color ) {
			cout << "Sqare c-tor is here...\n";
			EdgeLen = edgeLen;
		}
		double Area( ) const override { 
			double result = EdgeLen * EdgeLen;
			return result;
		}
		
		void print() {
			cout << "Area: " << Sqare::Area() << endl << "Color: ";
			print_color();
			Find_Bounds( EdgeLen, EdgeLen );
		}
		

};

class Rectangle : public Figure {
	protected:
		double Width, Height;
	public:
		Rectangle( double width, double height, double x = 1, double y = 1, string color = "None"  ) : Figure( x, y, color ) {
			cout << "Rectangle c-tor is here...\n";
			Width = width;
			Height = height;
		}
		
		double Area() const override { return Width * Height; }
		void print() {
			cout << "Area: " << Rectangle::Area() << endl << "Color: "; 
			print_color();
			Find_Bounds( Width, Height ); 
		}
	

}; 

class Triangle : public Figure {
	protected:
		double EdgeLen;
	public:
		Triangle( double EdgeLen, double x, double y, string color = "None" ) :\
		Figure( x, y, color ) {
			cout << "Triangle c-tor is here...\n";
			this->EdgeLen = EdgeLen;
		}
		double Area() const override { return sqrt(3) * pow(EdgeLen, 2) / 4; }
		void print() {
			cout << "Area: " << Triangle::Area() << endl << "Color: ";
			print_color();
			Find_Bounds(EdgeLen, EdgeLen );
		}
	

};


int main() {

	Circle *c = new Circle( 4, 2, 4 );
	c->print();
	
	Sqare *s = new Sqare( 3, 5, 10, "Red" );
	s->print();
	
	Rectangle *rec = new Rectangle( 1, 2, 4, 6, "Blue" );
	rec->print();

	Triangle *tri = new Triangle( 4, 1, 1, "Green" );
	tri->print();
	
	delete c; delete s; delete rec; delete tri;
	
	
	
}

