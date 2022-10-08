#include "main.h"
int node_num=0;
int bst_node_num=0;
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
        if(currNode->dirname==dir){ //e디렉토리 노드 참음
            pass_num=1;
            break;
        }
        if(currNode->down ==NULL){ //디렉토리에서의 마지막 노드일때까지 대릭테로리노드 못찾으면
            break;
        }
        currNode=currNode->down;
    }
    if(pass_num==0){ //디렉토리에서의 마지막 노드임
        Loaded_LIST_Node* new_dirnode= new Loaded_LIST_Node; //새로운 대렉토리 노드를 만들어줄것
        new_dirnode->dirname=dir;
        currNode->down = new_dirnode;
        new_dirnode->up = currNode;
        //currNode = currNode->down;
    }
    Loaded_LIST_Node* new_currNode = new Loaded_LIST_Node;
    if (pass_num==0) new_currNode= currNode->down;
    else if(pass_num==1) new_currNode = currNode;
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
    if (img_head == NULL) {
        //img_head=newNode;
        //return;
        Loaded_LIST_Node* NEWnode = new Loaded_LIST_Node;
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
void Loaded_LIST::Load_list_print() {
    Loaded_LIST_Node* currnode = new Loaded_LIST_Node;
    currnode = img_head->next;

    cout << "===============LOAD=============" << endl;
    while (currnode != NULL) {
        cout << currnode->img_name << "/" << currnode->unique_num << endl;
        currnode = currnode->next;
    }
    cout << "==================================" << endl;
    return;
}

void Loaded_LIST::Add_list_print(){
    Loaded_LIST_Node* currnode;
    currnode=img_head->down;
    currnode=currnode->next;
    cout<<"==============ADD================="<<endl;
    cout<<"Success"<<endl;
    while(currnode!=NULL){
        cout<<currnode->img_name<<" / "<<currnode->unique_num<<endl;
        currnode=currnode->next;
    }
    cout<<"=================================="<<endl;
    return;
}
void Manager::RUN(const char* filepath)
{
    // fout.open(RESULT_LOG_PATH); 
     //ferr.open(ERROR_LOG_PATH); //에러코드 파일 열라고?
    fin.open(filepath);
    char cmd[50] = "";
    Loaded_LIST *list=new Loaded_LIST;
    Tree_manager* tree=new Tree_manager;
    while (!fin.eof()) {
        fin.getline(cmd, 50);
        char* command = strtok(cmd, " ");
        if (command == NULL) { cout << "No command"; return; }

        if (strcmp(command, "LOAD") == 0) {
            if (!LOAD(cmd,list)) { //일단 정렬하고 비교
                PrintError(Load);
            }
        }
        else if (strcmp(command, "ADD") == 0) { //경로글자합쳐서 함수로 보내주기
            command=strtok(NULL," ");
            string dir= command;
            command = strtok(NULL,"\n");
            string file_name = command;
            
            string add_path = "./"+dir+"/"+file_name;
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
            string file_name1 = command;
            command = strtok(NULL,"\"");
            string change_name = command;
            command = strtok(NULL,"\n"); // eeeeeeeeeeeeeeeroooooooooooooorrrrrrrrrrr주의 " 500"일케읽힘
            string change_num = command;
            int int_NUMBER = atoi(change_num.c_str());
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
            string str = command;
            int findnum = atoi(str.c_str());
            if(!SELECT(tree, findnum)) PrintError(Select);
            else{ PrintSuc(Select);}
        }

    }
    // TODO: implement
}
Result Manager::LOAD(const char* filepath,Loaded_LIST* list) { //Loaded List class 불러오자 ///구현 안 끄남 loadelist 먼저 만들거임
   // Loaded_LIST list;
    string NAME = "0";
    string str_NUMBER;
    string trash1;
    int count = 0;
    //file.open("E:\\filesnumbers.csv", ios::in); //ios::in=>파일을 읽겠다는 뜻
    fread.open("./img_files/filesnumbers.csv", ios::in);
    if (fread.fail()) {
        cout << "해당 경로에 파일이 없음"<<endl;
        //PrintError(Load);
        return Fail;
    } 
    while (!fread.eof()) {
        getline(fread, str_NUMBER, ',');
        int int_NUMBER=atoi(str_NUMBER.c_str());
        getline(fread, NAME, '.');
        getline(fread,trash1,'\n');
        if(node_num > 100){
            list->delete_head();
            node_num--;
        }
        //int i = stoi(str_NUMBER); //string=>t
        list->Load_linklist(NAME, "img_files", int_NUMBER); //안에 전달할 넣어주기 dir이름 변경해야해ㅠ    
        node_num++;
    }
    list->Load_list_print(); //링크드리스트 만든 후 출력
    fread.close();
    count++; //이거!!!!!!!!!!!!!!!!!!!!!!!!!!!111수정 !!!!!!!!!!!11count++에드에서할것
    return Success;
}

Result Manager::ADD(const char* filepath,string dir_n, string csv_n, string path,Loaded_LIST* list) {//path1=>dirname, path2=>filename
    //Loaded_LIST list;
    string NAME, str_NUMBER, trash1;
    //cout<<path<<endl;//삭제해줄것
    
    fin2.open(path,ios::in);
    if (!fin2) {
        cout << "해당 경로에 파일이 없음"<<endl;
        //PrintError(Add);
        return Fail;
    }

     while (!fin2.eof()) {
        getline(fin2, str_NUMBER, ',');
        int int_NUMBER=atoi(str_NUMBER.c_str());
        getline(fin2, NAME, '.');
        getline(fin2,trash1,'\n');
        if(node_num > 100){
            list->delete_head();
            node_num--;
        }
        list->Add_linklist(NAME, dir_n , int_NUMBER); //안에 전달할 넣어주기 dir이름 변경해야해ㅠ  
        node_num++;  
    }
    list->Add_list_print(); //링크드리스트 만든 후 출력
    fin2.close();
    return Success;
}
Result Manager::PRINT(Tree_manager* tree){
    if(tree->get_bst_root()==NULL){
        return Fail;
    }
    else{tree->BST_Print(tree->get_bst_root()); }
    return Success;
}
Result Manager::MODIFY(const char* filepath,string dir_n, string n_imgname, int n_num, Loaded_LIST* list){
    if(!list->Modify_list(n_imgname, dir_n, n_num)){
        return Fail;
    }
    list->test_All_print();
    return Success;
}
Result Manager::MOVE(const char* filepath, Loaded_LIST* list, Tree_manager* tree){
    //[1]마지막 노드를 가져올것
    while(list->find_bst_root()!=NULL){
    if(bst_node_num>300){
        tree->delete_small();
        bst_node_num--;
    }
    tree->make_bst(list->find_bst_root());
    bst_node_num++;
    list->delete_tail();
    }
    node_num=0;
    tree->test_print_bst();
    return Success;
}
Result Manager::SELECT(Tree_manager* tree, int find_num){
    BST_Node*findnode;
    findnode= tree->get_find_node(find_num, tree->get_bst_root());
    if(findnode==NULL){return Fail;}
    string path_dir = findnode->bst_dir;
    string path_name = findnode->bst_name;
    string to_path = "./"+path_dir+"/"+path_name+".raw";
    tree->get_put_path(to_path);
    return Success;

}
void Tree_manager::make_bst(Loaded_LIST_Node* bring_node){
    BST_Node* newnode = new BST_Node;
    BST_Node* currnode;
    newnode->bst_dir = bring_node->dirname;
    newnode->bst_name= bring_node->img_name;
    newnode->bst_num= bring_node->unique_num;
    if(bst_root==NULL){
        bst_root = newnode;
        return;
    }
    currnode=bst_root;
    while(currnode!=NULL){
        if(currnode->bst_num > newnode->bst_num){
            if(currnode->left ==NULL){
                currnode->left=newnode;
                return;
            }
            currnode=currnode->left;
        }
        if(currnode->bst_num < newnode->bst_num){
            if(currnode->right == NULL){
                currnode->right = newnode;
                return;
            }
            currnode=currnode->right;
        } //엘스이프로 가틍ㄴ게 나오면 오류해줘야해
        
    }
    

}
void Loaded_LIST::delete_head(){
    Loaded_LIST_Node* currnode = img_head;
    Loaded_LIST_Node* prevnode = img_head;
    //[1]그 리스트에서 마지막 노드일 경우=>dir노드까지 없애준다
    //[2]아닌경우로
    currnode=currnode->next;
    if(currnode->next == NULL){
        delete currnode;
        img_head = prevnode->down;
        delete prevnode;
        return;
    }
    prevnode->next=currnode->next;
    delete currnode;
    return;
}
void Loaded_LIST::test_All_print(){
    Loaded_LIST_Node* currnode = img_head;
    Loaded_LIST_Node* dirnode= img_head;
    while(dirnode != NULL){
        cout<<"==============="<<currnode->dirname<<"================"<<endl;
        currnode=currnode->next;
        while(currnode!=NULL){
            cout<<currnode->img_name<<" / "<<currnode->unique_num<<endl;
            currnode=currnode->next;
        }
        dirnode=dirnode->down;
        currnode=dirnode;
        cout<<"================================================="<<endl;
    }
    return;
}
int Loaded_LIST::Modify_list(string name, string dir, int new_num){
    Loaded_LIST_Node* currnode;
    Loaded_LIST_Node* prevnode;
    currnode = img_head;
    //먼저 디렉토리 찾기
    while(1){
        if(currnode->dirname==dir) break;//디랙토리 노드 찾아다
        if(currnode->down==NULL){
            return 0; //반환값 수정 오류코드 보내도록
        }
        currnode= currnode->down;}
    prevnode= currnode;

    while(1){
        if(currnode->img_name == name) break; //숫자바꿀노드찾았다
        if(currnode->next ==NULL){return 0;} //끝까지왔는데 찾는게 없어 ㅠㅠ=>오류!
        prevnode=currnode;
        currnode=currnode->next;
    }
    Loaded_LIST_Node* newnode = new Loaded_LIST_Node;
    newnode->dirname=dir;
    newnode->unique_num = new_num;
    newnode->img_name = name;
    if(currnode->next==NULL){ //성공 리턴
        prevnode->next=newnode;
        newnode->back=prevnode;
        delete currnode;
        return 1;
    }
    if(currnode->next!=NULL){ //성공리턴
        prevnode->next=newnode;
        newnode->next=currnode->next;
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
    while(currnode->down != NULL){ //맨밑 디렉토리 노드까지 온다
        currnode=currnode->down;
    }
    while(currnode->next != NULL){//그 줄에서 제일 끝까지 간다.
        currnode= currnode->next;
    }
    return currnode;
}
void Loaded_LIST::delete_tail(){
    Loaded_LIST_Node*currnode = img_head;
    Loaded_LIST_Node*prevnode = img_head;
    Loaded_LIST_Node*tmp=img_head;
    int how_count=0;
    int how_count_dir=0;
    while(currnode->down != NULL){ //맨밑 디렉토리 노드까지 온다
        currnode=currnode->down;
        how_count_dir++;;
    }
    while(currnode->next != NULL){//그 줄에서 제일 끝까지 간다.
        prevnode=currnode;
        currnode= currnode->next;
        how_count++;
    }
    delete currnode; 
    prevnode->next=NULL;
    if(how_count_dir!=0 &&how_count==1){
        tmp=prevnode->up;
        delete prevnode;
        tmp->down = NULL;
        return;
    }
    if(how_count_dir==0 && how_count==1){
        delete prevnode;
        img_head=NULL;
        return;
    }
    return;
}
void Tree_manager::test_print_bst(){
    BST_Node*currnode= bst_root;
    while(currnode != NULL){
        cout<<currnode->bst_num<<" "<<currnode->bst_name<<endl;
        currnode=currnode->right;
    }
    return;
}
void Tree_manager::delete_small(){
    BST_Node* currnode=bst_root;
    BST_Node* prevnode=bst_root;
    BST_Node* savenode=NULL; 
    while(currnode->left != NULL){ //오직 찾는과정 반복탈출후delete할것
        prevnode=currnode;
        currnode=currnode->left;
    }
    if(currnode == bst_root){ //루트일 경우
        savenode=currnode->right;
        delete currnode;
        bst_root=savenode;
    }
    else if(currnode->left == NULL && currnode->right ==NULL){ //자식X
        delete currnode;
        prevnode->left=NULL;
    }
    else if(currnode->left ==NULL && currnode->right != NULL){//오른쪽자식만O
        prevnode->left=currnode->right;
        delete currnode; //아,,이거 오류나는거아니냐////////////////////////////////////////
    }
    else if(currnode->left != NULL){ //왼쪽자식이 오ㅙ있니
        cout<<"delete_small 함수에서 오류발생"<<endl;
    }
}
void Tree_manager::BST_Print(BST_Node*currnode){
    if(currnode->left!=NULL) BST_Print(currnode->left);
    cout<<currnode->bst_dir<<" / \""<<currnode->bst_name<<"\" / "<<currnode->bst_num<<endl;
    if(currnode->right!=NULL) BST_Print(currnode->right);
}
void Tree_manager::postorder(BST_Node* root, string word){
    queue<BST_Node* > q;
    if(root==NULL){
        return;
    }
    stack<BST_Node*> s;
    s.push(root);

    stack<BST_Node* > out;
    while(!s.empty()){
        BST_Node* curr = s.top();
        s.pop();

        out.push(curr);
        if(curr->left){
            s.push(curr->left);
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
    while(!q.empty()){
        //cout<<"들어왔니"<<q.front()->bst_name<<endl;
        const char* tmp = q.front()->bst_name.c_str();
        const char* tmp3=word.c_str();
        char* tmp1 = (char *)tmp;
        char* tmp2 = (char *)tmp3;
        if(search(tmp1, tmp2)==1){
            cout<<"\""<<q.front()->bst_name<<"\" / "<<q.front()->bst_num<<endl;
        }
        q.pop();
    }
    cout<<"===================================="<<endl;

}
Result Manager::SEARCH(Tree_manager* tree, string word){
    if(tree->get_bst_root()==NULL){return Fail;}
    tree->postorder(tree->get_bst_root(),word);
    return Success;
}
void Tree_manager::process_1(int *shift, int *bpos, char *pat, int m)
{
    int i = m, j = m+1;
    bpos[i] = j;
    while(i > 0)
    {
        while(j <= m && pat[i-1] != pat[j-1])
        {
            if (shift[j] == 0)
                shift[j] = j-i;
            j = bpos[j];
        }
        i--; j--;
        bpos[i] = j; 
    }
}
void Tree_manager::process_2(int *shift, int *bpos, char *pat, int m)
{
    int i, j;
    j = bpos[0];
    for(i=0; i<=m; i++)
    {
        if(shift[i]==0)
            shift[i] = j;
  
        if (i==j)
            j = bpos[j];
    }
}
int Tree_manager::search(char *text, char *pat)
{
    int m = strlen(pat);
    int n = strlen(text);
    int s=0; // 텍스트에 대한 패턴을 이동시키기 위한 변수
  
    int bpos[m+1], shift[m+1];
  
    
    for(int i=0;i<m+1;i++) shift[i]=0;
  
    //전처리 단계
    process_1(shift, bpos, pat, m);
    process_2(shift, bpos, pat, m);
  
    // 문자열 검색 단계
    while(s <= n-m)
    {
  
        int j = m-1;
  
        // 텍스트와 패턴을 오니쪽에서 오른쪽으로 비교
        while(j >= 0 && pat[j] == text[s+j])
            j--;
  
         // 텍스트에서 패턴을 발견한 경우
        if (j<0) {
            // 패턴을 다음 위치로 이동시킴
            return 1;
            s += shift[0];
        }
        else {
            // 패턴과 불일치하는 경우 오프셋만큼 패턴을 이동
            s += shift[j+1];
        }
    }
  return 0;
}
BST_Node* Tree_manager::get_find_node(int findnum, BST_Node* currnode){
        if(currnode->bst_num == findnum){
            return currnode;
        }
        if(currnode->left!=NULL) get_find_node(findnum,currnode->left);
        if(currnode->right!=NULL) get_find_node(findnum,currnode->right);
        if(currnode->left==NULL && currnode->right == NULL) {return NULL;}
}
void Manager::PrintError(Result result) {  //------------Error_print----------
    cout << "===============Error=============" << endl;
    switch (result)
    {
    case Result::Load: //case Result::Load: 해야함?
        cout << 100 << endl;
        break;
    case Result::Add:
        cout << 200 << endl;
        break;
    case Result::Modify:
        cout << 300 << endl;
        break;
    case Result::Move:
        cout<<400<<endl;
        break;
    case Result::Search:
        cout<<600<<endl;
        break;
    }
    cout << "==================================" << endl;
}
void Manager::PrintSuc(Result result){ //ADD도 추가해줄것
    cout<<"=============";
    switch(result){
        case Result::Add:
            cout<<"Add";
            break;
        case Result::Modify:
            cout<<"Modfiy";
            break;
        case Result::Move:
            cout<<"Move";
            break;
        case Result::Select:
            cout<<"Select";
            break;
    }
    cout<<"============="<<endl;
    cout<<"Success"<<endl;
    cout<<"==============================="<<endl;
    return;
}