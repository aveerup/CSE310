#include "ScopeTable.cpp"
#include "SymbolInfo.cpp"
#include "SymbolTable.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

string& to_upper( string &str ){
    char c;
    for(int i=0; i<str.length(); i++){
        c = str[i];   // str[i] is a character, so can be assigned without problem
        str[i] = toupper(c);
    }

    return str;
}

void split_cmd(string &line, string** &cmd){

    string *word = new string("");
    int word_count = 0;

    for(int i=0; i<line.length(); i++){

        if( *word != "" ){
            if( line[i] == ' ' ){
                word_count += 1;
                cmd[ word_count-1 ] = word;
                // cout<<*word<<endl;
                word = new string("");
            }else{
                *word += line[i];
            }
        }else{
            if( line[i] != ' '){
                *word += line[i];
            }
        }

    }

    if(*word != ""){
        word_count += 1;
        cmd[word_count - 1] = word;
    }else{
        delete word;
    }
}

bool process(string** &cmd, SymbolTable* &symbolTable, ostream *fout){

    if( *cmd[0] == "I" ){
        if( *cmd[2] == "FUNCTION"){

            if( cmd[3] == NULL ){
                cout<<"I : Function type needs to have a return type"<<endl;
                return false;
            }else{

                SymbolInfo* new_symbol = new SymbolInfo(*cmd[1], *cmd[2]);
                SymbolInfo* temp = new_symbol;
                int i = 3;
                while(cmd[i]){

                    SymbolInfo* extra_symbol = new SymbolInfo("", *cmd[i]);
                    temp->set_extra_info(extra_symbol);
                    temp = extra_symbol;
                    i++;

                }
                
                symbolTable->Insert(new_symbol);

            }

        }else if( *cmd[2] == "STRUCT" || *cmd[2] == "UNION" ){
            
            int i = 0;
            while( cmd[i+3] ){
                i++;
            }

            if( i%2 != 0 ){
                cout<<"I : STRUCT or UNION needs to have variable_name and variable_type in pair"<<endl;
                return false;
            }else{

                SymbolInfo *new_symbol = new SymbolInfo(*cmd[1], *cmd[2]);
                SymbolInfo *temp = new_symbol;
                int i = 3;
                while(cmd[i]){
                    SymbolInfo *extra_info = new SymbolInfo(*cmd[i+1], *cmd[i]);
                    temp->set_extra_info(extra_info);
                    temp = extra_info;
                    i += 2;
                }
                symbolTable->Insert(new_symbol);

            }

        }else if( cmd[1] == NULL || cmd[2] == NULL ){

            return false;

        }else{

            SymbolInfo* new_symbol = new SymbolInfo(*cmd[1], *cmd[2]);
            symbolTable->Insert(new_symbol);

        }
    }else if( *cmd[0] == "L" &&  cmd[1] != NULL ){
        
        if(cmd[2] != NULL){
            *fout<<"\t\tNumber of parameters mismatch for the command "<<*cmd[0]<<endl;
            return false;
        }

        symbolTable->Look_Up(*cmd[1]);
    
    }else if( *cmd[0] == "D" && cmd[1] != NULL ){

        if(cmd[2] != NULL){
            *fout<<"\t\tNumber of parameters mismatch for the command "<<*cmd[0]<<endl;
            return false;
        }
      
        symbolTable->Remove(*cmd[1]);
    
    }else if( *cmd[0] == "P" && cmd[1] != NULL){

        if(cmd[2] != NULL){
            *fout<<"\t\tNumber of parameters mismatch for the command "<<*cmd[0]<<endl;
            return false;
        }

        if(*cmd[1] == "C"){

            symbolTable->Print_Current();

        }else if(*cmd[1] == "A"){

            symbolTable->Print_All();

        }else{
            *fout<<"\t\tNot valid option in command "<<*cmd[1]<<endl;
            return false;
        }
    
    }else if( *cmd[0] == "S" ){

        if(cmd[2] != NULL){
            *fout<<"\t\tNumber of parameters mismatch for the command "<<*cmd[0]<<endl;
            return false;
        }

        symbolTable->Enter_Scope();

    }else if( *cmd[0] == "E" ){

        if(cmd[1] != NULL){
            *fout<<"\t\tNumber of parameters mismatch for the command "<<*cmd[0]<<endl;
            return false;
        }

        // cout<<"process "<<2.7<<endl;
        symbolTable->Exit_Scope();
        // cout<<"process "<<2.8<<endl;

    }else{
        cout<<"Not valid command"<<endl;
        return false;
    }

    return true;
}

// need to set hash function from command line
// need to handle case for struct and union
// add couts' to approapriate places to match the sample output

float report_generator(ifstream *fin, ofstream *fout, string hash_name){
    long long num_buckets;
        string line;

        *fin >> num_buckets;
        // cout << "num_buckets " << num_buckets << endl;
        SymbolTable* symbolTable = new SymbolTable(num_buckets, &(*fout), hash_name);
        // cout<<1.2<<endl;

        getline(*fin, line); // to take the newline character that 
                            // remained after taking num_buckets input

        string** cmd = new string*[50];
        for(int i=0; i<50;i++)
            cmd[i] = NULL;
        long long cmd_no = 0; 
        
        while(true){

            for(int i=0; i<50; i++){
                if(cmd[i])
                    delete cmd[i];
                cmd[i] = NULL;
            }

            getline(*fin, line);
            cmd_no += 1;
            *fout<<"Cmd "<<cmd_no<<": "<<line<<endl;

            split_cmd(line, cmd);
            // cout<<1.4<<endl;

            if(cmd[0] && *cmd[0] == "Q"){

                for(int i=0; i<50; i++){
                    if(cmd[i])
                        delete cmd[i];
                }
                delete[] cmd;
                
                float result = symbolTable->get_collision();
                delete symbolTable;

                (*fin).clear();             
                (*fin).seekg(0, ios::beg);  

                return result;

            }else if(cmd[0]){
                process( cmd, symbolTable, &*fout);
            }
                
        }
}

int main(int argc, char* argv[]){
    if(argc <= 4){
        ifstream fin(argv[1]);
        ofstream fout(argv[2]);
        string hash_name;
        if(argc == 4)
            hash_name = argv[3];

        string hash_names[3] = {"SDBM", "BKDR", "RS"};
        // cout<<1.1<<endl;
        ofstream fout_report("report.txt");
        for(int i =0; i<3; i++){
            fout_report<<hash_names[i]<<"     "<<report_generator(&fin, &fout, hash_names[i])<<endl;
        }

        fin.close();
        fout.close();

    }else{
        cout<<"Need to just give the name of input and output file. Can also provide the name of Hashing intended."<<endl;
    }
}