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

void Manager::RUN(const char* filepath)
{
    // fout.open(RESULT_LOG_PATH); 
     //ferr.open(ERROR_LOG_PATH); //에러코드 파일 열라고?
    fin.open(filepath);
    char cmd[50] = "";

    while (!fin.eof()) {
        fin.getline(cmd, 50);
        char* command = strtok(cmd, " ");
        if (command == NULL) { cout << "No command"; return; }

        if (strcmp(command, "LOAD") == 0) {
            if (!LOAD(cmd)) { //일단 정렬하고 비교
                PrintError(Load);
            }
        }
        else if (strcmp(command, "ADD") == 0) { //경로글자합쳐서 함수로 보내주기
            char* tmp = strtok(NULL, "");
            char* tmp1 = strtok(tmp, " ");
            char* tmp2 = strtok(NULL, "\n");
            cout<<tmp1<<"템프사이의"<<tmp2<<endl; //삭제
            //char* path_add = strcat(tmp1, tmp2);
            if (!ADD(tmp1, tmp2)) {
                PrintError(Add);
            }
        }

    }
    // TODO: implement
}
Result Manager::LOAD(const char* filepath) { //Loaded List class 불러오자 ///구현 안 끄남 loadelist 먼저 만들거임
    Loaded_LIST list;
    string NAME = "0";
    string str_NUMBER;
    string trash1;
    fstream file;
    int count = 0;
    //file.open("E:\\filesnumbers.csv", ios::in); //ios::in=>파일을 읽겠다는 뜻
    file.open("./img_files/filesnumbers.csv", ios::in);
    if (file.fail()) {
        cout << "해당 경로에 파일이 없음";
        PrintError(Load);
        return Load;
    }
    while (!file.eof()) {
        getline(file, str_NUMBER, ',');
        getline(file, NAME, '.');
        getline(file,trash1,'\n');
        //int i = stoi(str_NUMBER); //string=>int
        list.Load_linklist(NAME, "img_files", str_NUMBER); //안에 전달할 넣어주기 dir이름 변경해야해ㅠ    
    }
    list.Load_list_print(); //링크드리스트 만든 후 출력
    file.close();
    count++; //이거!!!!!!!!!!!!!!!!!!!!!!!!!!!111수정 !!!!!!!!!!!11count++에드에서할것
    return Success;
}

Result Manager::ADD(char* path1, char*path2) {
    string dir_foradd;
    char plus[50] = "./";
    char* csv_path = strcat(plus, path); //csv경로

    return Success;
}

void Loaded_LIST::Load_linklist(string name, string dir, string num) {
    Loaded_LIST_Node* newNode = new Loaded_LIST_Node;
    newNode->img_name = name;
    newNode->dirname = dir;
    newNode->unique_num = num;
    if (img_head == NULL) {
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
    cout << "================================" << endl;
    return;
}
void Manager::PrintError(Result result) {  //------------Error_print----------
    cout << "==============Error============" << endl;
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
