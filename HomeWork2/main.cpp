#include <cstdlib>
#include <iostream>
using namespace std;

// class Node interface
class ObjectNode{
private:
    int _obj;
    ObjectNode* _next;
public:
    ObjectNode();
    ObjectNode(int d, ObjectNode* n);
    friend class Shapes;
    friend class ShapesRep;
};
// class Node methods
ObjectNode::ObjectNode(): _obj(0), _next(nullptr) {}
ObjectNode::ObjectNode(int d, ObjectNode* n): _obj(d), _next(n) {}




// Class Invariant: An instance of this class acts as a container of MyObject objects
// and a container of string pointers that will point to descriptions (strings) of each
// MyObject object. When a Shapes object is instantiated, an object is created with
// empty containers large enough to hold the number of elements as appropriate for the
// particular constructor called.
class ShapesRep{
private:
	//this is the head of the list.
	ObjectNode* _object;
	string** _type;
	int _size;
        unsigned _rctr;
	ShapesRep();
	ShapesRep(int x);
        ~ShapesRep();
        ShapesRep(const ShapesRep& b);
        const ShapesRep& operator=(const ShapesRep& b);
        void Free();
        void Copy(const ShapesRep& b);
        friend class Shapes;
};

//
void ShapesRep::Free(){
    cout << "in Free()" << endl;

    ObjectNode* n = _object;
    while (n != nullptr){
        ObjectNode* t = n->_next;
        delete n;
        n = t;
    } 
    if(_type != nullptr){
        for (int i=0; i<_size; i++){
            delete _type[i];
        }
    }
    delete _type;

    _size = 0;
}

void ShapesRep::Copy(const ShapesRep& b){
    if (b._object == nullptr){
        _object = nullptr;
        _type = nullptr;
        _size = 0;
        return;
    }
    
    ObjectNode* newObj = new ObjectNode(b._object->_obj, nullptr);
    _object = newObj;
    ObjectNode* prev = _object;
    ObjectNode* temp = b._object->_next;
    while (temp != nullptr){
        newObj = new ObjectNode(temp->_obj, nullptr);
        prev->_next = newObj;
        temp = temp->_next;
        prev = prev->_next;
    }

     _type = new string*[b._size];
    for(int i=0; i < b._size; i++){
        _type[i] = b._type[i];
    }
    _size = b._size;
}

ShapesRep::ShapesRep(){
    cout << "in ShapesRep()" << endl;
    _object = nullptr;
    _type = nullptr;
    _size = 0;
    _rctr = 1;
}

ShapesRep::ShapesRep(int x){
    // Pre: parameter must be >= 1
    // Post: object created with x number of shapes
    cout << "in ShapesRep(int x)" << endl;
    _object = new ObjectNode();
    ObjectNode* t = _object, *t2;
    for (int i=1; i<x; i++){
        // i have set this to instantiate the nodes with a _dataValue. not our teacher.
        t2 = new ObjectNode(i, nullptr);
	t->_next = t2;
        t = t2;
    }
     _size = x;
    
    _type = new string*[x];
    for(int i=0; i< _size;i++){
        _type[i] = new string(" "); 
        cout << "the string is "<<*_type[i] << endl;
    }
    _rctr = 1;
}

ShapesRep::ShapesRep(const ShapesRep& b){
    cout << "in ShapesRep(const ShapesRep)" << endl;
    Copy(b);
    _rctr = 1;
}

ShapesRep::~ShapesRep(){
    cout << "in ~ShapesRep()" << endl;
    Free();
}

const ShapesRep& ShapesRep::operator =(const ShapesRep& b){
    cout << "in ShapesRep oper=" << endl;
    if (this != &b){
        Free();
        Copy(b);
    }
    return *this;
}


// class Shapes interface
class Shapes{
private:
    ShapesRep* _rep;
public:
    Shapes();
    Shapes(int x);
    Shapes(const Shapes& b);
    ~Shapes();
    const Shapes& operator=(const Shapes& b);
    void Unique();
    void Print();
    void AddObject(int a);
};

Shapes::Shapes(){
    cout << "in Shapes()" << endl;
    _rep = new ShapesRep();
}

Shapes::Shapes(int x){
    cout << "in Shapes(int x)" << endl;
    _rep = new ShapesRep(x);
}

Shapes::~Shapes(){
    cout << "in ~Shapes()" << endl;
    _rep->_rctr--;
    if (_rep->_rctr == 0){
        // calls ~ListRep
        delete _rep;  
    }
}

const Shapes& Shapes::operator =(const Shapes& b){
    cout << "in Shapes oper=" << endl;
    if(this != &b){
        _rep->_rctr--;
        if (_rep->_rctr == 0){
            // calls ~ListRep
            delete _rep;  
        }
        _rep = b._rep;
        _rep->_rctr++;
    }
    return *this;
}

void Shapes::Print(){
    cout << "_rep is pointing at address " << _rep << endl;
    cout << "_rctr is  " << _rep->_rctr << endl;
    cout << "_size is " << _rep->_size << endl;
    cout << "ObjectNode values: " << endl;
    ObjectNode* t = _rep->_object;   
    while(t != nullptr){
        cout << "\t" << t->_obj << " is at address " << t << endl;
        t = t->_next;
    }
    cout << "_type values: " << endl;
    int i = 0;
    while(_rep->_type != nullptr && i<_rep->_size && _rep->_type[i] != nullptr){
        cout << "\t" <<*_rep->_type[i] << endl;
        i++;
    }
}

void Shapes::AddObject(int a){
    cout << "in List Add" << endl;
    //Unique();
    // we are letting List add the Node
    ObjectNode* t = new ObjectNode(a, nullptr);
    if(_rep->_object == nullptr){
        _rep->_object = t;
        _rep->_object = _rep->_object;
        _rep->_size++;
    }
    else{
        ObjectNode* n = _rep->_object;
        while(n->_next != nullptr){
            n = n->_next;
        }
        n->_next = t;
        _rep->_size++;
    }
}




/*
 * 
 */
int main(int argc, char** argv) {
    cout << "Main - List n" << endl;
    Shapes n(1);
    n.AddObject(5);
    n.AddObject(6);
    n.Print();
    cout << endl;
    
    return 0;
}

