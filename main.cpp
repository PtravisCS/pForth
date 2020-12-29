#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <typeinfo>
#include <typeindex>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <stack>
#include <math.h>
#include <algorithm>

using namespace std;

//numeric stack
std::stack<double> st;

//string stack
std::stack<string> sst;
vector<string> tokenize(vector<string>);

//create type for function pointers used in map.
typedef void (*voidFunctionType)(void);

/**
 * Struct used to contain the map powering the dictionary.
 *
*/
struct Interface {

  unordered_map<string, pair<voidFunctionType, type_index>> m1; //Unordered map containing funcion pointers corresponding to dictionary words

  template<typename T> //
  void insert(string s1, T f1) {
    auto tt = type_index(typeid(f1));
    m1.insert(make_pair(s1, make_pair((voidFunctionType)f1, tt)));
  }

  template<typename T, typename... Args>
  T searchAndCall(string s1, Args&&... args) {

    auto mapIter = m1.find(s1);

    auto mapVal = mapIter->second;

    auto typeCastedFun = (T(*)(Args ...))(mapVal.first);

    assert(mapVal.second == type_index(typeid(typeCastedFun)));
    return typeCastedFun(forward<Args>(args)...);

  }

  bool keyInMap(string key) {

    if (m1.find(key) == m1.end()) {
      return false;
    } else {
      return true;
    }

  }

};

/**
 * Name:        isNum
 * Parameters:  String s, a string to be tested.
 * Returns:     Bool, true if the string is a number, false otherwise.
 * Desc:        Tests if a string is a number.
*/
bool isNum(const string &s) {

  return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);

}

void reads() {

 string str;
 getline(cin,str);

 sst.push(str);

 return;

}

void duplicate() {

  if (!st.empty()) {
    auto value = st.top();
    st.push(value);
  } else {
    cout << "Stack Underflow at: " << __LINE__ << endl;
  }

  return;

}

void drop() {

  if (!st.empty()) {

    st.pop();

  } else {

    cout << "Stack Underflow at: " << __LINE__ << endl;

  }

  return;

}

void add() {

  if (st.size() >= 2) {

    auto num1 = st.top();
    st.pop();
    auto num2 = st.top();
    st.pop();
    st.push(num1 + num2);

  } else {

    cout << "Stack Underflow at: " << __LINE__ << endl;

  }

  return;

}

void mult() {

  if (st.size() >= 2) {

    auto num1 = st.top();
    st.pop();
    auto num2 = st.top();
    st.pop();
    st.push(num1 * num2);

  } else {

    cout << "Stack Underflow at: " << __LINE__ << endl;

  }

  return;

}

void sub() {

  if (st.size() >= 2) {

    auto num1 = st.top();
    st.pop();
    auto num2 = st.top();
    st.pop();
    st.push(num2 - num1);

  } else {

    cout << "Stack Underflow at: " << __LINE__ << endl;

  }

  return;

}

void divide() {

  if (st.size() >= 2) {

    auto num1 = st.top();
    st.pop();
    auto num2 = st.top();
    st.pop();
    st.push(num2 / num1);

  } else {

    cout << "Stack Underflow at: " << __LINE__ << endl;

  }

  return;

}

void print() {

  if (!st.empty()) {

    cout << st.top() << endl;
    st.pop();

  } else {

    cout << "Stack Underflow at: " << __LINE__ << endl;

  }

  return;

}

void sprint() {

  if (!sst.empty()) {

    cout << sst.top() << endl;
    sst.pop();

  } else {

    cout << "String Stack Underflow at: " << __LINE__ << endl;

  }

}

//prints the current contents of the numeric stack
//destroys stack contents in the process
void s() {

  vector<double> contents;

  cout << "---------" << endl;
  while (!st.empty()) {

    contents.push_back(st.top());
    cout << st.top() << endl;
    st.pop();

  }
  cout << "---------" << endl;
 
  for (int i = contents.size(); i --> 0; ) {
    st.push(contents[i]);
  }

  return;

}

void nswap() {

  if (st.size() >= 2) {
    double var1 = st.top();
    st.pop();
    double var2 = st.top();
    st.pop();

    st.push(var1);
    st.push(var2);
  } else {

    cout << "Stack Underflow at: " << __LINE__ << endl;

  }

  return;

}

//( a b --  a b a)
void over() {

  if (st.size() >= 2) {

    double var1 = st.top();
    st.pop();
    double var2 = st.top();
    st.pop();

    st.push(var1);
    st.push(var2);
    st.push(var1);

  } else {

    cout << "Stack Underflow" << endl;

  }

  return;

}

// ( a b c -- b c a )
void rot() {

  if (st.size() >= 3) {

    double var1 = st.top();
    st.pop();
    double var2 = st.top();
    st.pop();
    double var3 = st.top();
    st.pop();

    st.push(var1);
    st.push(var3);
    st.push(var2);

  }

  return;

}

void cr() {

  cout << endl;

  return;

}

int main(int argc, char *argv[]) {

  int c = 0;

  string fileIn;
  string fileOut;


  //Get command line operators and process them.
  while ((c = getopt (argc, argv, "h?f:o:")) != -1) {
    switch(c) {
      case 'f':
        fileIn = optarg;
        break;
      case 'o':
        fileOut = optarg;
        break;
      case '?':
        cout << endl;
        cout << "Pforth: A FORTH varient developed in C++" << endl;
        cout << "Author: Paul Travis" << endl;
        cout << "----------------------------------------" << endl;
        cout << "f - file to transpile" << endl;
        cout << "o - file to output" << endl;
        cout << endl;
        break;
      default:
        cout << "Error unrecognized operand or unspecified file" << endl;
        cout << "terminating" << endl;
        cout << endl;
        return -1;
        break;
    }
  }

  //create file object to store input file.
  ifstream file;

  //attempt to open input file.
  file.open(fileIn.c_str());

  //initialize vector to store code
  vector<string> code;

  //test if file successfully opened
  if (file.is_open()) { //if the file opened

    string line;
    cout << "Opened file" << endl;

    //read code line by line
    while (getline (file,line)) {
      //place code into vector
      code.push_back(line);
    }

    //close the file containing the code
    file.close();

  } else { //if the file failed to open

    cout << "Failed to open file" << endl;
    return -1;

  }

  try {

    //split all contained strings by space
    //place all such strings into their own index of the vector
    code = tokenize(code);
  } catch (...) {

    return -1;
  }

  Interface wordMap;
  wordMap.insert("dup",duplicate);
  wordMap.insert("drop",drop);
  wordMap.insert("+",add);
  wordMap.insert("*",mult);
  wordMap.insert("-",sub);
  wordMap.insert("/",divide);
  wordMap.insert(".",print);
  wordMap.insert(".s",s);
  wordMap.insert("rot",rot);
  wordMap.insert("over",over);
  wordMap.insert("swap",nswap);
  wordMap.insert("cr",cr);
  wordMap.insert("reads",reads);
  wordMap.insert("s.",sprint);

  /*
  wordMap.searchAndCall<void>("dup");
  wordMap.searchAndCall<void>("+",__LINE__);
  wordMap.searchAndCall<void>(".");
  wordMap.searchAndCall<void>("+",__LINE__);
  */

  for (int i = 0; i < code.size(); i++) {

    if (isNum(code[i])) { //if code is a number push it to the stack

      st.push(atof(code[i].c_str()));
      cout << "Was a number" << endl;

    } else if (code[i] == "(") {//if code is a comment block ignore it

      while (code[i] != ")") {

        i++;

      }
    
    } else if (code[i] == "\"") {//if code is a string push it to the string stack (darn single datatype stack)
      
      string str = "";
      i++;

      while (code[i] != "\"") { //until end of string keep adding each character to str varaible

        str += code[i];
        i++;

      }

      sst.push(str); //push str varaible to string stack

    } else if (wordMap.keyInMap(code[i])) { //else if code corresponds to a command

      wordMap.searchAndCall<void>(code[i]); //execute command corresponding to code

    } else { //code was not a comment, string, or a command

      cout << "Syntax Error on Word: " << i << endl;

    }

  }

  return 0;

}


/*
 * Name: tokenize
 * Parameters: vector<string>, a vector containing code to be tokenized
 * Returns: vector<string>, a vector containing tokenized code
 * Desc: takes a string vector with space delmited code and returns a vector containing
 *       each token in an individual index.
 *
 */
vector<string> tokenize(vector<string> code) {

  string line, token;
  char delim = ' '; //space delimeter
  vector<string> tokens; //vector to be returned containing each token on an individual line
  stringstream stream; //stream used to help tokenize each line

  for (int i = 0; i < code.size(); i++) {
    line = code[i];
    stream << line; //place line into the string stream
    cout << "Line = " << line << endl;
    while (getline (stream, token, delim)) { //while there are still tokens in the line
      if (!(token == "\"")) { //if the token is not a quotation mark (indicating a string)
        tokens.push_back(token); //put the token into the vector 
      } else {

        tokens.push_back(token); //put the quotation mark into the vector 
        getline(stream, token); //get the rest of the line and place it into the string named token
        char tmp = token.back(); //get the last char of the string stored in token for testing.
        token.pop_back(); //remove the last character of the string stored in token. This is presumed to be a quotation mark. 
        
        if (tmp == '\"') {

          tokens.push_back(token); //place the string into the vector
          tokens.push_back("\""); //place an ending quotation mark into the vector
        } else {
          
          cerr << "Syntax Error" << endl;
          cerr << "Incorrect syntax near " << token << "On line " << i + 1 << endl;
          throw "Syntax Error";
        }
      }
    }
    stream.clear();
  }


  return tokens;

}
