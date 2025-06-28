#pragma once
#include <iostream>
#include "2105112_SymbolInfo.cpp"
#include "2105112_ScopeTable.cpp"
using namespace std;

class SymbolTable{
    private:
        long long num_scopeTable = 0;
        ScopeTable *scopeTables = NULL;
        long long num_buckets = 20;
        ostream *fout = &cout;
        string hash_name = "SDBM";
        float collision = 0;

    public:

        SymbolTable();

        SymbolTable(ostream *fout);

        SymbolTable(long long n);

        SymbolTable(long long n, ostream *fout, string hash_name);

        ~SymbolTable();

        void Enter_Scope();

        void Exit_Scope();

        bool Insert(SymbolInfo *symbol);

        bool Remove(string &symbol_name);

        SymbolInfo* Look_Up(string &symbol_name);

        void Print_Current();

        void Print_All();

        void set_output_stream(ostream *fout);

        float get_collision();
};

SymbolTable::SymbolTable(){
    this->Enter_Scope();
}

SymbolTable::SymbolTable(ostream *fout){
    this->fout = fout;
    this->Enter_Scope();
}


SymbolTable::SymbolTable(long long n){
    this->num_buckets = n;
    this->Enter_Scope();
}

SymbolTable::SymbolTable(long long n, ostream *fout, string hash_name){
    this->num_buckets = n;
    this->fout = fout;
    this->hash_name = hash_name;
    this->Enter_Scope();
}

SymbolTable::~SymbolTable(){

    ScopeTable *temp;
    while(this->scopeTables){

        temp = this->scopeTables;
        this->scopeTables = this->scopeTables->get_next();
        
        delete temp;
    }

}

void SymbolTable::Enter_Scope(){

    this->num_scopeTable += 1;
    ScopeTable* scopeTable = new ScopeTable(this->num_scopeTable, this->num_buckets, hash_name);
    scopeTable->set_output_stream(this->fout);
    
    scopeTable->set_next(this->scopeTables);
    this->scopeTables = scopeTable;

    *fout<<"\t\tScopeTable# "<<num_scopeTable<<" created"<<endl;

}

void SymbolTable::Exit_Scope(){
    ScopeTable *temp = this->scopeTables;
    if(temp->get_id() == 1)
        return ;

    this->scopeTables = temp->get_next();
    temp->set_next(NULL);

    this->collision += temp->get_collision();
    delete temp;
}

bool SymbolTable::Insert(SymbolInfo *symbol){
    symbol->set_output_stream(fout);
    return this->scopeTables->Insert(symbol);
}

bool SymbolTable::Remove(string &symbol_name){
    bool removed = this->scopeTables->Delete(symbol_name);

    if(!removed){
        *fout<<"Not found in the current ScopeTable"<<endl;
    }

    return removed;
}

SymbolInfo* SymbolTable::Look_Up(string &symbol_name){
    ScopeTable* temp = this->scopeTables;
    SymbolInfo* found_symbol = NULL;
    while(temp){
        found_symbol = temp->Look_Up(symbol_name);
        if( found_symbol != NULL)
            return found_symbol; 
            
        temp = temp->get_next();
    }

    if(found_symbol == NULL)
        *fout<<"\t\t'"<<symbol_name<<"' not found in any of the ScopeTables"<<endl;

    return found_symbol;
}

void SymbolTable::Print_Current(){
    
    ScopeTable::tab_space += 2;
    this->scopeTables->Print();
    
    ScopeTable::tab_space = 0;

}

void SymbolTable::Print_All(){
    ScopeTable *temp = this->scopeTables;

    while(temp){
        ScopeTable::tab_space += 2;
        temp->Print();
        temp = temp->get_next();
    }

    ScopeTable::tab_space = 0;

}

void SymbolTable::set_output_stream(ostream *fout){
    this->fout = fout;

}

float SymbolTable::get_collision(){
    ScopeTable *temp = this->scopeTables;
    while(temp){
        this->collision += temp->get_collision();
        temp = temp->get_next();
    }

    return this->collision/this->num_scopeTable;
}