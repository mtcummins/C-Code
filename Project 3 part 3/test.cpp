//coded by Mitchell Cummins
//pre none
//post will print out everything contained in vartable, instable, and symboltable
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

-------------------------------------------------------------------------

//coded by Mitchell Cummins
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

    //pre the varible value is nonempty
    //post a string is printed out.
    void execute(){
        cout << value << endl;
        //not sure if this should be updated so i did it anyway if an output stment is breaking the code this might be why!!!!!!
        pc++;
    }
};

-------------------------------------------------------------------------------------------------------------------------

//coded by Mitchell Cummins
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
            delete p_expr;
        }
        
        //pre none.
        //post the else target is set.
        void setElsetarget(int i){
            elsetarget = i;
        }


        string toString(){
             return Stmt::getName() + " " +  p_expr->toString() + " " + elsetarget;
        }

        //pre p_expr is not a nullptr & a else target has been set.
        //post the pc counter will be set to the next instruction needed to run.
        void execute(){
            if(p_expr->eval == 1){
                pc++;
            }else{
                pc = elsetarget;
            }
        }
};

------------------------------------------------------------------------------------------------

//coded by Mitchell Cummins
class InFixExpr : public Expr{
private:
vector<Expr *> exprs;
vector<string> ops;  // tokens of operators
public:

InFixExpr(){}

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

----------------------------------------------------------------------------------------------

//coded by Mitchell Cummins
//pre none
//post a while statment is built as well as a goto statment that are 
    //put on the instruction table.
void buildWhile(){
    tokitr++; lexitr++;
    
    InFixExpr* exp = buildExpr("t_while");
    
    //build while statement and put it in insttable
    Stmt* st = new WhileStmt(exp);
    Stmt* gtstmt = new gotoStmt("goto");
    gtstmt->setTarget(pc);
    insttable.push_back(st);
    pc++;

    //iter on loop
    tokitr++; lexitr++;
    
    //iter on next stmt in if body
    while(*tokitr!="t_end"){
        buildStmt();
    }
    st->setElseTarget(pc);
    
    //iter on t_end
    tokitr++; lexitr++;
    //iter on t_loop
    tokitr++; lexitr++;
}

-----------------------------------------------------------------

//coded by Mitchell Cummins
//pre none
//post an output statment of either type string or expression is built
    //and put on to the instruction table.
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