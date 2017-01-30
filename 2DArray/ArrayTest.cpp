
#include<iostream>
using namespace std;

#include "Array.h"

class Point {
public:	
	friend ostream &operator<<( ostream &output, const Point &ob ) {
    	output<<"( "<<ob.m_x<<", "<<ob.m_y<<" )";
    	
    	return output;
    }
    
    Point(float x=0, float y=0):m_x(x), m_y(y) {
    }
    
    Point(const Point& other):m_x(other.m_x), m_y(other.m_y) {
    }

private:    
    float m_x, m_y;
};

//#include <string.h>

int main() {
	Array<Point> a1(10, 10);
	
	//Array Map(5, 5);
	
	for(int x = 0; x < a1.length(); x++) {
		for(int y = 0; y < a1[x].length(); y++) {
			a1[x][y] = Point(x*2.5, y*1.0L);
		}
	}
	
	cout<<"a1: "<<a1<<endl;
	return 0;
}
