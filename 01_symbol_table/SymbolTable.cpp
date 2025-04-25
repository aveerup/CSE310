#pragma once
#include <iostream>
#include "SymbolInfo.cpp"
#include "ScopeTable.cpp"
using namespace std;

class SymbolTable{
    private:
        long long num_scopeTable = 0;
        ScopeTable *scopeTables = NULL;
        long long num_buckets = 20;

    public:
        SymbolTable();

        SymbolTable(long long n);

        void Enter_Scope();

        void Exit_Scope();

        bool Insert(SymbolInfo *symbol);

        bool Remove(string &symbol_name);

        SymbolInfo* Look_Up(string &symbol_name);

        void Print_Current();

        void Print_All();
};

SymbolTable::SymbolTable(){
    this->Enter_Scope();
}

SymbolTable::SymbolTable(long long n){
    this->num_buckets = n;
    this->Enter_Scope();
}

void SymbolTable::Enter_Scope(){
    this->num_scopeTable += 1;
    ScopeTable* scopeTable = new ScopeTable(this->num_scopeTable, this->num_buckets);
    
    scopeTable->set_next(this->scopeTables);
    this->scopeTables = scopeTable;

    cout<<"ScopeTable# "<<num_scopeTable<<" created"<<endl;

}

void SymbolTable::Exit_Scope(){
    ScopeTable *temp = this->scopeTables;
    if(temp->get_id() == 1)
        return ;

    cout<<"symbol_table "<<2.7<<endl;

    this->scopeTables = temp->get_next();
    temp->set_next(NULL);

    delete temp;
}

bool SymbolTable::Insert(SymbolInfo *symbol){
    cout<<"symbol_table_insert "<<2.2<<endl;
    return this->scopeTables->Insert(symbol);
}

bool SymbolTable::Remove(string &symbol_name){
    return this->scopeTables->Delete(symbol_name);
}

SymbolInfo* SymbolTable::Look_Up(string &symbol_name){
    ScopeTable* temp = this->scopeTables;
    SymbolInfo* found_symbol = NULL;
    while(temp){
        found_symbol = this->scopeTables->Look_Up(symbol_name);
        if( found_symbol != NULL)
            return found_symbol;
        else 
            temp = temp->get_next();
    }

    return found_symbol;
}

void SymbolTable::Print_Current(){
    this->scopeTables->Print();
}

void SymbolTable::Print_All(){
    ScopeTable *temp = this->scopeTables;
    while(temp){
        temp->Print();
        temp = temp->get_next();
    }
}