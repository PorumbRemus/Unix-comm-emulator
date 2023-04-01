#include <iostream>
#include<cstdio>
#include<string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include<stdio.h>
#include <sys/stat.h>
#include<pwd.h>
#include <grp.h>
#include<ctime>
#include<dirent.h>
#include <vector>
#include<fstream>
#include<deque>
#include <csignal>
#include <fcntl.h>

using namespace std;

//the command parser
void parse_by_space(vector<string> &param, char *pcom)
{
    char * pch,*array[1024];
    int index=0;
    param.clear();
    pch = strtok(pcom, " ");
    while (pch != NULL){
        array[index++] = strdup(pch);
        pch = strtok(NULL, " ");
    }
    for(int i=0;i<index;i++)
    {
        param.push_back(array[i]);
    }
}
void read_c(char *command, vector<string> &pipeparam) {
    char *l;
    char *pch,*pipear[1024], *pipech;
    int index = 0,pipeindex=0;
    cout<<endl;
    l = readline("λ ");
    string line(l);
    if (line!=""){
        add_history(l);
    }
    pipech = strstr(l, " | ");
    while (pipech != NULL) {
        *pipech = '\0';
        pipear[pipeindex++] = strdup(l);
        l = pipech + strlen(" | ");
        pipech = strstr(l, " | ");
    }
    pipear[pipeindex++] = strdup(l);


    for(int i=0;i<pipeindex;i++)
    {
        strcat(command, pipear[i]);
        if(i!=pipeindex-1)
            strcat(command," ");
        pipeparam.push_back(pipear[i]);
    }


    cout<<endl;

}

//tac command without file

void tacno()
{
    char l[256];
    deque<string> reverse;
    clearerr(stdin);
    while(!cin.fail())
    {
        cin.getline(l,sizeof(l));
        reverse.push_front(l);
    }
    cin.clear();
    for(string l: reverse)
    {
        cout<<l<<endl;
    }

}

//tac command with file

void tacyes(const char *d){
    FILE* f;
    deque<string> reverse;
    f=fopen(d,"r");
    if(f==NULL)
    {
        cout<<"Could not open file"<<endl;
        return;
    }
    char l[256];
    string s;
    while(fgets(l,sizeof(l),f)!=NULL) {
        reverse.push_front(l);
    }
    fclose(f);
    for(string l: reverse){
        cout<<l;
    }
}

// tac -b command without file
void tacno_b()
{
    char l[256];
    deque<string> reverse;
    clearerr(stdin);
    while(!cin.fail())
    {
        cin.getline(l,sizeof(l));
        reverse.push_front(l);
    }
    cin.clear();
    int i=0;
    for(string l: reverse)
        i++;
    int j=0;
    for(string l: reverse)
    {
        j++;
        if(j<i)
        {
            cout<<endl<<l;
        }
        else
            cout<<l;
    }

}

//tac -b command with file
void tacyes_b(const char *d){
    FILE* f;
    deque<string> reverse;
    f=fopen(d,"r");
    if(f==NULL)
    {
        cout<<"Could not open file"<<endl;
        return;
    }
    char l[256];
    string s;
    int i=0;
    while(fgets(l,sizeof(l),f)!=NULL) {
        reverse.push_front(l);
        i++;
    }
    fclose(f);
    int j=0;
    for(string l: reverse)
    {
        j++;
        cout<<l;
    }


}

// tac with s flag without file
void tacno_s(string c)
{
    char l[256];
    deque<string> reverse;
    int ok=0, j,b=0;
    clearerr(stdin);
    while(!cin.fail())
    {
        cin.getline(l,sizeof(l));
//        for(int i=0;i<strlen(l);i++) {
//            if(l[i]==c[0])
//            {
//                int j=i;
//            }
//            while(l[j]==c[b++])
//            {
//                if(b==c.length())
//                    ok=1;
//            }
//        }
        reverse.push_front(l);
    }
    cout<<ok<<endl;
    cin.clear();
    for(string l: reverse)
    {
        cout<<l<<endl;
    }

}

//tac  with s flagwith file

void tacyes_s(const char *d,string c){
    FILE* f;
    deque<string> reverse;
    f=fopen(d,"r");
    if(f==NULL)
    {
        cout<<"Could not open file"<<endl;
        return;
    }
    char l[256];
    string s;
    while(fgets(l,sizeof(l),f)!=NULL) {
        reverse.push_front(l);
    }
    fclose(f);
    for(string l: reverse){
        cout<<l;
    }
}

//dirname command
void dirname(string s)
{
    int i, c = 0, ok = 0;

    while (s.back() == '/') {
        s.pop_back();
    }
    if(s.empty())
        cout<<"/"<<endl;
    else {
        for (i = 0; i <= s.size(); i++)
            if (s[i] == '/') {
                c++;
            }
        if (c == 0 || (c == 1 && s.back() == '/')) {
            cout << "."<<endl;
        } else
            ok = 1;
    }
    if(ok==1) {
        while (s.back() == '/') {
            s.pop_back();
        }
        size_t lastSlashPos = s.find_last_of('/');
        string sub = s.substr(0, lastSlashPos);
        while (sub.back() == '/') {
            sub.pop_back();
        }
        cout << sub<<endl;
    }
}

//printing layout for ls -l
const char *mode_string(mode_t mode) {
    static char str[11];
    str[0] = (S_ISDIR(mode)) ? 'd' : '-';
    str[1] = (mode & S_IRUSR) ? 'r' : '-';
    str[2] = (mode & S_IWUSR) ? 'w' : '-';
    str[3] = (mode & S_IXUSR) ? 'x' : '-';
    str[4] = (mode & S_IRGRP) ? 'r' : '-';
    str[5] = (mode & S_IWGRP) ? 'w' : '-';
    str[6] = (mode & S_IXGRP) ? 'x' : '-';
    str[7] = (mode & S_IROTH) ? 'r' : '-';
    str[8] = (mode & S_IWOTH) ? 'w' : '-';
    str[9] = (mode & S_IXOTH) ? 'x' : '-';
    str[10] = '\0';
    return str;
}

//executable check for ls command
bool is_executable(const char* path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return (path_stat.st_mode & S_IXUSR) != 0;
}

//flagless ls command
void ls(const char *d){
    DIR *directory=opendir(d);
    struct dirent *entry;
    if(directory==NULL)
    {
        cout<<"Could not open directory"<<endl;
        return;
    }
    while((entry=readdir(directory))!=NULL)
    {
        if(entry->d_name[0]!='.') {
            if (entry->d_type == DT_LNK) {
                cout << entry->d_name << endl;//magenta for symboilic links
            } else if (entry->d_type == DT_DIR) {
                cout << entry->d_name << endl;//blue for directories
            } else if (entry->d_type == DT_FIFO) {
                cout << entry->d_name << endl; //yelow for fifo
            } else if (entry->d_type == DT_SOCK) {
                cout << entry->d_name << endl; //cyan for sockets
            } else if (is_executable(entry->d_name))
            {
                cout << entry->d_name <<endl; //white for exe
            } else if (entry->d_type == DT_REG) {
                cout << entry->d_name << endl;//green for files
            }
        }
    }

    if(closedir(directory)==-1)
    {
        cout<<"Could not close directory.\n";
        exit(EXIT_FAILURE);
    }
}

//ls -a flag command

void lsa(const char *d)
{
    DIR *directory=opendir(d);
    struct dirent *entry;
    if(directory==NULL)
    {
        cout<<"Could not open directory"<<endl;
        return;
    }
    while((entry=readdir(directory))!=NULL)
    {
        if (entry->d_type == DT_LNK) {
            cout << entry->d_name << endl;//magenta for symboilic links
        } else if (entry->d_type == DT_DIR) {
            cout << entry->d_name << endl;//blue for directories
        } else if(entry->d_type==DT_FIFO){
            cout << entry->d_name << endl;//yellow for fifo
        } else if(entry->d_type==DT_SOCK){
            cout << entry->d_name << endl;//cyan for sockets
        } else if(is_executable(entry->d_name))
            cout << entry->d_name << endl;//white for exe
        else if (entry->d_type == DT_REG) {
            cout << entry->d_name << endl;//green for files
        }
    }
    if(closedir(directory)==-1)
    {
        cout<<"Could not close directory"<<endl;
        return;
    }
}

// ls -s flag command

void lss(const char *d)
{
    int i=0;
    DIR *directory=opendir(d);
    struct stat info;
    struct dirent *entry;
    int size;
    if(directory==NULL)
    {
        cout<<"Could not open directory"<<endl;
        return;
    }
    while((entry=readdir(directory))!=NULL)
    {
        if(entry->d_name[0]!='.')
            if(stat(entry->d_name,&info)==0) {
                if (entry->d_type == DT_LNK) {
                    size=info.st_blocks/2;
                    i=i+size;
                    cout << size << " " << entry->d_name << endl;//magenta for symboilic links
                } else if (entry->d_type == DT_DIR) {
                    size=info.st_blocks/2;
                    i=i+size;
                    cout << size << " " << entry->d_name << endl;//blue for directories
                } else if (entry->d_type == DT_FIFO) {
                    size=info.st_blocks/2;
                    i=i+size;
                    cout << size << " " << entry->d_name << endl;//yellow for fifo
                }else if (entry->d_type == DT_SOCK) {
                    size=info.st_blocks/2;
                    i=i+size;
                    cout << size << " " << entry->d_name << endl;//cyan for sockets
                }else if (is_executable(entry->d_name)) {
                    size=info.st_blocks/2;
                    i=i+size;
                    cout << size << " " << entry->d_name << endl;//white for exe
                }else if (entry->d_type == DT_REG) {
                    size=info.st_blocks/2;
                    i=i+size;
                    cout <<size<< " " << entry->d_name << endl;//green for files
                }
            }
            else{
                cout<<"Error getting file info"<<endl;
                return;
            }

    }
    cout<<"Total: "<<i;
    if(closedir(directory)==-1)
    {
        cout<<"Could not close directory"<<endl;
        return;
    }
}

// ls -F flag command

void lsf(const char* d){
    DIR *directory=opendir(d);
    struct dirent *entry;
    struct stat info;
    stat(d,&info);
    if(directory==NULL)
    {
        cout<<"Could not open directory"<<endl;
        return;
    }
    while((entry=readdir(directory))!=NULL)
    {
        if(entry->d_name[0]!='.') {

            if (entry->d_type == DT_LNK) {
                cout << entry->d_name << "@" << endl;//magenta for symboilic links
            }
            else if (entry->d_type == DT_DIR) {
                cout << entry->d_name << "/" << endl;//blue for directories
            }
            else if(entry->d_type==DT_FIFO) {
                cout << entry->d_name << "|" << endl;//yellow for fifo
            }
            else if (entry->d_type == DT_SOCK){
                cout << entry->d_name << "=" <<endl;//cyan for sockets
            }
            else if(is_executable(entry->d_name)!=0)
            {
                cout << entry->d_name << "*" <<endl;//white for exe
            }
            else if (entry->d_type == DT_REG) {
                cout << entry->d_name << endl;//green for files
            }
        }
    }
    if(closedir(directory)==-1)
    {
        cout<<"Could not close directory"<<endl;
        return;
    }
}

//ls -l flag command

void lsl(const char *d)
{
    int i=0;
    DIR *directory=opendir(d);
    string a;
    cout<<a<<endl;
    struct stat info;
    struct dirent *entry;
    struct passwd *pwd;
    struct group *grp;
    struct tm* time_info;
    int size;
    if(directory==NULL)
    {
        cout<<"Could not open directory"<<endl;
        return;
    }
    while((entry=readdir(directory))!=NULL)
    {
        if(entry->d_name[0]!='.')
            if(stat(entry->d_name,&info)==0) {
                time_t last=info.st_mtime;
                time_info= gmtime(&last);
                pwd=getpwuid(info.st_uid);
                grp=getgrgid(info.st_uid);
                switch (time_info->tm_mon){
                    case 0:
                        a="January ";
                        break;
                    case 1:
                        a="February ";
                    case 2:
                        a="March ";
                        break;
                    case 3:
                        a="April ";
                    case 4:
                        a="May ";
                        break;
                    case 5:
                        a="June ";
                    case 6:
                        a="July ";
                        break;
                    case 7:
                        a="August ";
                        break;
                    case 8:
                        a="September ";
                        break;
                    case 9:
                        a="October ";
                        break;
                    case 10:
                        a="November ";
                        break;
                    case 11:
                        a="December ";
                        break;
                }
                if (entry->d_type == DT_LNK) {
                    size=info.st_blocks/2;
                    i=i+size;
                    cout <<mode_string(info.st_mode)<<" "<<info.st_nlink<<" "<<pwd->pw_name<<" "<<grp->gr_name<<" "<<info.st_size<< " " <<a<<" "<<time_info->tm_mday<<" "<<time_info->tm_hour+2<<":"<<time_info->tm_min<<" "<< entry->d_name << endl;//magenta for symboilic links
                }
                else if (entry->d_type == DT_DIR) {
                    size=info.st_blocks/2;
                    i=i+size;
                    cout <<mode_string(info.st_mode)<<" "<<info.st_nlink<<" "<< pwd->pw_name<<" "<<grp->gr_name<<" "<<info.st_size << " " <<a<<" "<<time_info->tm_mday<<" "<<time_info->tm_hour+2<<":"<<time_info->tm_min<<" "<< entry->d_name << endl;//blue for directories
                }else if (entry->d_type == DT_FIFO) {
                    size=info.st_blocks/2;
                    i=i+size;
                    cout <<mode_string(info.st_mode)<<" "<<info.st_nlink<<" "<< pwd->pw_name<<" "<<grp->gr_name<<" "<<info.st_size << " " <<a<<" "<<time_info->tm_mday<<" "<<time_info->tm_hour+2<<":"<<time_info->tm_min<<" " << entry->d_name << endl;//yellow for fifo
                }
                else if (entry->d_type == DT_SOCK) {
                    size=info.st_blocks/2;
                    i=i+size;
                    cout <<mode_string(info.st_mode)<<" "<<info.st_nlink<<" "<< pwd->pw_name<<" "<<grp->gr_name<<" "<<info.st_size << " " <<a<<" "<<time_info->tm_mday<<" "<<time_info->tm_hour+2<<":"<<time_info->tm_min<<" " << entry->d_name << endl;//cyan for sockets
                }
                else if (is_executable(entry->d_name)) {
                    size=info.st_blocks/2;
                    i=i+size;
                    cout <<mode_string(info.st_mode)<<" "<<info.st_nlink<<" "<< pwd->pw_name<<" "<<grp->gr_name<<" "<<info.st_size << " " <<a<<" "<<time_info->tm_mday<<" "<<time_info->tm_hour+2<<":"<<time_info->tm_min<<" " << entry->d_name << endl;//white for exe
                }
                else if (entry->d_type == DT_REG) {
                    size=info.st_blocks/2;
                    i=i+size;
                    cout <<mode_string(info.st_mode)<<" "<<info.st_nlink<<" "<< pwd->pw_name<<" "<<grp->gr_name<<" "<<info.st_size<< " " <<a<<" "<<time_info->tm_mday<<" "<<time_info->tm_hour+2<<":"<<time_info->tm_min<<" " << entry->d_name << endl;//green for files
                }
            }
            else{
                cout<<"Error getting file info"<<endl;
                return;
            }

    }
    cout<<"Total: "<<i;
    if(closedir(directory)==-1)
    {
        cout<<"Could not close directory"<<endl;
        return;
    }
}


void execTermComWithPopen(char* command)
{
    FILE* com= popen(command,"r");
    char output[1024];
    while(fgets(output,1024,com)!=nullptr)
    {
        cout<<output;
    }
    int end_code=pclose(com);
    if(end_code==0)
        cout<<"Command was successful ended with code "<<end_code<<endl;
    else
        cout<<"Error in executing command ended with code "<<end_code<<endl;

}
void check_command()
{
    string file;
    int redirect=0,append=0;
    char *com;
    vector<string> param;
    vector<string> pipeparam;
    com=(char*) malloc((100)* sizeof(char));

    while(true) {
        int back = dup(STDOUT_FILENO);
        memset(com, 0, 100);
        param.clear();
        pipeparam.clear();
        read_c(com, pipeparam);
        string c = com;
        for (int i = 0; i < pipeparam.size(); i++)
        {
            parse_by_space(param, (char *)pipeparam[i].c_str());
            for (int i = 0; i < param.size(); i++) {
                if (param[i] == ">>" && append != 1) {
                    append = 1;
                    file = param[i + 1];
                    cout << file << endl;
                    param.erase(param.begin() + i, param.end());
                } else if (param[i] == ">" && redirect != 1) {
                    redirect = 1;
                    file = param[i + 1];
                    cout << file << endl;
                    param.erase(param.begin() + i, param.end());
                }
            }

            if (c == "exit") {
                cout << "Closing Terminal.." << endl;
                break;
            } else if (c.find("tac -s") == 0) {
                if (append == 1) {
                    int file2 = open(file.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0777);
                    dup2(file2, STDOUT_FILENO);
                    close(file2);
                    append = 0;
                }

                if (redirect == 1) {
                    int file1 = open(file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0777);
                    dup2(file1, STDOUT_FILENO);
                    close(file1);
                    redirect = 0;
                }
                if (param.size() < 3)
                    cout << "not enough parameters" << endl;
                if (param.size() == 3)
                    tacno_s(param[3]);
                else {
                    for (int i = 3; i < param.size(); i++) {
                        cout << endl << param[i] << ".." << endl;
                        tacyes_s(param[i].c_str(), param[3]);
                    }
                }
            } else if (c.find("tac -b") == 0) {
                if (append == 1) {
                    int file2 = open(file.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0777);
                    dup2(file2, STDOUT_FILENO);
                    close(file2);
                    append = 0;
                }

                if (redirect == 1) {
                    int file1 = open(file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0777);
                    dup2(file1, STDOUT_FILENO);
                    close(file1);
                    redirect = 0;
                }
                if (param.size() == 2)
                    tacno_b();
                else {
                    for (int i = 2; i < param.size(); i++) {
                        cout << endl << param[i] << ".." << endl;
                        tacyes_b(param[i].c_str());
                    }
                }
            } else if (c.find("tac") == 0) {
                if (append == 1) {
                    int file2 = open(file.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0777);
                    dup2(file2, STDOUT_FILENO);
                    close(file2);
                    append = 0;
                }

                if (redirect == 1) {
                    int file1 = open(file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0777);
                    dup2(file1, STDOUT_FILENO);
                    close(file1);
                    redirect = 0;
                }
                if (param.size() == 1)
                    tacno();
                else {
                    for (int i = 1; i < param.size(); i++) {
                        cout << endl << param[i] << ".." << endl;
                        tacyes(param[i].c_str());
                    }
                }
            } else if (c.find("ls -a") == 0) {
                if (append == 1) {
                    int file2 = open(file.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0777);
                    dup2(file2, STDOUT_FILENO);
                    close(file2);
                    append = 0;
                }

                if (redirect == 1) {
                    int file1 = open(file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0777);
                    dup2(file1, STDOUT_FILENO);
                    close(file1);
                    redirect = 0;
                }
                if (param.size() == 2)
                    lsa(".");
                else {
                    for (int i = 2; i < param.size(); i++) {
                        cout << endl << param[i] << ".." << endl;
                        lsa(param[i].c_str());
                    }
                }
            } else if (c.find("ls -s") == 0) {
                if (append == 1) {
                    int file2 = open(file.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0777);
                    dup2(file2, STDOUT_FILENO);
                    close(file2);
                    append = 0;
                }

                if (redirect == 1) {
                    int file1 = open(file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0777);
                    dup2(file1, STDOUT_FILENO);
                    close(file1);
                    redirect = 0;
                }
                if (param.size() == 2)
                    lss(".");
                else {
                    for (int i = 2; i < param.size(); i++) {
                        cout << endl << param[i] << ".." << endl;
                        lss(param[i].c_str());
                    }
                }
            } else if (c.find("ls -F") == 0) {
                if (append == 1) {
                    int file2 = open(file.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0777);
                    dup2(file2, STDOUT_FILENO);
                    close(file2);
                    append = 0;
                }

                if (redirect == 1) {
                    int file1 = open(file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0777);
                    dup2(file1, STDOUT_FILENO);
                    close(file1);
                    redirect = 0;
                }
                if (param.size() == 2)
                    lsf(".");
                else {
                    for (int i = 2; i < param.size(); i++) {
                        cout << endl << param[i] << ".." << endl;
                        lsf(param[i].c_str());
                    }
                }
            } else if (c.find("ls -l") == 0) {
                if (append == 1) {
                    int file2 = open(file.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0777);
                    dup2(file2, STDOUT_FILENO);
                    close(file2);
                    append = 0;
                }

                if (redirect == 1) {
                    int file1 = open(file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0777);
                    dup2(file1, STDOUT_FILENO);
                    close(file1);
                    redirect = 0;
                }
                if (param.size() == 2)
                    lsl(".");
                else {
                    for (int i = 2; i < param.size(); i++) {
                        cout << endl << param[i] << ".." << endl;
                        lsl(param[i].c_str());
                    }
                }
            } else if (c.find("ls") == 0) {
                if (append == 1) {
                    int file2 = open(file.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0777);
                    dup2(file2, STDOUT_FILENO);
                    close(file2);
                    append = 0;
                }

                if (redirect == 1) {
                    int file1 = open(file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0777);
                    dup2(file1, STDOUT_FILENO);
                    close(file1);
                    redirect = 0;
                }


                if (param.size() == 1)
                    ls(".");
                else {
                    for (int i = 1; i < param.size(); i++) {
                        cout << endl << param[i] << ".." << endl;
                        ls(param[i].c_str());
                    }

                }
            } else if (c.find("dirname") == 0) {
                if (append == 1) {
                    int file2 = open(file.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0777);
                    dup2(file2, STDOUT_FILENO);
                    close(file2);
                    append = 0;
                }

                if (redirect == 1) {
                    int file1 = open(file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0777);
                    dup2(file1, STDOUT_FILENO);
                    close(file1);
                    redirect = 0;
                }
                for (int i = 1; i < param.size(); i++) {
                    cout << endl;
                    dirname(param[i]);
                }
            } else
                execTermComWithPopen(com);
            dup2(back, STDOUT_FILENO);
            close(back);
        }
    }

}
int main(int argc, char **argv) {

    check_command();
    return 0;
}