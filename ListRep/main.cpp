#include <cstdlib>
#include <iostream>
using namespace std;

// class Node interface
class Node{
private:
    int _data;
    Node* _next;
public:
    Node();
    Node(int d, Node* n);
    friend class List;
    friend class ListRep;
};
// class Node methods
Node::Node(): _data(0), _next(nullptr) {}
Node::Node(int d, Node* n): _data(d), _next(n) {}

// class ListRep interface
class ListRep{
private:
    Node* _head;
    Node* _tail;
    unsigned _rctr;
    ListRep();
    ~ListRep();
    ListRep(const ListRep& b);
    const ListRep& operator=(const ListRep& b);
    void Free();
    void Copy(const ListRep& b);
    friend class List;
};
// class ListRep methods
void ListRep::Free(){
    Node* n = _head;
    while (n != nullptr){
        Node* t = n->_next;
        delete n;
        n = t;
    }
}

void ListRep::Copy(const ListRep& b){
    if (b._head == nullptr){
        _head = _tail = nullptr;
        return;
    }
    Node* newnode = new Node(b._head->_data, nullptr);
    _head = newnode;
    Node* prev = _head;
    Node* temp = b._head->_next;
    while (temp != nullptr){
        newnode = new Node(temp->_data, nullptr);
        prev->_next = newnode;
        temp = temp->_next;
        prev = prev->_next;
    }
    _tail = prev;
}

ListRep::ListRep(){
    cout << "in ListRep()" << endl;
    _head = _tail = nullptr;
    _rctr = 1;
}

ListRep::ListRep(const ListRep& b){
    cout << "in ListRep(const ListRep)" << endl;
    Copy(b);
    _rctr = 1;
}

ListRep::~ListRep(){
    cout << "in ~ListRep()" << endl;
    Free();
}

const ListRep& ListRep::operator=(const ListRep& b){
    cout << "in ListRep oper=" << endl;
    if (this != &b){
        Free();
        Copy(b);
    }
    return *this;
}
// class List interface
class List{
private:
    ListRep* _rep;
public:
    List();
    List(const List& b);
    ~List();
    const List& operator=(const List& b);
    void Unique();
    void Print();
    void Add(int a);
};
// class List methods
List::List(){
    cout << "in List()" << endl;
    _rep = new ListRep();
}
List::~List(){
    cout << "in ~List()" << endl;
    _rep->_rctr--;
    if (_rep->_rctr == 0){
        // calls ~ListRep
        delete _rep;  
    }
}
List::List(const List& b){
    cout << "in List(const List&)" << endl;
    _rep = b._rep;
    _rep->_rctr++;
}
const List& List::operator=(const List& b){
    cout << "in List oper=" << endl;
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
void List::Print(){
    cout << "_rep is pointing at address " << _rep << endl;
    cout << "_rctr is  " << _rep->_rctr << endl;
    cout << "Node values: " << endl;
    Node* t = _rep->_head;   
    while(t != nullptr){
        cout << "\t" << t->_data << " is at address " << t << endl;
        t = t->_next;
    }
}
void List::Add(int a){
    cout << "in List Add" << endl;
    Unique();
    // we are letting List add the Node
    Node* t = new Node(a, nullptr);
    if(_rep->_head == nullptr){
        _rep->_head = t;
        _rep->_tail = _rep->_head;
    }
    else{
        _rep->_tail->_next = t;
        _rep->_tail = t;
    }
}
void List::Unique(){
    cout << "in List Unique" << endl;
    if(_rep->_rctr == 1)
        return;
    _rep->_rctr--;
    _rep = new ListRep(*_rep);
}
/*
 * 
 */
int main(int argc, char** argv) {
    cout << "Main - List n" << endl;
    List n;
    n.Add(5);
    n.Add(6);
    n.Print();
    cout << endl;

    cout << "Main - List m" << endl;
    List m(n); // copy constructor 
    m.Print();
    cout << endl;

    cout << "Main - List p" << endl;
    List p;
    p.Print();
    p=n;
    p.Print();
    cout << endl;
    p.Add(7);
    p.Print();
    
    return 0;
}

