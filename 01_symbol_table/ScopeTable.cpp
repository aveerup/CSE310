#pragma once
#include <iostream>
#include "SymbolInfo.cpp"
#include "HashFunctions.cpp"
using namespace std;

class ScopeTable{
    private:
        long long id;
        long long num_buckets;
        unsigned int (*hash_function)(string str, unsigned int num_buckets) = Hash_function;
        SymbolInfo** symbolInfos;
        ScopeTable *next;

    public:
        ScopeTable(long long id);

        ScopeTable(long long id, long long n);

        ~ScopeTable();

        long long get_id();

        void set_next(ScopeTable *scopeTable);

        ScopeTable* get_next();

        bool Insert(SymbolInfo *symbol);
        
        SymbolInfo* Look_Up(string &symbol_name);
        
        bool Delete(string &symbol_name);
        
        void Print();

};

ScopeTable::ScopeTable(long long id){
    this->id = id;
    this->num_buckets = 20;
    this->symbolInfos = new SymbolInfo*[num_buckets];
    for(int i = 0;i< num_buckets; i++){
        this->symbolInfos[i] = NULL;
    }
}

ScopeTable::ScopeTable(long long id, long long n){
    this->id = id;
    this->num_buckets = n;
    this->symbolInfos = new SymbolInfo*[num_buckets];
    for(int i = 0;i< num_buckets; i++){
        this->symbolInfos[i] = NULL;
    }
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
    cout<<"scope_table_insert "<<2.4<<endl;
    bool exists = this->Look_Up(variable_name);
    cout<<"scope_table_insert "<<2.3<<endl;
    if(exists)
        return false;
    else{
        
        long long hash_value = this->hash_function(symbol->get_variable_name(), this->num_buckets);
        
        symbol->set_symbolInfo(this->symbolInfos[hash_value]);
        this->symbolInfos[hash_value] = symbol;

        return true;
    }
}

SymbolInfo* ScopeTable::Look_Up(string &symbol_name){
    long long hash_value = this->hash_function(symbol_name, this->num_buckets);
    cout<<"scope_table_look_up hash_value"<<hash_value<<endl;

    SymbolInfo *temp = this->symbolInfos[hash_value];
    while(temp){
        if(temp->get_variable_name() == symbol_name ){
            return temp;
        }
        temp = temp->get_next();
    }

    return NULL;
}

bool ScopeTable::Delete(string &symbol_name){
    long long hash_value = this->hash_function(symbol_name, this->num_buckets);
    
    SymbolInfo *temp = this->symbolInfos[hash_value];
    SymbolInfo *parent;
    while(temp){
        if(temp->get_variable_name() == symbol_name ){
            parent->set_symbolInfo(temp->get_next());
            delete temp;
            return true;
        }
        parent = temp;
        temp = temp->get_next();
    } 
    
    return false;
}

void ScopeTable::Print(){
    for(int i=0; i<this->num_buckets; i++){
        cout<<i+1<<"-->";
        SymbolInfo *temp = this->symbolInfos[i];

        while(temp){
            temp->Print();
            temp = temp->get_next();
        }
        cout<<endl;
    }
}