#pragma once;
#include <iostream>
#include <string>
using namespace std;

class SymbolInfo{
	private:
		string variable_name;
		string variable_type;
		SymbolInfo *nextSymbolInfo = NULL;
		SymbolInfo *extraInfo = NULL;
		ostream *fout = &cout;
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

		void set_output_stream(ostream *fout);
			
};

SymbolInfo::SymbolInfo(string variable_name, string variable_type ){
	this->variable_name = variable_name;
	this->variable_type = variable_type;
}

SymbolInfo::~SymbolInfo(){
	// cout<<"SymbolInfo "<<this->variable_name<<" "<<variable_type<<" deleted"<<endl;
	if(this->extraInfo)
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

SymbolInfo* SymbolInfo::get_extra_info(){
	return this->extraInfo;
}

void SymbolInfo::Print(){
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

void SymbolInfo::set_output_stream(ostream *fout){
	this->fout = fout;
}

