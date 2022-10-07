#include "main.h"


int main(int argc, char* argv[])
{
    const char* commandFilepath = "command.txt";
    if (argc > 1)
        commandFilepath = argv[1];

    Manager m;
    m.RUN(commandFilepath);

    return 0;
}

void Loaded_LIST::Add_linklist(string name, string dir, string num){
    Loaded_LIST_Node* currNode=img_head;
    Loaded_LIST_Node* newNode = new Loaded_LIST_Node;
    
    newNode->img_name = name;
    newNode->dirname = dir;
    newNode->unique_num = num;

    int pass_num = 0;
    while(1)
    {
        if(currNode->dirname==dir){
            pass_num=1;
            break;
        }
        if(currNode->down ==NULL){
            break;
        }
        currNode=currNode->down;
    }
    if(pass_num==0){
        Loaded_LIST_Node* new_dirnode= new Loaded_LIST_Node;
        new_dirnode->dirname=dir;
        currNode->down = new_dirnode;
        //currNode = currNode->down;
    }
    Loaded_LIST_Node* new_currNode = new Loaded_LIST_Node;
    if (pass_num==0) new_currNode= currNode->down;
    else if(pass_num==1) new_currNode = currNode;
    while(new_currNode->next != NULL){
        new_currNode=new_currNode->next;
    }
    new_currNode->next=newNode;
    return ;
}

void Loaded_LIST::Load_linklist(string name, string dir, string num) {
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
        }
        else if (strcmp(command,"MODIFY")==0){
            cout<<"모디파이왔디"<<endl;
            command=strtok(NULL," ");
            string file_name1 = command;
            command = strtok(NULL,"\"");
            string change_name = command;
            command = strtok(NULL,"\n"); // eeeeeeeeeeeeeeeroooooooooooooorrrrrrrrrrr주의 " 500"일케읽힘
            string change_num = command;

            if(!MODIFY(cmd, file_name1, change_name, change_num, list)){
                PrintError(Modify);
            }
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
        getline(fread, NAME, '.');
        getline(fread,trash1,'\n');
        //int i = stoi(str_NUMBER); //string=>t
        list->Load_linklist(NAME, "img_files", str_NUMBER); //안에 전달할 넣어주기 dir이름 변경해야해ㅠ    
    }
    list->Load_list_print(); //링크드리스트 만든 후 출력
    fread.close();
    count++; //이거!!!!!!!!!!!!!!!!!!!!!!!!!!!111수정 !!!!!!!!!!!11count++에드에서할것
    return Success;
}

Result Manager::ADD(const char* filepath,string dir_n, string csv_n, string path,Loaded_LIST* list) {//path1=>dirname, path2=>filename
    //Loaded_LIST list;
    string NAME, str_NUMBER, trash1;
    cout<<path<<endl;//삭제해줄것
    
    fin2.open(path,ios::in);
    if (!fin2) {
        cout << "해당 경로에 파일이 없음"<<endl;
        //PrintError(Add);
        return Fail;
    }

     while (!fin2.eof()) {
        getline(fin2, str_NUMBER, ',');
        getline(fin2, NAME, '.');
        getline(fin2,trash1,'\n');
        list->Add_linklist(NAME, dir_n , str_NUMBER); //안에 전달할 넣어주기 dir이름 변경해야해ㅠ    
    }
    
    list->Add_list_print(); //링크드리스트 만든 후 출력
    fin2.close();
    return Success;
}
Result Manager::MODIFY(const char* filepath,string dir_n, string n_imgname, string n_num, Loaded_LIST* list){
    if(!list->Modify_list(n_imgname, dir_n, n_num)){
        return Fail;
    }
    list->test_All_print();
    return Success;
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
int Loaded_LIST::Modify_list(string name, string dir, string new_num){
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
        if(currnode->img_name == name) break;
        if(currnode->next ==NULL){return 0;}
        prevnode=currnode;
        currnode=currnode->next;
    }
    Loaded_LIST_Node* newnode = new Loaded_LIST_Node;
    newnode->dirname=dir;
    newnode->unique_num = new_num;
    newnode->img_name = name;
    if(currnode->next==NULL){ //성공 리턴
        prevnode->next=newnode;
        delete currnode;
        return 1;
    }
    if(currnode->next!=NULL){ //성공리턴
        prevnode->next=newnode;
        newnode->next=currnode->next;
        delete currnode;
        return 1;
    }
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


    }
    cout << "==================================" << endl;
    /*
    if(result==Load) {
        cout<<"=====Error===="<<endl;
        cout<<Load<<endl;

    }
    else if(result==Add) return 200;
    else if(result==)*/
}