#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;
enum Result{
    Fail = 0,
    Success=1,
    Load = 100,
    Add=200,
    Modify=300,
    Move=400,
    Print=500,
    Search=600,
    Select=700,
    Edit=800

};
class Loaded_LIST_Node{   // -------------[Loaded_LIST_Node]-----------
public:
    Loaded_LIST_Node* next=NULL;
    Loaded_LIST_Node* back=NULL;
    Loaded_LIST_Node* down=NULL;
    Loaded_LIST_Node* up=NULL;
    string img_name=""; 
    string dirname="";
    int unique_num;
};
class BST_Node{
public:
    BST_Node*right=NULL;
    BST_Node*left=NULL;
    string bst_name="";
    string bst_dir="";
    int bst_num;
};

class Loaded_LIST
{
    //프랜드클라스 선언해줄것!!!!!!!!!!?
private:
   Loaded_LIST_Node* img_head=NULL ;
public:

    Loaded_LIST(){}//manager에 상속받아서 :해야하나
    void Load_linklist(string name, string dir, int num);
    void Add_linklist(string name, string dir, int num);
    void Load_list_print();
    void Add_list_print();
    void delete_head();
    void delete_tail();
    int Modify_list(string name, string dir, int new_num);
    void test_All_print(); //t삭제해줄것
    Loaded_LIST_Node* find_bst_root();
};

class Tree_manager{
private:
    BST_Node* bst_root=NULL;
public:
    Tree_manager(){}
    void make_bst(Loaded_LIST_Node* bring_node);
    void test_print_bst(); //삭제할것
    void delete_small();
    void BST_Print(BST_Node* currnode);
    BST_Node* get_bst_root(){return bst_root;}
};

class Manager
{
private:
    std::ifstream fin;
    std::ifstream fread;
    std::ifstream fin2;
public:
    Manager() {};
    //~Manager();
    void RUN(const char* filepath);
    void PrintError(Result result);
    void PrintSuc(Result result);

private:
    Result LOAD(const char* filepath,Loaded_LIST* list);
    Result ADD(const char* filepath,string dir_n, string csv_n, string path,Loaded_LIST* list);
    Result MODIFY(const char* filepath,string dir_n, string n_imgname, int n_num, Loaded_LIST* list);
    Result MOVE(const char* filepath,Loaded_LIST*list, Tree_manager* tree);
    Result PRINT(Tree_manager* tree);
};


