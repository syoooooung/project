#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;
enum Result {
    Success = 0,
    Load = 100,
    Add = 200,
    Modify = 300,
    Move = 400,
    Print = 500,
    Search = 600,
    Select = 700,
    Edit = 800

};
class Manager
{
private:
    std::ifstream fin;

public:
    Manager() {};
    //~Manager();
    void RUN(const char* filepath);

    void PrintError(Result result);
private:
    Result LOAD(const char* filepath);
    Result ADD(char* path1, char*path2);
};

class Loaded_LIST_Node {   // -------------[Loaded_LIST_Node]-----------
public:
    Loaded_LIST_Node* next = NULL;
    Loaded_LIST_Node* down = NULL;
    string img_name; //->
    string dirname;
    string unique_num;
};
class Loaded_LIST
{ 
private:
    Loaded_LIST_Node* img_head = NULL;

public:
    Loaded_LIST() {}//manager에 상속받아서 :해야하나
    void Load_linklist(string name, string dir, string num);
    void Load_list_print();
};
