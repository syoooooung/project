#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <stack>
#include <queue>
#include <cstdio>
#include <cmath>

using namespace std;

std::ofstream flog; //ofstream for outputtextfile

enum Result{ //Enum fo errorcode and successcode
    Fail = 0,
    Success=1,
    Load = 100,
    Add=200,
    Modify=300,
    Move=400,
    Print=500,
    Search=600,
    Select=700,
    Edit=800,
    Exit=900

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
class Database_BST_Node{
public:
    Database_BST_Node*right=NULL;
    Database_BST_Node*left=NULL;
    string bst_name="";
    string bst_dir="";
    int bst_num;
};

class Loaded_LIST
{
    //프랜드클라스 선언해줄것!!!!!!!!!!?
private:
   Loaded_LIST_Node* img_head=NULL ; //head of 2D_Linked_List
public:

    Loaded_LIST(){}
    void Load_linklist(string name, string dir, int num);//make_Load_linkedlist
    void Add_linklist(string name, string dir, int num); //make_add_linkedlist
    void Load_list_print(); //load output print
    void delete_head(); //nodenumebr 100up=> delete from front
    void delete_tail(); //move BSt and delete tail
    int Modify_list(string name, string dir, int new_num); //modify node find func
    Loaded_LIST_Node* find_bst_root(); //bst root return func
    Loaded_LIST_Node* get_head(){return img_head;} //2D linked list head return func
};

class Database_BST{
private:
    Database_BST_Node* bst_root=NULL;
    Database_BST_Node* pre_cur=NULL;
    string im_path="";
    string before_name="";
public:
    Database_BST(){}
    void make_bst(Loaded_LIST_Node* bring_node); //bst maker
    void delete_small(); //bst node 300up => delete func
    void BST_Print(Database_BST_Node* currnode); //print bst
    Database_BST_Node* get_bst_root(){return bst_root;} //return bst_root
    void get_find_node(int findnum,Database_BST_Node* root); //find specific node for select
    void postorder(Database_BST_Node* root, string word); //postorder 
    int search(char *text, char *pat); //Boyer-Moore func
    void process_2(int *shift, int *bpos, char *pat, int m); //pretreatment for boyer1
    void process_1(int *shift, int *bpos,char *pat, int m); //pretreatment for boter2
    void put_path(string path){im_path = path;} //save path in private
    void put_name(string name){before_name = name;} //save img_name in private
    string get_path(){return im_path;} //return path
    string get_name(){return before_name;} //return img_name
    void put_node(Database_BST_Node* sav){pre_cur=sav;} //save node in private for select
    Database_BST_Node* get_node(){return pre_cur;} //return precur
};

class Manager
{
private:
    std::ifstream fin;
    std::ifstream fread2;
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
    Result MOVE(const char* filepath,Loaded_LIST*list, Database_BST* tree);
    Result PRINT(Database_BST* tree);
    Result SEARCH(Database_BST* tree, string word);
    Result SELECT(Database_BST* tree, int finde_num);
    Result EDIT(Database_BST* tree,string cmd);
    void EXIT(Database_BST* tree, Loaded_LIST* list);
};


