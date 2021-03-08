#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
using namespace std;


// You will need these forward references.
class Expr;
class Stmt;

// Runtime Global Variables
int pc;  // program counter
vector<string> lexemes;
vector<string> tokens;
vector<string>::iterator lexitr;
vector<string>::iterator tokitr;
map<string, int> vartable; // map of variables and their values
vector<Stmt *> insttable; // table of instructions
map<string, string> symboltable; // map of variables to datatype (i.e. sum t_integer)


// Runtime Global Methods
void dump(); // prints vartable, instable, symboltable

// You may need a few additional global methods to manipulate the global variables


// Classes Stmt and Expr
// It is assumed some methods in statement and expression objects will change and
// you may need to add a few new ones.

class Stmt{ // statements are executed!
private:
string name;
public:
Stmt(string s){
name = s;
}
string getName(){
    return name;
}
virtual ~Stmt(){};
virtual string toString() = 0;
virtual void execute() = 0;
};


class AssignStmt : public Stmt{
private:
string var;
Expr* p_expr;

public:
AssignStmt(string t, string s, Expr* e)
:Stmt(t){
var = s;
p_expr = e;
//???
}

~AssignStmt(){
delete p_expr;
}

string toString(){
return Stmt::getName() + " " + var + " " + p_expr->toString();
}

void execute(){
    p_expr->eval();
}

};



class InputStmt : public Stmt{
private:
string var;
public:
InputStmt();
~InputStmt();
string toString();
void execute();
};

class StrOutStmt : public Stmt{
private:
    string value;
public:
    StrOutStmt(string str){
        value = str;
    }

    ~StrOutStmt();

    string toString(){
        Stmt::getName() + " " + value;
    }

    void execute(){
        cout << value << endl;
        //not sure if this should be updated so i did it anyway if an output stment is breaking the code this might be why!!!!!!
        pc++;
    }
};


class ExprOutStmt : public Stmt{
private:
Expr* p_expr;
public:
ExprOutStmt();
~ExprOutStmt();
string toString();
void execute();
};

class IfStmt : public Stmt{
private:
Expr* p_expr;
int elsetarget;

public:
    IfStmt(string t, Expr* e)
    :Stmt(t){
        p_expr = e;
        elsetarget = -1;
    }

    int getElsetarget(){
        return elsetarget;
    }

    void setElsetarget(int i){
        elsetarget = i;
    }

    ~IfStmt(){
        delete p_expr;
    }

    string toString(){
        return Stmt::getName() + IfStmt::p_expr->toString() + elsetarget;
    }

    void execute(){
        cout << "executing" << endl;
    }
};

class WhileStmt : public Stmt{
    private:
        Expr* p_expr;
        int elsetarget;
    public:
        WhileStmt(Expr* expr, int target){
            p_expr = expr;
            elsetarget = target;
        }

        ~WhileStmt();

        string toString(){
             return Stmt::getName() + " " +  p_expr->toString() + " " + elsetarget;
        }

        void execute(){
            if(expr->eval == 1){
                pc++;
            }else{
                pc = elsetarget;
            }
        }
};







class Expr{ // expressions are evaluated!
public:
virtual int eval() = 0;
virtual string toString() = 0;
virtual ~Expr(){}
};


class ConstExpr : public Expr{
private:
    int value;
public:
ConstExpr(int val){
    value = val;
}

int eval(){
    return value;
}

string toString(){
    return value + "";
}
};



class IdExpr : public Expr{
private:
    string id;
public:
IdExpr(string s){
    id = s;
}
int eval();
string toString();
};



class InFixExpr : public Expr{
private:
vector<Expr *> exprs;
vector<string> ops;  // tokens of operators
public:

//Not sure if anything needs to be passed in to this need to discuss with the group.
InFixExpr(){}

void addTerm(Expr* val){
    exprs.push_back(val);
}

void addOp(string op){
    ops.push_back(op);
}

~InFixExpr(){

}

int eval(){
    string temp = exprs[0]->toString();

    for (int i=1; i<exprs.size(); i++){
        str += " " + ops[i] + " ";
        str += exprs[i]->toString();
    } 
}

string toString(){
    string str="";
    str += exprs[0]->toString() + " ";
    for (int i=1; i<exprs.size(); i++){
        str += " " + ops[i] + " ";
        str += exprs[i]->toString();
    } 
}

};



class Compiler{
private:
//each method creats a chunk of memory and puts it in instruction table
void buildIf(){
    //then
    InFixExpr* exp = new InFixExpr();
    if(*tokitr == "t_number"){
        int n = std::stoi(*lexitr);
        Expr* c = new ConstExpr(n);
        exp->addTerm(c);
    }
    else{
        Expr* e = new IdExpr(*lexitr);
        exp->addTerm(e);
    }
    
    tokitr++; lexitr++;
    while(*tokitr != "t_lt" && *tokitr != "t_le" && *tokitr != "t_gt" && *tokitr != "t_ge" && *tokitr != "t_eq" && *tokitr != "t_ne"){
        exp->addOp(*lexitr);
        tokitr++; lexitr++;
        
        if(*tokitr == "t_number"){
            int n = std::stoi(*lexitr);
            Expr* c = new ConstExpr(n);
            exp->addTerm(c);
        }
        else{
            Expr* e = new IdExpr(*lexitr);
            exp->addTerm(e);
        }
        tokitr++; lexitr++;
    }
    exp->addOp(*lexitr);
    tokitr++; lexitr++;
    
    if(*tokitr == "t_number"){
        int n = std::stoi(*lexitr);
        Expr* c = new ConstExpr(n);
        exp->addTerm(c);
    }
    else{
        Expr* e = new IdExpr(*lexitr);
        exp->addTerm(e);
    }
    tokitr++; lexitr++;
    
    while(*tokitr != "s_rparen"){
        exp->addOp(*lexitr);
        tokitr++; lexitr++;
        
        if(*tokitr == "t_number"){
            int n = std::stoi(*lexitr);
            Expr* c = new ConstExpr(n);
            exp->addTerm(c);
        }
        else{
            Expr* e = new IdExpr(*lexitr);
            exp->addTerm(e);
        }
        tokitr++; lexitr++;
    }
}

void buildWhile(){
    InFixExpr* exp = buildExpr("t_while");
    
    //build if statement and put it in insttable
    Stmt* st = new WhileStmt("t_while", exp);
    insttable.push_back(st);
    pc++;

    //iter on then
    tokitr++; lexitr++;
    
    //iter on next stmt in if body
    while(*tokitr!="t_loop"){
        build expression
}

void buildStmt(){
    tokitr++; lexitr++;
    
    //iter on expr
    InFixExpr* exp = buildExpr("t_if");
    
    //build if statement and put it in insttable
    Stmt* st = new IfStmt("t_if", exp);
    insttable.push_back(st);
    pc++;
}

void buildAssign(){
    //tokitr on =
    tokitr--; lexitr--;
    string id = *lexitr;
    tokitr++; lexitr++;
    tokitr++; lexitr++;
    
    InFixExpr* exp = new InFixExpr();
    
    if(*tokitr == "t_number"){
        int n = std::stoi(*lexitr);
        Expr* c = new ConstExpr(n);
        exp->addTerm(c);
    }
    else{
        Expr* e = new IdExpr(*lexitr);
        exp->addTerm(e);
    }
    
    tokitr++; lexitr++;
    while(*tokitr != "s_semi"){
        exp->addOp(*lexitr);
        tokitr++; lexitr++;
        
        if(*tokitr == "t_number"){
            int n = std::stoi(*lexitr);
            Expr* c = new ConstExpr(n);
            exp->addTerm(c);
        }
        else{
            Expr* e = new IdExpr(*lexitr);
            exp->addTerm(e);
        }
        tokitr++; lexitr++;
    }
    
    Stmt* as = new AssignStmt("t_assign", id, exp);
    insttable.push_back(as);
    pc++;
}

void buildInput();
void buildOutput();
// use one of the following buildExpr methods
//void buildExpr(Expr*&);
Expr* buildExpr();
//why?

void populateTokenLexemes(istream& infile){
string line, tok, lex;
int pos;
getline(infile, line);
while(!infile.eof()){
    pos = line.find(":");
    tok = line.substr(0, pos-1);
    lex = line.substr(pos+2, line.length()-2-pos);
    cout << pos << tok << lex << endl;
    tokens.push_back(tok);
    lexemes.push_back(lex);
    getline(infile, line);
}
tokitr = tokens.begin();
lexitr = lexemes.begin();
}

void populateSymbolTable(istream& infile){
    if(*tokitr == "t_var"){
        tokitr++; lexitr++;
        while(*tokitr!="t_begin"){
            if(*tokitr!="s_comma" && *tokitr!="s_semi"){
                symboltable.insert(pair<string, string>(*lexitr, *tokitr));
            }
            tokitr++; lexitr++;
        }
    }
}

public:
Compiler(istream& source, istream& symbols){
    populateTokenLexemes(source);
    populateSymbolTable(symbols);
}

bool compile(){
    // builds the instruction table and declaration check
    //tokeitr on "t_begin"
    tokitr++; lexitr++;
    pc = 0;
    //each method returns increased iterator(iterator on the next chunk)
    while(*tokitr!=tokens.end()){
        if(*tokitr == "t_if"){
            tokitr++; lexitr++;
            if(*tokitr == "s_lparen"){
                tokitr++; lexitr++;
                //lexitr on expr
                buildIf();
            }
            
        }
        else
        if(*tokitr == "t_while"){
            tokitr++; lexitr++;
            buildWhile();
        }
        else
        if(*tokitr == "t_assign"){
            buildAssign();
        }
        else
        if(*tokitr == "t_input"){
            tokitr++; lexitr++;
            buildInput();
        }
        else
        if(*tokitr == "t_output"){
            tokitr++; lexitr++;
            buildOutput();
        }
        else
        if(*tokitr == "t_else"){
            for(int i=0; i<pc; i++){
                Stmt* stm = insttable.at(i);
                if(stm->getName() == "t_if"){
                    IfStmt::stm.setElsetarget(pc);
                }
                
            }
        }
        else
        if(*tokitr == "t_end"){
            tokitr++; lexitr++;
            if(*tokitr == "t_loop"){
                //create a goto object
            }
        }
    }
}
void run(); 
// executes the instruction table
};


int main() {
    ifstream infile("data.txt");
    if (!infile){
    cout << "error opening input file - token/lexeme pairs" << endl;
    }
    else{
    Compiler* c = new Compiler(infile, infile);
    }
    return 1;
}


