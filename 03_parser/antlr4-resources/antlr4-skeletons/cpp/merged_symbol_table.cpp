#pragma once;
#include <iostream>
#include <string>
using namespace std;

inline unsigned int SDBMHash ( string str , unsigned int num_buckets ) {
	unsigned int hash = 0;
	unsigned int len = str . length () ;

	for ( unsigned int i = 0; i < len ; i ++)
	{
		hash = (( str [ i ]) + ( hash << 6) + ( hash << 16) - hash )  ;
	}

		return hash % num_buckets;
}

inline unsigned int RSHash(const string &str, unsigned int bucketSize) {
    unsigned int b = 378551;
    unsigned long a = 63689;
    unsigned long hash = 0;

    for (char c : str) {
        hash = hash * a + c;
        a *= b;
    }
    return hash % bucketSize;
}

inline unsigned int BKDRHash(const string &str, unsigned int bucketSize) {
    unsigned long hash = 0;
    unsigned int seed = 131; // or 31, 131, 1313, 13131...
    for (char c : str) {
        hash = hash * seed + c;
    }
    return hash % bucketSize;
}

inline unsigned int sdbmHash(const char *p) {
    unsigned int hash = 0;
    auto *str = (unsigned char *) p;
    int c{};
    while ((c = *str++)) {
    hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

inline unsigned int Hash_function(string str, unsigned int num_buckets, string hash_name){
    
	if(hash_name == "BKDR")
		return BKDRHash(str, num_buckets);
	else if(hash_name == "RS")
		return RSHash(str, num_buckets);
	else
		return SDBMHash(str, num_buckets);

}

class SymbolInfo{
	private:
		string variable_name;
		string variable_type;
        string type_specifier;
		SymbolInfo *nextSymbolInfo = NULL;
		SymbolInfo *extraInfo = NULL;
		ostream *fout = &cout;
        bool is_array;
        bool is_func;
        bool is_defined;

	public:
    int int_val;
    float float_val;

    SymbolInfo(string variable_name, string variable_type ,string type_specifier, bool is_array = false, bool is_func = false, bool is_defined = false){
        this->variable_name = variable_name;
        this->variable_type = variable_type;
        this->type_specifier = type_specifier;
        this->is_array = is_array;
        this->is_func = is_func;
        this->is_defined = is_defined;
    }
    
     ~SymbolInfo(){
        // cout<<"SymbolInfo "<<this->variable_name<<" "<<variable_type<<" deleted"<<endl;
        if(this->extraInfo)
            delete extraInfo;
    }
    
    void  set_variable_name(string variable_name){
        this->variable_name = variable_name;
    }
    
    void  set_variable_type(string variable_type){
        this->variable_type = variable_type;
    }
    
    void set_type_specifier(string type_specifier){
        this->type_specifier = type_specifier;
    }

    void set_is_defined(bool is_defined){
        this->is_defined = is_defined;
    }

    void  set_symbolInfo(SymbolInfo* symbolInfo){
        this->nextSymbolInfo = symbolInfo;
    }
    
    string  get_variable_name(){
        return variable_name;
    }
    
    string  get_variable_type(){
        return variable_type;
    }

    string get_type_specifier(){
        return this->type_specifier;
    }

    bool get_is_array(){
        return this->is_array;
    }

    bool get_is_func(){
        return this->is_func;
    }

    bool get_is_defined(){
        return this->is_defined;
    }
    
    SymbolInfo*  get_next(){
        return nextSymbolInfo;
    }
    
    void  set_extra_info(SymbolInfo *extraSymbol){
        if(extraSymbol == NULL)
            return ;
    
        if(extraInfo == NULL)
            this->extraInfo = extraSymbol;
        else{
            SymbolInfo *temp = this->extraInfo;
            while(temp->get_extra_info()){
                temp = temp->get_extra_info();
            }
            temp->set_extra_info(extraSymbol);
        }
    
    }

    void set_extra_info(string variable_name, string variable_type ,string type_specifier, bool is_array = false, bool is_func = false){
        SymbolInfo *extraSymbol = new SymbolInfo(variable_name, variable_type, type_specifier, is_array, is_func);
        
        if(extraInfo == NULL)
            this->extraInfo = extraSymbol;
        else{
            SymbolInfo *temp = this->extraInfo;
            while(temp->get_extra_info()){
                temp = temp->get_extra_info();
            }
            temp->set_extra_info(extraSymbol);
        }
    }

    SymbolInfo*  get_extra_info(){
        return this->extraInfo;
    }
    
    void  Print(){
        if(this->get_variable_type() == "STRUCT" || this->get_variable_type() == "UNION"){
            *fout<<"<"<<variable_name<<","<<variable_type<<",";
            SymbolInfo *extra = this->extraInfo;
            while(extra){
                if(extra == this->extraInfo)
                    *fout<<"{";
                *fout<<"("<<extra->get_variable_type()<<","<<extra->get_variable_name()<<")";
                if(extra->get_extra_info() != NULL)
                    *fout<<",";
                else
                    *fout<<"}";
    
                extra = extra->get_extra_info();
            }
            *fout<<">";
        }else if(this->get_variable_type() == "FUNCTION"){
            *fout<<"<"<<variable_name<<","<<variable_type<<","<<this->extraInfo->get_variable_type()<<"<==";
            
            SymbolInfo *extra = this->extraInfo->get_extra_info();
            while(extra){
                if(extra == this->extraInfo->get_extra_info())
                    *fout<<"(";
                *fout<<extra->get_variable_type();
                if(extra->get_extra_info() != NULL)
                    *fout<<",";
                else
                    *fout<<")";
    
                extra = extra->get_extra_info();
            }
            *fout<<">";
        }else{
            *fout<<"< "<<variable_name<<" : "<<variable_type<<" >";
        }
    }
    
    void  set_output_stream(ostream *fout){
        this->fout = fout;
    }
    
			
};


class ScopeTable{
    private:
        double id;
        long long num_buckets;
        unsigned int (*hash_function)(string str, unsigned int num_buckets, string hash_name) = Hash_function;
        SymbolInfo** symbolInfos;
        ScopeTable *next;
        ostream *fout = &cout;
        string hash_name = "SDBM";
        float collision = 0;

    public:
      static int tab_space;

      ScopeTable(double id, string hash_name){
        this->id = id;
        this->num_buckets = 20;
        this->symbolInfos = new SymbolInfo*[num_buckets];
        for(int i = 0;i< num_buckets; i++){
            this->symbolInfos[i] = NULL;
        }
        this->hash_name = hash_name;
    }
    
      ScopeTable(double id, long long n, string hash_name){
        this->id = id;
        this->num_buckets = n;
        this->symbolInfos = new SymbolInfo*[num_buckets];
        for(int i = 0;i< num_buckets; i++){
            this->symbolInfos[i] = NULL;
        }
        this->hash_name = hash_name;
    }
    
      ~ScopeTable(){
        for(int i=0; i<this->num_buckets; i++){
            while(symbolInfos[i]){
                SymbolInfo *temp = symbolInfos[i];
                symbolInfos[i] = symbolInfos[i]->get_next();
                temp->set_symbolInfo(NULL);
                
                delete temp;
            }
        }
    
        delete[] symbolInfos;
        // *fout<<"\t\tScopeTable# "<<this->id<<" removed"<<endl;
        // cout<<"\t\tScopeTable# "<<this->id<<" removed"<<endl;
    
    }
    
    double   get_id(){
        return this->id;
    }
    
    void   set_next(ScopeTable *scopeTable){
        this->next = scopeTable;
    }
    
    ScopeTable*   get_next(){
        return this->next;
    }
    
    bool   Insert(SymbolInfo *symbol){
        string variable_name = symbol->get_variable_name();
        // cout<<"scope_table_insert "<<2.4<<endl;
        SymbolInfo* exists = this->Look_Up(variable_name);
        // cout<<"scope_table_insert "<<2.3<<endl;
    
        if(exists == NULL){
            
            long long hash_value = this->hash_function(symbol->get_variable_name(), this->num_buckets, this->hash_name);
            // cout<<variable_name<<endl;
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
            // *fout<<"\t\tInserted in ScopeTable# "<<this->id<<" at position "<<hash_value+1<<","<<list_symbol_no+1<<endl;
    
            return true;
        }
    
        delete symbol;
        // cout<<"scope_table_insert "<<2.7<<endl;
        return false;
    }
    
    SymbolInfo*   Look_Up(string &symbol_name){
        long long hash_value = this->hash_function(symbol_name, this->num_buckets, this->hash_name);
    
        SymbolInfo *temp = this->symbolInfos[hash_value];
        int list_symbol_pos = 0;
        while(temp){
    
            list_symbol_pos += 1;
            if(temp->get_variable_name() == symbol_name ){
                // *fout<<"\t\t'"<<symbol_name<<"' "<<"found in ScopeTable# "<<this->id<<" at position "<<hash_value + 1<<", "<< list_symbol_pos<<endl;
                return temp;
            }
            temp = temp->get_next();
    
        }
    
        // cout<<"scope_table_look_up "<<2.8<<endl;
        return NULL;
    }
    
    bool   Delete(string &symbol_name){
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
    
    void   Print(){
        
        // for(int j=0; j<  tab_space; j++){
        //     *fout<<"\t";
        // }
    
        *fout<<"ScopeTable # "<<this->id<<endl;
    
        for(int i=0; i<this->num_buckets; i++){
        
            // for(int j=0; j<  tab_space; j++){
            //     *fout<<"\t";
            // }
    
            if(this->symbolInfos[i] != NULL){
                *fout<<i<<" --> ";
                SymbolInfo *temp = this->symbolInfos[i];
    
                while(temp){
                    temp->Print();
                    temp = temp->get_next();
                }
                *fout<<endl;
            }
            
        }
    
    }
    
    void   set_output_stream(ostream *fout){
        this->fout = fout;
    }
    
    float   get_collision(){
        return this->collision;
    }
    

};

inline int  ScopeTable::tab_space = 0;


class SymbolTable{
    private:
        double num_scopeTable = 0;
        ScopeTable *scopeTables = NULL;
        long long num_buckets = 20;
        ostream *fout = &cout;
        string hash_name = "SDBM";
        float collision = 0;

    public:

     SymbolTable(){
        this->Enter_Scope();
    }
    
     SymbolTable(ostream *fout){
        this->fout = fout;
        this->Enter_Scope();
    }
    
    
     SymbolTable(long long n){
        this->num_buckets = n;
        this->Enter_Scope();
    }
    
     SymbolTable(long long n, ostream *fout, string hash_name){
        this->num_buckets = n;
        this->fout = fout;
        this->hash_name = hash_name;
        this->Enter_Scope();
    }
    
     ~SymbolTable(){
    
        ScopeTable *temp;
        while(this->scopeTables){
    
            temp = this->scopeTables;
            this->scopeTables = this->scopeTables->get_next();
            
            delete temp;
        }
    
    }

    int get_num_of_scopeTable(){
        return this->num_scopeTable;
    }
    
    void  Enter_Scope(){
    
        ScopeTable* scopeTable = new ScopeTable(1 + this->num_scopeTable*0.1, this->num_buckets, hash_name);
        this->num_scopeTable += 1;
    
        scopeTable->set_output_stream(this->fout);
        
        scopeTable->set_next(this->scopeTables);
        this->scopeTables = scopeTable;
    
        // *fout<<"\t\tScopeTable# "<<num_scopeTable<<" created"<<endl;
    
    }
    
    void  Exit_Scope(){
        ScopeTable *temp = this->scopeTables;
        if(temp->get_id() == 1)
            return ;
        
        this->scopeTables = temp->get_next();
        temp->set_next(NULL);
    
        this->collision += temp->get_collision();
        delete temp;
    }
    
    bool  Insert(string name, string type, string type_specifier, bool is_array = false, bool is_func = false, bool is_defined = false){
        SymbolInfo *symbol = new SymbolInfo(name, type, type_specifier, is_array, is_func, is_defined);
        symbol->set_output_stream(fout);
        return this->Insert(symbol);
    }
    
    bool  Insert(SymbolInfo *symbol){
        symbol->set_output_stream(fout);
        return this->scopeTables->Insert(symbol);
    }
    
    bool  Remove(string &symbol_name){
        bool removed = this->scopeTables->Delete(symbol_name);
    
        if(!removed){
            *fout<<"Not found in the current ScopeTable"<<endl;
        }
    
        return removed;
    }
    
    SymbolInfo*  Look_Up(string symbol_name){
        ScopeTable* temp = this->scopeTables;
        SymbolInfo* found_symbol = NULL;
        while(temp){
            found_symbol = temp->Look_Up(symbol_name);
            if( found_symbol != NULL)
                return found_symbol; 
                
            temp = temp->get_next();
        }

        if(found_symbol == NULL)
            cout<<"\t\t'"<<symbol_name<<"' not found in any of the ScopeTables"<<endl;
    
        return found_symbol;
    }
    
    void  Print_Current(){
        
          ScopeTable::tab_space += 2;
        this->scopeTables->Print();
        
          ScopeTable::tab_space = 0;
    
    }
    
    void  Print_All(){
        ScopeTable *temp = this->scopeTables;
    
        while(temp){
            //   tab_space += 2;
            temp->Print();
            temp = temp->get_next();
        }
        *fout<<endl; // extra
    
        //   tab_space = 0;
    
    }
    
    void  set_output_stream(ostream *fout){
        this->fout = fout;
    
    }
    
    float  get_collision(){
        ScopeTable *temp = this->scopeTables;
        while(temp){
            this->collision += temp->get_collision();
            temp = temp->get_next();
        }
    
        return this->collision/this->num_scopeTable;
    }
};

