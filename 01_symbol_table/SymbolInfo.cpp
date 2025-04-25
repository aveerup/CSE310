#pragma once
#include <iostream>
#include <string>
using namespace std;

class SymbolInfo{
	private:
		string variable_name;
		string variable_type;
		SymbolInfo *nextSymbolInfo;
		SymbolInfo *extraInfo = NULL;
	public:
		SymbolInfo(string variable_name, string variable_type);

		~SymbolInfo();

		void set_variable_name(string variable_name);

		void set_variable_type(string variable_type);

		void set_symbolInfo(SymbolInfo* nextSymbolInfo);

		string get_variable_name();

		string get_variable_type();

		SymbolInfo* get_next();

		void set_extra_info(SymbolInfo *extraInfo);

		SymbolInfo* get_extra_info();

		void Print();
			
};

SymbolInfo::SymbolInfo(string variable_name, string variable_type ){
	this->variable_name = variable_name;
	this->variable_type = variable_type;
}

SymbolInfo::~SymbolInfo(){
	if(extraInfo)
		delete extraInfo;
}

void SymbolInfo::set_variable_name(string variable_name){
	this->variable_name = variable_name;
}

void SymbolInfo::set_variable_type(string variable_type){
	this->variable_type = variable_type;
}

void SymbolInfo::set_symbolInfo(SymbolInfo* symbolInfo){
	this->nextSymbolInfo = symbolInfo;
}

string SymbolInfo::get_variable_name(){
	return variable_name;
}

string SymbolInfo::get_variable_type(){
	return variable_type;
}

SymbolInfo* SymbolInfo::get_next(){
	return nextSymbolInfo;
}

void SymbolInfo::set_extra_info(SymbolInfo *extraSymbol){
	if(extraSymbol == NULL)
		return ;

	cout<<"symbol_info_set_extra "<<2.6<<endl;
	extraSymbol->set_extra_info(this->extraInfo);
	cout<<"symbol_info_set_extra "<<2.5<<endl;
	this->extraInfo = extraSymbol;
}

SymbolInfo* SymbolInfo::get_extra_info(){
	return this->extraInfo;
}

void SymbolInfo::Print(){
	if(this->get_variable_name() == "Struct"){
		cout<<"<"<<variable_name<<","<<variable_type;
		SymbolInfo *extra = this->extraInfo;
		while(extra){
			cout<<",";
			if(extra == this->extraInfo)
				cout<<"{";
			cout<<"("<<extra->get_variable_type()<<extra->get_variable_name()<<")";
			if(extra->get_extra_info() != NULL)
				cout<<",";
			else
				cout<<"}";

			extra = extra->get_extra_info();
		}
		cout<<">";
	}else if(this->get_variable_name() == "Function"){
		cout<<"<"<<variable_name<<","<<variable_type;
		SymbolInfo *extra = this->extraInfo;
		while(extra){
			cout<<",";
			if(extra == this->extraInfo)
				cout<<"{";
			cout<<extra->get_variable_type();
			if(extra->get_extra_info() != NULL)
				cout<<",";
			else
				cout<<"}";

			extra = extra->get_extra_info();
		}
		cout<<">";
	}else{
		cout<<"<"<<variable_name<<","<<variable_type<<">";
	}
}

