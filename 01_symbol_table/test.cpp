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

    cout<<1.8<<endl;

    string *word = new string("");
    int word_count = 0;

    for(int i=0; i<line.length(); i++){

        if( *word != "" ){
            if( line[i] == ' ' ){
                word_count += 1;
                cmd[ word_count-1 ] = word;
                cout<<*word<<endl;
                word = new string("");
            }else{
                *word += line[i];
                cout<<*word<<' ';
            }
        }else{
            if( line[i] != ' '){
                *word += line[i];
                cout<<*word<<' ';
            }
        }

    }

    word_count += 1;
    cmd[word_count - 1] = word;
}

bool process(string** &cmd, SymbolTable* &symbolTable){

    if( *cmd[0] == "I" ){
        cout<<"process "<<1.9<<endl;
        if( *cmd[2] == "FUNCTION"){

            if( cmd[3] == NULL ){
                cout<<"I : Function type needs to have a return type"<<endl;
                return false;
            }else{
                cout<<"process "<<2.0<<endl;
                SymbolInfo* new_symbol = new SymbolInfo(*cmd[1], *cmd[2]);
                cout<<"process "<<2.1<<endl;
                int i = 3;
                while(cmd[i]){
                    cout<<"process "<<2.3<<endl;
                    SymbolInfo* extra_symbol = new SymbolInfo("", *cmd[i]);
                    cout<<"process "<<2.4<<endl;
                    new_symbol->set_extra_info(extra_symbol);
                    i++;
                }
                cout<<"process "<<2.2<<endl;
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

                SymbolInfo* new_symbol = new SymbolInfo(*cmd[1], *cmd[2]);
                int i = 3;
                while(cmd[i]){
                    SymbolInfo *extra_info = new SymbolInfo(*cmd[i], *cmd[i+1]);
                    new_symbol->set_extra_info(extra_info);
                    i += 2;
                }
                symbolTable->Insert(new_symbol);

            }

        }else if( *cmd[1] == "" || *cmd[2] == "" ){

            return false;

        }else{
            cout<<"process "<<2.0<<endl;
            SymbolInfo* new_symbol = new SymbolInfo(*cmd[1], *cmd[2]);
            cout<<"process "<<2.1<<endl;
            symbolTable->Insert(new_symbol);

        }
    }else if( *cmd[0] == "L" &&  cmd[1] != NULL ){

        symbolTable->Look_Up(*cmd[1]);
    
    }else if( *cmd[0] == "D" && cmd[1] != NULL ){
      
        symbolTable->Remove(*cmd[1]);
    
    }else if( *cmd[0] == "P" && cmd[1] != NULL){
        
        if(*cmd[1] == "C"){

            symbolTable->Print_Current();

        }else if(*cmd[1] == "A"){

            symbolTable->Print_All();

        }else{
            cout<<"Not valid Print option"<<endl;
            return false;
        }
    
    }else if( *cmd[0] == "S" ){

        symbolTable->Enter_Scope();

    }else if( *cmd[0] == "E" ){

        cout<<"process "<<2.7<<endl;
        symbolTable->Exit_Scope();
        cout<<"process "<<2.8<<endl;

    }else{
        cout<<"Not valid command"<<endl;
        return false;
    }

    return true;
}

int main(int argc, char* argv[]){
    if(argc<4){
        ifstream fin(argv[1]);
        ofstream fout(argv[2]);
        cout<<1.1<<endl;

        long long num_buckets;
        string line;

        fin >> num_buckets;
        cout << "num_buckets " << num_buckets << endl;
        SymbolTable* symbolTable = new SymbolTable(num_buckets);
        cout<<1.2<<endl;

        getline(fin, line); // to take the newline character that 
                            // remained after taking num_buckets input

        string** cmd = new string*[50];
        
        while(true){
            for(int i=0; i<50; i++){
                cmd[i] = NULL;
            }
            cout<<1.3<<endl;

            getline(fin, line);
            cout<<line<<endl;

            split_cmd(line, cmd);
            cout<<1.4<<endl;

            if(cmd[0] == NULL || *cmd[0] == "Q"){
                cout<<1.7<<endl;
                return 0;
            }else{
                cout<<1.5<<endl;
                process( cmd, symbolTable );
                cout<<1.6<<endl;
            }
                
        }

    }else{
        cout<<"Need to just give the name of input and output file. Can also provide the name of Hashing intended."<<endl;
    }
}

// need to set hash function from command line
// need to handle case for struct and union
// add couts' to approapriate places to match the sample output