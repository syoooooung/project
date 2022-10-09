#include "main.h"
int node_num=0; //count for not upto 100
int bst_node_num=0; //count for not upto 300
#define ALP_LEN 256

int main(int argc, char* argv[])
{
    const char* commandFilepath = "command.txt";
    if (argc > 1)
        commandFilepath = argv[1];

    Manager m;
    m.RUN(commandFilepath);

    return 0;
}

void Loaded_LIST::Add_linklist(string name, string dir, int num){
    Loaded_LIST_Node* currNode=img_head;
    Loaded_LIST_Node* prevNode;
    Loaded_LIST_Node* newNode = new Loaded_LIST_Node;
    
    newNode->img_name = name;
    newNode->dirname = dir;
    newNode->unique_num = num;

    int pass_num = 0;
    while(1)
    {
        if(currNode->dirname==dir){ //find directory node
            pass_num=1;
            break;
        }
        if(currNode->down ==NULL){ //if final node in directory and don't find specific dir_node,
            break;
        }
        currNode=currNode->down;
    }
    if(pass_num==0){ //final node in dir_node
        Loaded_LIST_Node* new_dirnode= new Loaded_LIST_Node; //create new node
        new_dirnode->dirname=dir;
        currNode->down = new_dirnode;
        new_dirnode->up = currNode;
        //currNode = currNode->down;
    }
    Loaded_LIST_Node* new_currNode = new Loaded_LIST_Node; //dir_node->next =>first node of that dir_node
    if (pass_num==0) new_currNode= currNode->down; //if that node is first node of that dir_node
    else if(pass_num==1) new_currNode = currNode; //not first node
    while(new_currNode->next != NULL){
        new_currNode=new_currNode->next; 
    }
    new_currNode->next=newNode;
    newNode->back=new_currNode;
    return ;
}

void Loaded_LIST::Load_linklist(string name, string dir, int num) {
    Loaded_LIST_Node* newNode = new Loaded_LIST_Node;
    newNode->img_name = name;
    newNode->dirname = dir;
    newNode->unique_num = num;
    if (img_head == NULL) { //if that node is first node
        //img_head=newNode;
        //return;
        Loaded_LIST_Node* NEWnode = new Loaded_LIST_Node; //create new dir_node
        NEWnode->dirname = dir;
        img_head = NEWnode;
    }

    Loaded_LIST_Node* CurrNode = img_head;
    while (CurrNode->next != NULL) {
        CurrNode = CurrNode->next;
    }

    CurrNode->next = newNode;
    newNode->back = CurrNode;
    return;
}
void Loaded_LIST::Load_list_print() { //print of Load output
    Loaded_LIST_Node* currnode = new Loaded_LIST_Node;
    currnode = img_head->next;

    cout << "===============LOAD=============" << endl;
    flog << "===============LOAD=============" << endl;
    while (currnode != NULL) {
        cout << currnode->img_name << "/" << currnode->unique_num << endl;
        flog<< currnode->img_name << "/" << currnode->unique_num << endl;
        currnode = currnode->next;
    }
    cout << "==================================" << endl;
    flog << "==================================" << endl;
    return;
}

void Manager::RUN(const char* filepath)
{
    // fout.open(RESULT_LOG_PATH); 
     //ferr.open(ERROR_LOG_PATH); 
    fin.open(filepath);
    flog.open("log.txt",ios::app);
    char cmd[50] = "";
    Loaded_LIST *list=new Loaded_LIST;
    Database_BST* tree=new Database_BST;
    while (!fin.eof()) {
        fin.getline(cmd, 50);
        char* command = strtok(cmd, " ");
        if (command == NULL) { cout << "No command"; return; }

        if (strcmp(command, "LOAD") == 0) {
            if (!LOAD(cmd,list)) { //arr and compare
                PrintError(Load); //if return=>Fail : print error
            }
        }
        else if (strcmp(command, "ADD") == 0) { //경로글자합쳐서 함수로 보내주기
            command=strtok(NULL," ");
            string dir= command; //scan dirname
            command = strtok(NULL,"\n");
            string file_name = command; //scan csv name
            
            string add_path = "./"+dir+"/"+file_name; //make path
            //char* path_add = strcat(tmp1, tmp2);
            if (!ADD(cmd,dir, file_name, add_path,list)) {
                PrintError(Add);
            }
            else{
                PrintSuc(Add);
            }
        }
        else if (strcmp(command,"MODIFY")==0){
            command=strtok(NULL," ");
            string file_name1 = command; //dirname
            command = strtok(NULL,"\"");
            string change_name = command; //imgname
            command = strtok(NULL,"\n"); // eeeeeeeeeeeeeeeroooooooooooooorrrrrrrrrrrs
            string change_num = command; //string num
            int int_NUMBER = atoi(change_num.c_str()); //string => int
            if(!MODIFY(cmd, file_name1, change_name, int_NUMBER, list)){
                PrintError(Modify);
            }
            else{
                PrintSuc(Modify);
            }
        }
        else if(strcmp(command,"MOVE")==0){
            if(!MOVE(cmd, list, tree)){
                PrintError(Move);
            }
            else{
                PrintSuc(Move);
            }
        }
        else if(strcmp(command,"PRINT")==0){
            if(!PRINT(tree)) PrintError(Print);
        }
        else if(strcmp(command,"SEARCH")==0){
            command=strtok(NULL,"\"");
            if(!SEARCH(tree, command)) PrintError(Search);
        }
        else if(strcmp(command, "SELECT")==0){
            command=strtok(NULL,"\n");
            string str = command; //string
            int findnum = atoi(str.c_str()); //string=>int
            if(!SELECT(tree, findnum)) PrintError(Select);
            else{ PrintSuc(Select);}
        }
        else if(strcmp(command,"EDIT")==0){
            command=strtok(NULL,"\n");
            string edit_cmd = command; //what edit
            if(!EDIT(tree,edit_cmd)){PrintError(Edit);}
            else{ PrintSuc(Edit);}
        }
        else if(strcmp(command,"EXIT")==0){
            EXIT(tree, list);
            delete tree;
            delete list;
            PrintSuc(Exit);
            flog.close();
            return;
        }
        else{ //else error
            if(strcmp(command,"ADD")==0){PrintError(Add);}
            else if(strcmp(command,"MODIFY")==0){PrintError(Modify);}
            else if(strcmp(command,"SEARCH")==0){PrintError(Search);}
            else if(strcmp(command,"SELECT")==0){PrintError(Select);}     
            else if(strcmp(command,"EDIT")==0){}//PrintError(Edit);}
            else{PrintError(dontknow);}
        }

    }
    // TODO: implement
}
Result Manager::LOAD(const char* filepath,Loaded_LIST* list) { //bring Loaded List class 
   // Loaded_LIST list;
    string NAME = "0";
    string str_NUMBER;
    string trash1;
    int count = 0;
    //file.open("\\filesnumbers.csv", ios::in); //ios::in=>read file
    fread2.open("./img_files/filesnumbers.csv", ios::in);
    if (fread2.fail()) {
        cout << "no file that path"<<endl;
        //PrintError(Load);
        return Fail;
    } 
    while (!fread2.eof()) {
        getline(fread2, str_NUMBER, ',');
        int int_NUMBER=atoi(str_NUMBER.c_str());
        getline(fread2, NAME, '.');
        getline(fread2,trash1,'\n');
        if(node_num > 100){
            list->delete_head();
            node_num--;
        }
        //int i = stoi(str_NUMBER); //string=>t
        list->Load_linklist(NAME, "img_files", int_NUMBER); //change dirname    
        node_num++;
    }
    list->Load_list_print(); //make linkedlist and print
    fread2.close();
    count++; //whatisthiscount
    return Success;
}

Result Manager::ADD(const char* filepath,string dir_n, string csv_n, string path,Loaded_LIST* list) {//path1=>dirname, path2=>filename
    //Loaded_LIST list;
    string NAME, str_NUMBER, trash1;
    //cout<<path<<endl;
    if(dir_n == "" || csv_n == ""){ return Fail;}
    fin2.open(path,ios::in);
    if (!fin2) {
        cout << "No file that path"<<endl;
        //PrintError(Add);
        return Fail;
    }

     while (!fin2.eof()) {
        getline(fin2, str_NUMBER, ',');
        int int_NUMBER=atoi(str_NUMBER.c_str()); //string =>int
        getline(fin2, NAME, '.');
        getline(fin2,trash1,'\n');
        if(node_num > 100){
            list->delete_head(); //delete head if node up 100
            node_num--;
        }
        list->Add_linklist(NAME, dir_n , int_NUMBER); //change dir nameTT 
        node_num++;  //chech node number
    }
    fin2.close();
    return Success;
}
Result Manager::PRINT(Database_BST* tree){
    if(tree->get_bst_root()==NULL){ //if bst empty=> error
        return Fail;
    }
    else{
        cout<<"===============PRINT==============="<<endl;
        flog<<"===============PRINT==============="<<endl;
        tree->BST_Print(tree->get_bst_root()); 
        cout<<"==================================="<<endl;
        flog<<"==================================="<<endl;
        }
    return Success;
}
Result Manager::MODIFY(const char* filepath,string dir_n, string n_imgname, int n_num, Loaded_LIST* list){
    //if(dir_n=="" || n_imgname==""){return Fail;}
    if(!list->Modify_list(n_imgname, dir_n, n_num)){
        return Fail;
    }
    return Success;
}
Result Manager::MOVE(const char* filepath, Loaded_LIST* list, Database_BST* tree){
    //[1]bring final node
    if(list->get_head()==NULL){return Fail;} //if linkedlist empty=> error
    while(list->find_bst_root()!=NULL){
    if(bst_node_num>300){ //if bst up 300 
        tree->delete_small(); //delete small unique num node
        bst_node_num--;
    }
    tree->make_bst(list->find_bst_root()); //make bst
    bst_node_num++; //chech node number
    list->delete_tail();
    }
    node_num=0;
    return Success;
}
Result Manager::SELECT(Database_BST* tree, int find_num){
    Database_BST_Node*findnode;
    tree->get_find_node(find_num, tree->get_bst_root());
    findnode=tree->get_node();
    if(findnode==NULL){return Fail;} //if not findnode => error
    string path_dir = findnode->bst_dir;
    string path_name = findnode->bst_name;
    string to_path = "./"+path_dir+"/"+path_name+".RAW"; //make raw path 
    tree->put_name(path_name); //imgname save
    tree->put_path(to_path); //path save
    return Success;
}
Result Manager::EDIT(Database_BST* tree, string cmd){
    string img_path = tree->get_path();
    string pre_name = tree->get_name();
    const char* fin_path = img_path.c_str();
    int width = 256, height =256;

    FILE* input_file, *output_file;
    stack<int> s;
    queue<int> q;
    unsigned char input_data[256][256];

    input_file = fopen(fin_path,"rb");
    if(input_file ==NULL){
        cout<<"file not found"<<endl;
        return Fail;
    }
    fread(input_data, sizeof(unsigned char), width* height, input_file);
    
    int i,j=0;
    const char* tmp=cmd.c_str();
    char*tmp1 =(char *)tmp;
    string new_cmd = strtok(tmp1," ");
    //flipped edit
    if(new_cmd=="-f"){
        unsigned char output_data[256][256];
        for(i=0; i<height; i++){
            for(j=0;j<width;j++){
                s.push(input_data[i][j]); //put use stack
            }
        }
        for(i=0; i<height ; i++){
            for(j=0;j<width;j++){
                output_data[i][j]=s.top(); //bring top use stack => flipped!
                s.pop(); //and pop
            }
        }
    string change_path ="./Result/"+pre_name+"_flipped.RAW"; //make new path
    const char* change_path1=change_path.c_str(); //change string=>constchar
    output_file = fopen(change_path1 , "wb");
    fwrite(output_data, sizeof(unsigned char), width*height, output_file);
    }
    
    else if(new_cmd=="-l"){ //edit adjusted
        unsigned char output_data[256][256];
        string str_num=strtok(NULL,"\n");
        int lig_num=atoi(str_num.c_str());

        for(i=0;i<height;i++){
            for(j=0;j<width;j++){
                q.push(input_data[i][j]); //put data use queue
            }
        }
        for(i=0;i<height;i++){
            for(j=0;j<width;j++){
                if(q.front()+lig_num<=255){
                    output_data[i][j]=q.front();} //if final num<255=>plus
                else{
                    output_data[i][j]=255; //max 255 fix
                }
                q.pop(); //pop
            }
        }
        string change_path ="./Result/"+pre_name+"_adjusted.RAW"; //make path
        const char* change_path1=change_path.c_str(); //string=>const char*
        output_file = fopen(change_path1 , "wb");
        fwrite(output_data, sizeof(unsigned char), width*height, output_file);
    }
    else{ //edit resized
        double tmp_num=0;
        unsigned char output_data[128][128]; //resize
        for(i=0;i<128;i++){
            for(j=0;j<128;j++){
                tmp_num = (input_data[2*i][2*j] + input_data[2*i][2*j+1]+input_data[2*i+1][2*j]+input_data[2*i+1][2*j+1])/4;
                output_data[i][j] = round(tmp_num); // 4=>1 and round
            }
        }
        string change_path ="./Result/"+pre_name+"_resized.RAW"; //make path
        const char* change_path1=change_path.c_str(); //string=>const char*
        output_file = fopen(change_path1 , "wb");
        fwrite(output_data, sizeof(unsigned char), 128*128, output_file);
    }
    fclose(input_file); //edit end close file
    fclose(output_file);
    return Success;
}
void Manager::EXIT(Database_BST* tree, Loaded_LIST* list){
    while(tree->get_bst_root() != NULL){ //delete memory
        tree->delete_small();
    }
    while(list->get_head() != NULL){
        list->delete_tail();
    }
    return;
}
void Database_BST::make_bst(Loaded_LIST_Node* bring_node){
    Database_BST_Node* newnode = new Database_BST_Node;
    Database_BST_Node* currnode;
    newnode->bst_dir = bring_node->dirname;
    newnode->bst_name= bring_node->img_name;
    newnode->bst_num= bring_node->unique_num;
    if(bst_root==NULL){ //if root ==null
        bst_root = newnode; //that is root node!!
        return;
    }
    currnode=bst_root; //root Existence
    while(currnode!=NULL){
        if(currnode->bst_num > newnode->bst_num){ //if newnum small
            if(currnode->left ==NULL){ 
                currnode->left=newnode; //go left
                return;
            }
            currnode=currnode->left;
        }
        if(currnode->bst_num < newnode->bst_num){ //if newnum big
            if(currnode->right == NULL){
                currnode->right = newnode; //go right
                return;
            }
            currnode=currnode->right;
        } //else equal => error
        
    }
    

}
void Loaded_LIST::delete_head(){
    Loaded_LIST_Node* currnode = img_head;
    Loaded_LIST_Node* prevnode = img_head;
    //[1] final node that list=> dirnode delete
    //[2] else
    currnode=currnode->next;
    if(currnode->next == NULL){ //final node
        delete currnode;
        img_head = prevnode->down; //next dir_node
        delete prevnode;
        return;
    }
    prevnode->next=currnode->next;
    delete currnode;
    return;
}
int Loaded_LIST::Modify_list(string name, string dir, int new_num){
    Loaded_LIST_Node* currnode;
    Loaded_LIST_Node* prevnode;
    currnode = img_head;
    prevnode= img_head;
    //find same number
    
    while(1){
        while(currnode->next!=NULL){
            currnode=currnode->next;
            if(currnode->unique_num==new_num){return 0;} //that's error!!!
        }
        if(prevnode->down == NULL){break;}
        prevnode=prevnode->down;
        currnode=prevnode;
    }
    currnode = img_head; //restart
    prevnode= img_head;
    
    //first find dirname
    while(1){
        if(currnode->dirname==dir) break;//find dirnode !!
        if(currnode->down==NULL){
            return 0; //error
        }
        currnode= currnode->down;}
    prevnode= currnode;

    while(1){
        if(currnode->img_name == name) break; //find change numebr node 
        if(currnode->next ==NULL){return 0;} //end of node but not find=> error!
        prevnode=currnode;
        currnode=currnode->next;
    }
    Loaded_LIST_Node* newnode = new Loaded_LIST_Node;
    newnode->dirname=dir;
    newnode->unique_num = new_num;
    newnode->img_name = name;
    if(currnode->next==NULL){ //success return
        prevnode->next=newnode; //if final node
        newnode->back=prevnode;
        delete currnode;
        return 1;
    }
    if(currnode->next!=NULL){ //success return
        prevnode->next=newnode;
        newnode->next=currnode->next; //not final node
        currnode->next->back=newnode;
        newnode->back=prevnode;
        delete currnode;
        return 1;
    }
    return 0;
}
Loaded_LIST_Node* Loaded_LIST::find_bst_root(){
    if(img_head==NULL){return NULL;}
    Loaded_LIST_Node*currnode = img_head;
    while(currnode->down != NULL){ //final dirnode
        currnode=currnode->down;
    }
    while(currnode->next != NULL){//final node in that dirnode
        currnode= currnode->next;
    }
    return currnode;
}
void Loaded_LIST::delete_tail(){
    Loaded_LIST_Node*currnode = img_head;
    Loaded_LIST_Node*prevnode = img_head;
    Loaded_LIST_Node*tmp=img_head;
    int how_count=0; //count for how many move
    int how_count_dir=0; //count for how many move dir node
    while(currnode->down != NULL){ //move bottom node
        currnode=currnode->down;
        how_count_dir++;; 
    }
    while(currnode->next != NULL){//that bottom node and final node
        prevnode=currnode;
        currnode= currnode->next;
        how_count++;
    }
    delete currnode; 
    prevnode->next=NULL;
    if(how_count_dir!=0 &&how_count==1){ //not head=dirnode and dirnode next node
        tmp=prevnode->up;
        delete prevnode;
        tmp->down = NULL;
        return;
    }
    if(how_count_dir==0 && how_count==1){ //that node is head->next node
        delete prevnode;
        img_head=NULL;
        return;
    }
    return;
}

void Database_BST::delete_small(){
    Database_BST_Node* currnode=bst_root;
    Database_BST_Node* prevnode=bst_root;
    Database_BST_Node* savenode=NULL; 
    while(currnode->left != NULL){ //find proccess and break
        prevnode=currnode;
        currnode=currnode->left;
    }
    if(currnode == bst_root){ //if root
        savenode=currnode->right;
        delete currnode;
        bst_root=savenode;
    }
    else if(currnode->left == NULL && currnode->right ==NULL){ //no child
        delete currnode;
        prevnode->left=NULL;
    }
    else if(currnode->left ==NULL && currnode->right != NULL){//child only right
        prevnode->left=currnode->right;
        delete currnode; //hmmm////////////////////////////////////////
    }
    else if(currnode->left != NULL){ //left child that's error
        cout<<"delete_small func error"<<endl;
    }
}
void Database_BST::BST_Print(Database_BST_Node*currnode){ //bst print
    if(currnode->left!=NULL) BST_Print(currnode->left);
    cout<<currnode->bst_dir<<" / \""<<currnode->bst_name<<"\" / "<<currnode->bst_num<<endl;
    flog<<currnode->bst_dir<<" / \""<<currnode->bst_name<<"\" / "<<currnode->bst_num<<endl;
    if(currnode->right!=NULL) BST_Print(currnode->right);
}
void Database_BST::postorder(Database_BST_Node* root, string word){
    queue<Database_BST_Node* > q; //using queue stl
    if(root==NULL){ //if not exist bst
        return;
    }
    stack<Database_BST_Node*> s; //using stack stl
    s.push(root); //push rootnode

    stack<Database_BST_Node* > out;
    while(!s.empty()){
        Database_BST_Node* curr = s.top();
        s.pop();

        out.push(curr);
        if(curr->left){
            s.push(curr->left); //postorder
        }
        if(curr->right){
            s.push(curr->right);
        }
    }
    while(!out.empty()){
        //cout<<out.top()->bst_name<<endl;
        q.push(out.top());
        out.pop();
    }
//Queue
    cout<<"================SEARCH=============="<<endl;
    flog<<"================SEARCH=============="<<endl;
    while(!q.empty()){
        //cout<<"heele"<<q.front()->bst_name<<endl;
        const char* tmp = q.front()->bst_name.c_str();
        const char* tmp3=word.c_str(); //string =>const char*
        char* tmp1 = (char *)tmp; //const char* => char*
        char* tmp2 = (char *)tmp3;
        if(search(tmp1, tmp2)==1){
            cout<<"\""<<q.front()->bst_name<<"\" / "<<q.front()->bst_num<<endl;
            flog<<"\""<<q.front()->bst_name<<"\" / "<<q.front()->bst_num<<endl;
        } //print for check
        q.pop();
    }
    cout<<"===================================="<<endl;
    flog<<"===================================="<<endl;

}
Result Manager::SEARCH(Database_BST* tree, string word){
    if(tree->get_bst_root()==NULL || word==""){return Fail;}
    tree->postorder(tree->get_bst_root(),word);
    return Success;
}
void Database_BST::process_1(int *shift, int *bringpos, char *pat, int m)
{ //pre_process for boyermoor 
    int i = m, j = m+1; //m==patter len
    bringpos[i] = j; //bringpos = m+1
    while(i > 0) //i==>j
    {
        while(j <= m && pat[i-1] != pat[j-1])
        {
            if (shift[j] == 0)
                shift[j] = j-i; //j not equal
            j = bringpos[j];
        }
        i--; j--;
        bringpos[i] = j; 
    }
}
void Database_BST::process_2(int *shift, int *bpos, char *pat, int m)
{
    int i, j;
    j = bpos[0]; //p[i-1] != p[j-1]  ==> shift
    for(i=0; i<=m; i++)
    { //if in j => not equal : shift[j+1]
        if(shift[i]==0)
            shift[i] = j;
  
        if (i==j)
            j = bpos[j];
    }
}
int Database_BST::search(char *text, char *pat)
{
    int m = strlen(pat);
    int n = strlen(text);
    int s=0; 
    //pattern move about text
    int bpos[m+1], shift[m+1];
  
    for(int i=0;i<m+1;i++) shift[i]=0;
    
    process_1(shift, bpos, pat, m);
    process_2(shift, bpos, pat, m);
  
    // search string
    while(s <= n-m)
    {
        int j = m-1;
        //text and pattern left->right
        while(j >= 0 && pat[j] == text[s+j])
            j--;
  
         // find pattern in text
        if (j<0) {
            // move pattern next level 
            return 1;
            s += shift[0];
        }
        else {
            // not equal with pattern bpos
            s += shift[j+1];
        }
    }
  return 0;
}
void Database_BST::get_find_node(int findnum, Database_BST_Node* currnode){
    if(currnode != NULL){
        if(currnode->bst_num==findnum){
            put_node(currnode); return;} //find node same numebr that want num =>return
        if(currnode->left!=NULL)get_find_node(findnum,currnode->left);
        if(currnode->right!=NULL)get_find_node(findnum,currnode->right);
    }     
}
void Manager::PrintError(Result result) {  //------------Error_print----------
    cout << "===============ERROR=============" << endl;
    flog << "===============ERROR=============" << endl;
    switch (result)
    {
    case Result::Load: //case Result::Load: ??
        cout << 100 << endl;
        flog << 100 << endl;
        break;
    case Result::Add:
        cout << 200 << endl;
        flog << 200 << endl;
        break;
    case Result::Modify:
        cout << 300 << endl;
        flog<< 300 <<endl;
        break;
    case Result::Move:
        cout<<400<<endl;
        flog<<400<<endl;
        break;
    case Result::Search:
        cout<<600<<endl;
        flog<<600<<endl;
        break;
    case Result::Select:
        cout<<700<<endl;
        flog<<700<<endl;
        break;
    case Result::dontknow:
        cout<<777<<endl;
        flog<<777<<endl;
    case Result::Edit:
        cout<<800<<endl;
        flog<<800<<endl;
        break;

    }
    cout << "==================================" << endl;
    flog << "==================================" << endl;
}
void Manager::PrintSuc(Result result){ //plus add
    cout<<"=============";
    flog<<"=============";
    switch(result){
        case Result::Add:
            cout<<"ADD";
            flog<<"ADD";
            break;
        case Result::Modify:
            cout<<"MODIFY";
            flog<<"MODIFY";
            break;
        case Result::Move:
            cout<<"MOVE";
            flog<<"MOVE";
            break;
        case Result::Select:
            cout<<"SELECT";
            flog<<"SELECT";
            break;
        case Result::Edit:
            cout<<"EDIT";
            flog<<"EDIT";
            break;
        case Result::Exit:
            cout<<"EXIT";
            flog<<"EXIT";
            break;
    }
    cout<<"============="<<endl;
    flog<<"============="<<endl;
    cout<<"SUCCESS"<<endl;
    flog<<"SUCCESS"<<endl;
    cout<<"==============================="<<endl;
    flog<<"==============================="<<endl;
    return;
}