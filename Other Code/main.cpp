#include <cstdlib>
#include <iostream>
using namespace std;

// class Node interface
class ObjectNode{
private:
    int _data;
    ObjectNode* _next;
public:
    ObjectNode();
    ObjectNode(int d, Node* n);
    friend class Shapes;
    friend class ShapesRep;
};
// class Node methods
Node::Node(): _data(0), _next(nullptr) {}
Node::Node(int d, Node* n): _data(d), _next(n) {}





// Class Invariant: An instance of this class acts as a container of MyObject objects
// and a container of string pointers that will point to descriptions (strings) of each
// MyObject object. When a Shapes object is instantiated, an object is created with
// empty containers large enough to hold the number of elements as appropriate for the
// particular constructor called.
class Shapes{
private:
	ObjectNode* _head;
	ObjectNode* _object;
	string** _type;
	int _size;
public:
	Shapes(){_object = NULL; _type = NULL; _size=0;}
	Shapes(int x){
		// Pre: parameter must be >= 1
		// Post: object created with x number of shapes
		_object = new ObjectNode();
		ObjectNode* t = _object, *t2;
		for (int i=1; i<x; i++){
			// i have set this to instantiate the nodes with a _dataValue. not our teacher.
			t2 = new ObjectNode(0);
			t->SetNext(t2);
			t = t2;
		}
		_type = new string*[x];
		_size = x;
	}
}
