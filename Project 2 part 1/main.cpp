/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mtcummins
 *
 * Created on May 15, 2019, 10:46 AM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include<iterator>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class LexAnalyzer{
private:
  vector <string> lexemes;   // a string of lexemes that correspond to the input file
  vector <string> tokens;      // a string of tokens that correspond to the input file
  map <string, string> tokenmap;   // a map structure that maps lexemes to their 
  //  <key,data>            // corresponding tokens for easy look up
  // other private methods 
  int Type(char c);
  map <string, string>::iterator itr;
public:

// pre: parameter refers to open data file consisting of token and lexeme pairs
//      i.e.  t_and and t_begin begin t_boolean boolean t_break break
// post: tokenmap has been populated
LexAnalyzer(istream& infile);

  
  // pre: 1st parameter refers to an open text file that contains source code in the 
        //      language, 2nd parameter refers to an open empty output file 
  // post: the token and lexeme pairs for the given input file have been written to 
  //      the output file.  If there is an error, the incomplete token/lexeme pairs,
        //      as well as an error message have printed to the output file.  A success or 
        //      fail message has printed to the console.
void scanFile(istream& infile, ostream& outfile);

};


LexAnalyzer::LexAnalyzer(istream& infile){
  string key;
  string data;
  while (infile >> data >> key) {
    //cout<< key<< ", " << data << endl;
    tokenmap.insert(pair<string,string>(key,data));
  }
  cout << tokenmap.count("(")<<endl;

  /**
  map<string, string>::iterator itr; 
  cout << "\nThe map is: \n"; 
  cout << "\tKEY\tELEMENT\n"; 
  for (itr = tokenmap.begin(); itr != tokenmap.end(); ++itr) { 
    cout << itr->first<<", " << itr->second << endl; 
  } 
  cout << endl; 
  **/
}

void LexAnalyzer::scanFile(std::istream &infile, std::ostream &outfile){
  char c;
  int count=0;
  bool str=false;
  int type;
  bool moved = false;
  std::istream_iterator<char> itr;
  itr = istream_iterator<char>(infile);
  noskipws(infile);
  
  while( itr != istream_iterator<char>()){
      if(moved==false){
        c=*itr;
      }
      moved = false;
      if(c=='='){
            string temp;
            temp+=c;
            itr++;
            c=*itr;
            if(c=='='){
              
                temp+=c;
            }else{
                moved=true;
            }
            tokens.push_back(temp);
            lexemes.push_back(tokenmap.at(temp));
            cout << tokenmap.at(temp)<<", "<<temp<<endl;
        }
        else if(c==','){
            string temp;
            temp+=c;
            tokens.push_back(temp);
            lexemes.push_back(tokenmap.at(temp));
            cout << tokenmap.at(temp)<<", "<<c<<endl;
        }else if(c==':'){
            string temp;
            temp+=c;
            tokens.push_back(temp);
            lexemes.push_back(tokenmap.at(temp));
            cout << tokenmap.at(temp)<<", "<<c<<endl;
        }else if(c=='('){
            string temp;
            temp+=c;
            tokens.push_back(temp);
            lexemes.push_back(tokenmap.at(temp));
            cout << tokenmap.at(temp)<<", "<<c<<endl;
        }else if(c==')'){
            string temp;
            temp+=c;
            tokens.push_back(temp);
            lexemes.push_back(tokenmap.at(temp));
            cout << tokenmap.at(temp)<<", "<<c<<endl;
        }else if(c==';'){
            string temp;
            temp+=c;
            tokens.push_back(temp);
            lexemes.push_back(tokenmap.at(temp));
            cout << tokenmap.at(temp)<<", "<<c<<endl;
        }else if(c=='<'){
            string temp;
            temp+=c;
            itr++;
            c=*itr;
            if(c=='='){
                
                temp+=c;
                moved = false;
            }else{
                moved=true;
            }
            tokens.push_back(temp);
            lexemes.push_back(tokenmap.at(temp));
            cout << tokenmap.at(temp)<<", "<<temp<<endl;
        }else if(c=='>'){
            string temp;
            temp+=c;
            itr++;
            c=*itr;
            if(c=='='){
                
                temp+=c;
                moved =false;
            }else{
                moved=true;
            }
            tokens.push_back(temp);
            lexemes.push_back(tokenmap.at(temp));
            cout << tokenmap.at(temp)<<", "<<temp<<endl;
        }else if(c=='!'){
            string temp;
            temp+=c;
            itr++;
            c=*itr;
            if(c=='='){
                temp+=c;
                moved =false;
                tokens.push_back(temp);
                lexemes.push_back(tokenmap.at(temp));
                cout << tokenmap.at(temp)<<", "<<temp<<endl;
            }else{
                //THROW AN ERROR
                moved=true;
            }
        }else if(c=='+'){
            string temp;
            temp+=c;
            tokens.push_back(temp);
            lexemes.push_back(tokenmap.at(temp));
            cout << tokenmap.at(temp)<<", "<<c<<endl;
        }else if(c=='-'){
            string temp;
            temp+=c;
            tokens.push_back(temp);
            lexemes.push_back(tokenmap.at(temp));
            cout << tokenmap.at(temp)<<", "<<c<<endl;
        }else if(c=='*'){
            string temp;
            temp+=c;
            tokens.push_back(temp);
            lexemes.push_back(tokenmap.at(temp));
            cout << tokenmap.at(temp)<<", "<<c<<endl;
        }else if(c=='/'){
            string temp;
            temp+=c;
            tokens.push_back(temp);
            lexemes.push_back(tokenmap.at(temp));
            cout << tokenmap.at(temp)<<", "<<c<<endl;
        }else if(c=='%'){
            string temp;
            temp+=c;
            tokens.push_back(temp);
            lexemes.push_back(tokenmap.at(temp));
            cout << tokenmap.at(temp)<<", "<<c<<endl;
        }else if(c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9'||c=='0'){
            string temp;
            temp+=c;
            itr++;
            cout<<c;
            c=*itr;
            //cout<< c;
            while ((c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9'||c=='0')&& itr != istream_iterator<char>()){
                temp+=c;
                moved =false;
                cout << c;
                itr++;
                if(itr != istream_iterator<char>()){
                     c=*itr;
                }
            }
            if(c==' '||itr == istream_iterator<char>()){
                moved =false;
                tokens.push_back(temp);
                lexemes.push_back("t_number");
                cout << "t_number"<<", "<<temp<<endl;
            }else{
                //THROW AN ERROR
                moved=true;
            }
            //cout << "in here" << endl;
        }else if(c=='"'){
            cout << "i got here"<< endl;
            string temp;
            temp+=c;
            itr++;
            //cout<<c;
            c=*itr;
            str = true;
            while (str == true){
                if(c=='"' ){
                    str=false;
                }else{
                   temp+=c;
                    itr++;
                    cout<<c;
                    c=*itr;
                }
            }
        }
      
        /**
        if((int)c != -30 ||(int)c != -128||(int)c != -99 || (int)c != -100 ){
            string temp;
            temp+=c;
            while(c!='"'){
                temp+=c;
                moved =false;
                cout << c;
                itr++;
                c=*itr;
            }
        }else{        
            //cout << "a";
        };
        **/
      
        if (moved==false){
            itr++;
        }
        
        
         
    }
}

int LexAnalyzer::Type(char c){
  if(c == ' '){
    cout<<"1";
    return 1;
  }
  cout << "0";
  return 0;
}

/*
 * 
 */
int main(int argc, char** argv) {
    ifstream infile("dataFile.txt");
    LexAnalyzer lex(infile);
    ifstream codeFile("test.txt");
    ofstream outPutFile("output.txt");
    lex.scanFile(codeFile, outPutFile);
    return 0;
}

