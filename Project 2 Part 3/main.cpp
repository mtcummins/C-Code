/*
 * Build and execute an instruction table given a token/lexeme file and 
 * a symbol table.
 */

/* 
 * File:   main.cpp
 * Author: Kateryna Paramonva, Mitchell Cummins, & Shuji Mizoguchi
 *
 * Created on May 31, 2019, 12:25 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
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


class Expr{ // expressions are evaluated!
public:
virtual int eval() = 0;
virtual string toString() = 0;
virtual ~Expr(){}
};

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

//written by Kateryna Paramonova
class AssignStmt : public Stmt{
private:
string var;
Expr* p_expr;

public:
AssignStmt(string t, string s, Expr* e)
:Stmt(t){
var = s;
p_expr = e;
}

~AssignStmt(){
    //delete p_expr;
}

string toString(){
    string str = "";
    str = Stmt::getName() + " " + var;  
    return str;
}

void execute(){
    //p_expr->eval();
    //vartable[var] = p_expr->eval(); //**********
}
};

/*
class InputStmt : public Stmt{
private:
string var;
string inp;
public:
InputStmt(string t, string s)
:Stmt(t){
    var = s;
    inp = "";
}
~InputStmt();

string toString(){
    return var;
}
void execute(){
    cout << "Input your identifier: ";
    cin >> inp;
}
};*/

//coded by Mitchell Cummins

class StrOutStmt : public Stmt{

private:

   string value;

public:

    StrOutStmt(string t, string str)
    :Stmt(t){

        value = str;

    }

 

    ~StrOutStmt();

 

    string toString(){

        Stmt::getName() + " " + value;

    }

 

    //pre the varible value is nonempty

    //post a string is printed out.

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
ExprOutStmt(string t, Expr* p)
:Stmt(t){
    p_expr = p;
}
~ExprOutStmt(){
    //delete p_expr;
}
string toString(){
    //return p_expr->toString();
}
void execute(){
    cout << toString();
}
};


//written by Kateryna Paramonova
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

    ~IfStmt(){
       // delete p_expr;
    }
    
    void setElsetarget(int i){
        elsetarget = i;
    }

    string toString(){
       // return Stmt::getName() + IfStmt::p_expr->toString() + elsetarget;
    }

    void execute(){
        cout << "executing" << endl;
    }
};

/*
class WhileStmt : public Stmt{
    private:
        Expr* p_expr;
        int elsetarget;
    public:
        WhileStmt(string t, Expr* expres)
        :Stmt(t){
            p_expr = expres;
            elsetarget = -1;
        }
 
        ~WhileStmt(); 

        string toString(){
            //return Stmt::getName() + " " +  p_expr->toString() + " " + elsetarget;
            return "";
        }
        void execute(){
          
            if(p_expr->eval == 1){
                pc++;
            }else{
                pc = elsetarget;
            }
             
            
        }
};
*/
 
/*
//written by Kateryna Paramonova
class gotoStmt : public Stmt{
    private:
        int target;
        
    public:
        gotoStmt(string t)
        :Stmt(t){
            target = -1;
        }
        ~gotoStmt();
        
        void setTarget(int i){
            target = i;
        }
        string toString(){
            return "";
        }
        void execute(){
            
        }
};*/

//written by Kateryna Paramonova
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

int eval(){
    return 0;
}
string toString(){
    return id + "";
}
};



class InFixExpr : public Expr{
private:
vector<Expr *> exprs;
vector<string> ops;  // tokens of operators
public:
InFixExpr(vector<Expr *> vals, vector<string> op){
    exprs = vals;
    ops = op;
}
void addTerm(Expr* val){

    exprs.push_back(val);

}

 

void addOp(string op){

    ops.push_back(op);

}

 

~InFixExpr(){

    for(int i=0; i<exprs.size();i++){

        delete exprs[i];

    }

}

//pre the vectors exprs & ops are not empty.

//post the expresions are evaluated and return an integer.

int eval(){

    string op;

    int value = exprs[0]->eval();

    for (int i=1; i<exprs.size(); i++){

        op = ops[i-1];
        if(op=="+"){

            value = value + exprs[i]->eval();

        }else if(op == "-"){

            value = value - exprs[i]->eval();

        }else if(op == "*"){

            value = value * exprs[i]->eval();

        }else if(op == "/"){

            value = value / exprs[i]->eval();

        }else if(op == "%"){

            value = value % exprs[i]->eval();

        }else if(op == "and"){

            // IDK IF THIS IS THE RIGHT WAY TO DO THIS.

            if(value && exprs[i]->eval()){

                value = 1;

            }else{

                value = 0;

            }

        }else if(op == "or"){

            // IDK IF THIS IS THE RIGHT WAY TO DO THIS.

            if(value || exprs[i]->eval()){

                value = 1;

            }else{

                value = 0;

            }

        }else if(op == "=="){

            if(value == exprs[i]->eval()){

                value = 1;

            }else{

                value = 0;

            }

        }else if(op == "<"){

            if(value < exprs[i]->eval()){

                value = 1;

            }else{

                value = 0;

            }

        }else if(op == "<="){

            if(value <= exprs[i]->eval()){

                value = 1;

            }else{

                value = 0;

            }

        }else if(op == ">"){

            if(value > exprs[i]->eval()){

                value = 1;

            }else{

                value = 0;

            }

        }else if(op == ">="){

            if(value >= exprs[i]->eval()){

                value = 1;

            }else{

                value = 0;

            }

        }else if(op == "!="){

            if(value != exprs[i]->eval()){

                value = 1;

            }else{

                value = 0;

            }

        }

    }

    return value;

}
string toString(){
    return "";
}
};



class Compiler{
private:
//each method creates a statement and puts it in instruction table
    
//written by Kateryna Paramonova
//pre: none
//post: an if statement is build and added to the insttable
void buildIf(){ 

    tokitr++; lexitr++;
    
    //iter on expr
    Expr* exp = buildExpr("t_if");
    
    //build if statement and put it in insttable
    Stmt* st = new IfStmt("t_if", exp);
    insttable.push_back(st);
    pc++;

    //iter on then
    tokitr++; lexitr++;
    
    //iter on next stmt in if body
    while(*tokitr!="t_else"){
        buildStmt();
    }

    //build a goto stmt and put it in insttable
//    Stmt* gstm = new gotoStmt("goto");
  //  insttable.push_back(gstm);
    pc++;
    
   // IfStmt::st->setElsetarget(pc);
    
    //iter on t_else
    tokitr++; lexitr++;
    
    //iter on next stmt in elsepart
    while(*tokitr!="t_end"){
        buildStmt();
    }
    
    //gotoStmt::st->setTarget(pc);
    
    //iter on t_end
    tokitr++; lexitr++;
    //iter on t_if
    tokitr++; lexitr++;
    //iter on next stmt
    
}

//coded by Mitchell Cummins
//pre none
//post a while statment is built as well as a goto statment that are

    //put on the instruction table.


void buildWhile(){
    tokitr++; lexitr++;

    Expr* exp = buildExpr("t_while");

    //build if statement and put it in insttable
    //Stmt* st = new WhileStmt("t_while", exp);
//    Stmt* gtstmt = new gotoStmt("goto");
    //gtstmt->setTarget(pc);
    //insttable.push_back(st);
    pc++;

    //iter on loop
    tokitr++; lexitr++;

    //iter on next stmt in if body

    while(*tokitr!="t_end"){

        buildStmt();

    }
    //st->setElseTarget(pc);

    //iter on t_end

    tokitr++; lexitr++;

    //iter on t_loop

    tokitr++; lexitr++;

}

//written by Kateryna Paramonova
//pre: none
//post: an appropriate build method is called for token
void buildStmt(){
    string varName;
    if(*tokitr == "t_if"){
        tokitr++; lexitr++;
        //tokitr on (
        buildIf();
    }
    
    else
    if(*tokitr == "t_while"){
        tokitr++; lexitr++;
        //tokitr on (
        buildWhile();
    }
    
    else
        if(*tokitr == "t_id"){
            varName = *lexitr;
            tokitr++; lexitr++;
            if(*tokitr == "t_assign"){
                tokitr++; lexitr++;
                //tokitr on num or var
                buildAssign(varName);
            }
        }

    else
    if(*tokitr == "t_input"){
        tokitr++; lexitr++;
        //tokitr on (
        buildInput();
    }
    
    else
    if(*tokitr == "t_output"){
        tokitr++; lexitr++;
        //tokitr on (
        //buildOutput();
    }

}

//written by Kateryna Paramonova
//pre: none
//post: an assignment statement is built and added to insttable
void buildAssign(string vName){
    //tokitr on num or var
    
    Expr* exp = buildExpr("t_assign");
    
    //iter on ;
    Stmt* as = new AssignStmt("t_assign", vName, exp);
    insttable.push_back(as);
    pc++;
    
    //iter on the next token
    tokitr++; lexitr++;
    
}

//written by Shuji
void buildInput(){
    tokitr++; lexitr++;
    
   // Stmt* i = new InputStmt("t_input",*lexitr);
   // insttable.push_back(i);
    
    //iter on id
    tokitr++; lexitr++;
    
    tokitr++; lexitr++;
    tokitr++; lexitr++;
    //iter on next 
}

//coded by Mitchell Cummins
//pre none
//post an output statment of either type string or expression is built
    //and put on to the instruction table.

void buildOutput(){

     tokitr++; lexitr++;

     if (*tokitr == "t_string"){

        Stmt* stmt = new StrOutStmt("t_output",*tokitr);

        insttable.push_back(stmt);

     }else{

        Expr* exp = buildExpr("t_output");

        Stmt* stmt = new ExprOutStmt("t_output",exp);

        insttable.push_back(stmt);

     } 

}

 

// use one of the following buildExpr methods
//void buildExpr(Expr*&);

//written by Kateryna Paramonova
//pre: none
//post: the expression of needed type is returned
Expr* buildExpr(string type){
    vector<Expr *> vals;
    vector<string> ops;
    
    //iter on first element of expr
    if(type!="t_assign"){
        int lparen = 0;
        int rparen = 0;
        
        while(rparen <= lparen && *tokitr!="s_semi"){
            if(*tokitr == "t_number"){
                string str = *lexitr;
                stringstream to_int(str); 
                int n=0;
                to_int >> n;
                Expr* ce = new ConstExpr(n);
                vals.push_back(ce);
            }

            else
            if(*tokitr == "t_true" || *tokitr == "t_false"){
                Expr* ce;
                if(*tokitr == "t_true"){
                    ce = new ConstExpr(1);
                }
                else{
                    ce = new ConstExpr(0);
                }
                
                vals.push_back(ce);
            }

            else
            if(*tokitr == "t_id"){
                Expr* e = new IdExpr(*lexitr);
                vals.push_back(e);
            }

            else
                if(*tokitr == "s_lparen"){
                    lparen++;
                }
            
                else
                    if(*tokitr == "s_rparen"){
                        rparen++;
                    }
            
                    else{
                        ops.push_back(*lexitr);
                    }
            
            tokitr++; lexitr++;
        }      
    }
    
    //iter on token past ) or ;
    
    if(ops.empty()){
        return vals.at(0);
    }
    else{
        Expr* exp = new InFixExpr(vals, ops);
        return exp;
    }
}
//why?

//written by Kateryna Paramonova
//pre: valid infile is passed
//post: token/lexem vectors are populated
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

//written by Kateryna Paramonova
//pre: valid infile is passed
//post: symboltable populated
void populateSymbolTable(istream& infile){
    string line, tok, lex;
    int pos;
    getline(infile, line);
    while(!infile.eof()){
        pos = line.find(":");
        tok = line.substr(0, pos-1);
        lex = line.substr(pos+2, line.length()-2-pos);
        //cout << pos << tok << lex << endl;
        symboltable.insert(pair<string,string> (lex, tok));
        getline(infile, line);
    }
}

public:
Compiler(istream& source, istream& symbols){
    populateTokenLexemes(source);
    populateSymbolTable(symbols);
    compile();
}

//written by Kateryna Paramonova
//pre: token/lexeme vectors and symboltable are populated
//post: instruction table populated, the result of declaration check returned
bool compile(){
    // builds the instruction table and declaration check
    
    //declaration check   
    while(tokitr!=tokens.end()){
        if(*tokitr == "t_id"){
            if(symboltable.count(*lexitr) == 0)
                return false;
        }
        tokitr++; lexitr++;
    }
    
    tokitr = tokens.begin();
    lexitr = lexemes.begin();

    pc = 0;
    //each method returns increased iterator(iterator on the next chunk)
    while(*tokitr!="t_begin"){
        tokitr++; lexitr++;
    }
    
    //iterator on t_begin
    tokitr++; lexitr++;
    while(tokitr!=tokens.end()){
        buildStmt();
    }
    
    return true;
}
void run();
        /*
    for(int it = 0; it != insttable.size(); it++){ 
         ))Assignmentstmt
         ))ifstmt-----------------------------------------
         ))constexpr*********
         ))inputstmt
         ))exproutstmt
         ))idexpr*********
         ))stroutstmt
         ))whilestmt--------------------------------------
         ))infixexpr*********
         
        if(insttable[it] != "t_if" && "t_while"){
            insttable[it]->execute();
        }
        else if(insttable[it] == "t_if"){
            if(insttable[it]->execute() == false){
                it = pc;
            }
            else{
                it = pc;
            }
        }
        else if(insttable[it] == "t_while"){
            while(insttable[it]->execute() == true){
                //loop???
            }
            it = pc;
        }
    }
// executes the instruction table*/
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