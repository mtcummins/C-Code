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
// prints vartable, instable, symboltable
void dump(){
    cout << "the vartable values are:" << endl;
    for (itr = vartable.begin(); itr != vartable.end(); ++itr){
        cout << itr->first << " " << itr->second << endl;
    }

    cout << "the insttable values are:" << endl;
    for(int i=0; i < insttable.size();i++){
        cout << insttable[i]->eval();
    }

    cout << "the symboltable values are:" << endl;
    for (itr = symboltable.begin(); itr != symboltable.end(); ++itr){
        cout << itr->first << " " << itr->second << endl;
    }
}

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

    ~IfStmt(){
        delete p_expr;
    }
    
    void setElsetarget(int i){
        elsetarget = i;
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
        WhileStmt(Expr* expres){
            p_expr = expres;
            elsetarget = -1;
        }

        ~WhileStmt(){
            delete p_expr
        }
        
        void setElsetarget(int i){
            elsetarget = i;
        }

        string toString(){
             return Stmt::getName() + " " +  p_expr->toString() + " " + elsetarget;
        }

        void execute(){
            if(p_expr->eval == 1){
                pc++;
            }else{
                pc = elsetarget;
            }
        }
};

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
        string gotoStmt();
        void execute();
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
    string op;
    int value = exprs[0]->eval();
    for (int i=1; i<exprs.size(); i++){
        op = ops[i-1]->toString();
        
        if(op=="+"){
            vlaue = value + exprs[i]->eval();
        }esle if(op == "-"){
            vlaue = value - exprs[i]->eval();
        }esle if(op == "*"){
            vlaue = value * exprs[i]->eval();
        }esle if(op == "/"){
            vlaue = value / exprs[i]->eval();
        }esle if(op == "%"){
            vlaue = value % exprs[i]->eval();
        }esle if(op == "and"){
            // IDK IF THIS IS THE RIGHT WAY TO DO THIS.
            if(value && exprs[i]->eval()){
                value = 1;
            }esle{
                value = 0;
            }
        }esle if(op == "or"){
            // IDK IF THIS IS THE RIGHT WAY TO DO THIS.
            if(value || exprs[i]->eval()){
                value = 1;
            }eslse{
                value = 0;
            }
        }esle if(op == "=="){
            if(value == exprs[i]->eval()){
                value = 1;
            }eslse{
                value = 0;
            }
        }esle if(op == "<"){
            if(value < exprs[i]->eval()){
                value = 1;
            }eslse{
                value = 0;
            }
        }esle if(op == "<="){
            if(value <= exprs[i]->eval()){
                value = 1;
            }eslse{
                value = 0;
            }
        }esle if(op == ">"){
            if(value > exprs[i]->eval()){
                value = 1;
            }eslse{
                value = 0;
            }
        }esle if(op == ">="){
            if(value >= exprs[i]->eval()){
                value = 1;
            }eslse{
                value = 0;
            }
        }esle if(op == "!="){
            if(value != exprs[i]->eval()){
                value = 1;
            }eslse{
                value = 0;
            }
        }
    } 
    return value;
}

string toString(){
    string str="";
    str += exprs[0]->toString() + " ";
    for (int i=1; i<exprs.size(); i++){
        str += " " + ops[i-1] + " ";
        str += exprs[i]->toString();
    } 
}

};



class Compiler{
private:
//each method creates a statement and puts it in instruction table
void buildIf(){ //building if statement

    tokitr++; lexitr++;
    
    //iter on expr
    InFixExpr* exp = buildExpr("t_if");
    
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
    Stmt* gstm = new gotoStmt("goto");
    insttable.push_back(gstm);
    pc++;
    
    IfStmt::st->setElsetarget(pc);
    
    //iter on t_else
    tokitr++; lexitr++;
    
    //iter on next stmt in elsepart
    while(*tokitr!="t_end"){
        buildStmt();
    }
    
    gotoStmt::st->setTarget(pc);
    
    //iter on t_end
    tokitr++; lexitr++;
    //iter on t_if
    tokitr++; lexitr++;
    //iter on next stmt
    
}

void buildWhile(){
    tokitr++; lexitr++;
    
    InFixExpr* exp = buildExpr("t_while");
    
    //build if statement and put it in insttable
    Stmt* st = new WhileStmt(exp);
    Stmt* gtstmt = new gotoStmt("goto");
    gtstmt->setTarget(pc);
    insttable.push_back(st);
    pc++;

    //iter on then
    tokitr++; lexitr++;
    
    //iter on next stmt in if body
    while(*tokitr!="t_end"){
        buildStmt();
    }
    st->setElseTarget(pc);
    
    //iter on t_end
    tokitr++; lexitr++;
    //iter on t_if
    tokitr++; lexitr++;
}

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
        buildOutput();
    }

}

void buildAssign(string vName){
    //tokitr on num or var
    
    InFixExpr* exp = buildExpr("t_assign");
    
    //iter on ;
    Stmt* as = new AssignStmt("t_assign", vName, exp);
    insttable.push_back(as);
    pc++;
    
    //iter on the next token
    tokitr++; lexitr++;
    
}

void buildInput();
void buildOutput(){
     tokitr++; lexitr++;
     if (*tokitr == "t_string"){
        StrOutStmt stmt = new StrOutStmt(*tokitr);
        insttable.push_back(stmt);
     }else{
        InFixExpr* exp = buildExpr("t_output");
        ExprOutStmt stmt = new ExprOutStmt(exp);
        insttable.push_back(stmt);
     }  
}

// use one of the following buildExpr methods
//void buildExpr(Expr*&);
Expr* buildExpr(string type){
    vector<Expr *> vals;
    vector<string> ops;
    
    //iter on first element of expr
    if(type!="t_assign"){
        int lparen = 0;
        int rparen = 0;
        
        while(rparen <= lparen && *tokitr!="s_semi"){
            if(*tokitr == "t_number"){
                stringstream to_int(*lexitr); 
                int n=0;
                to_int >> n;
                Expr* ce = new ConstExpr(n);
                vals.push_back(ce);
            }

            else
            if(*tokitr == "t_true" || *tokitr == "t_false"){
                Expr* ce = new ConstExpr(*lexitr);
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
        InFixExpr exp = new InFixExpr(vals, ops);
        return exp;
    }
}
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

bool compile(){
    // builds the instruction table and declaration check
    
    //declaration check   
    while(tokitr!=tokens.end()){
        if(*tokitr == "t_id"){
            if(!symboltable.find(*lexitr))
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

