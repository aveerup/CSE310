#pragma once
#include <iostream>
#include "2105112_SymbolInfo.cpp"
#include "2105112_HashFunctions.cpp"
using namespace std;

class ScopeTable{
    private:
        long long id;
        long long num_buckets;
        unsigned int (*hash_function)(string str, unsigned int num_buckets, string hash_name) = Hash_function;
        SymbolInfo** symbolInfos;
        ScopeTable *next;
        ostream *fout = &cout;
        string hash_name = "SDBM";
        float collision = 0;

    public:
        static int tab_space ;

        ScopeTable(long long id, string hash_name);

        ScopeTable(long long id, long long n, string hash_name);

        ~ScopeTable();

        long long get_id();

        void set_next(ScopeTable *scopeTable);

        ScopeTable* get_next();

        bool Insert(SymbolInfo *symbol);
        
        SymbolInfo* Look_Up(string &symbol_name);
        
        bool Delete(string &symbol_name);
        
        void Print();

        void set_output_stream(ostream *fout);

        float get_collision();

};

int ScopeTable::tab_space = 0;

ScopeTable::ScopeTable(long long id, string hash_name){
    this->id = id;
    this->num_buckets = 20;
    this->symbolInfos = new SymbolInfo*[num_buckets];
    for(int i = 0;i< num_buckets; i++){
        this->symbolInfos[i] = NULL;
    }
    this->hash_name = hash_name;
}

ScopeTable::ScopeTable(long long id, long long n, string hash_name){
    this->id = id;
    this->num_buckets = n;
    this->symbolInfos = new SymbolInfo*[num_buckets];
    for(int i = 0;i< num_buckets; i++){
        this->symbolInfos[i] = NULL;
    }
    this->hash_name = hash_name;
}

ScopeTable::~ScopeTable(){
    for(int i=0; i<this->num_buckets; i++){
        while(symbolInfos[i]){
            SymbolInfo *temp = symbolInfos[i];
            symbolInfos[i] = symbolInfos[i]->get_next();
            temp->set_symbolInfo(NULL);
            
            delete temp;
        }
    }

    delete[] symbolInfos;
    *fout<<"\t\tScopeTable# "<<this->id<<" removed"<<endl;
    cout<<"\t\tScopeTable# "<<this->id<<" removed"<<endl;

}

long long ScopeTable::get_id(){
    return this->id;
}

void ScopeTable::set_next(ScopeTable *scopeTable){
    this->next = scopeTable;
}

ScopeTable* ScopeTable::get_next(){
    return this->next;
}

bool ScopeTable::Insert(SymbolInfo *symbol){
    string variable_name = symbol->get_variable_name();
    // cout<<"scope_table_insert "<<2.4<<endl;
    SymbolInfo* exists = this->Look_Up(variable_name);
    // cout<<"scope_table_insert "<<2.3<<endl;

    if(exists == NULL){
        
        long long hash_value = this->hash_function(symbol->get_variable_name(), this->num_buckets, this->hash_name);
        // cout<<"ScopeTable_Insert hash_value "<<hash_value<<endl;
        
        SymbolInfo *temp = this->symbolInfos[hash_value];
        int list_symbol_no = 0;
        if(temp){
            this->collision += 1.0/this->num_buckets;
            list_symbol_no += 1;
            // cout<<"scope_table_insert "<<2.6<<endl;
            while(temp->get_next()){
                list_symbol_no += 1;
                // cout<<"scope_table_insert "<<2.5<<endl;
                temp = temp->get_next();
            }
            temp->set_symbolInfo(symbol);
        }else{
            this->symbolInfos[hash_value] = symbol;
        }
        *fout<<"\t\tInserted in ScopeTable# "<<this->id<<" at position "<<hash_value+1<<","<<list_symbol_no+1<<endl;

        return true;
    }

    delete symbol;
    // cout<<"scope_table_insert "<<2.7<<endl;
    return false;
}

SymbolInfo* ScopeTable::Look_Up(string &symbol_name){
    long long hash_value = this->hash_function(symbol_name, this->num_buckets, this->hash_name);

    SymbolInfo *temp = this->symbolInfos[hash_value];
    int list_symbol_pos = 0;
    while(temp){

        list_symbol_pos += 1;
        if(temp->get_variable_name() == symbol_name ){
            *fout<<"\t\t'"<<symbol_name<<"' "<<"found in ScopeTable# "<<this->id<<" at position "<<hash_value + 1<<", "<< list_symbol_pos<<endl;
            return temp;
        }
        temp = temp->get_next();

    }

    // cout<<"scope_table_look_up "<<2.8<<endl;
    return NULL;
}

bool ScopeTable::Delete(string &symbol_name){
    long long hash_value = this->hash_function(symbol_name, this->num_buckets, this->hash_name);
    
    SymbolInfo *temp = this->symbolInfos[hash_value];
    SymbolInfo *parent = NULL;
    int list_symbol_pos = 0;
    while(temp){
        list_symbol_pos += 1;
        if(temp->get_variable_name() == symbol_name ){

            if(parent != NULL) 
                parent->set_symbolInfo(temp->get_next());
            else{
                this->symbolInfos[hash_value] = temp->get_next();
            }
            delete temp;

            *fout<<"\t\tDeleted "<<symbol_name<<" from ScopeTable# "<<this->id<<" at position "<<hash_value + 1<<", "<<list_symbol_pos<<endl;

            return true;
        }
        parent = temp;
        temp = temp->get_next();
    } 
    
    *fout<<"\t\tNot found in current ScopeTable"<<endl;

    return false;
}

void ScopeTable::Print(){
    
    for(int j=0; j<ScopeTable::tab_space; j++){
        *fout<<"\t";
    }

    *fout<<"ScopeTable# "<<this->id<<endl;

    for(int i=0; i<this->num_buckets; i++){
    
        for(int j=0; j<ScopeTable::tab_space; j++){
            *fout<<"\t";
        }

        *fout<<i+1<<"--> ";
        SymbolInfo *temp = this->symbolInfos[i];

        while(temp){
            temp->Print();
            temp = temp->get_next();
        }
        *fout<<endl;
    }

}

void ScopeTable::set_output_stream(ostream *fout){
    this->fout = fout;
}

float ScopeTable::get_collision(){
    return this->collision;
}