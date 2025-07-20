parser grammar C8086Parser;

options {
    tokenVocab = C8086Lexer;
}

@parser::header {
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <cstdlib>
	#include <vector>
    #include "C8086Lexer.h"
	#include "info.cpp"
	#include "merged_symbol_table.cpp"

    extern std::ofstream parserLogFile;
    extern std::ofstream errorFile;
	extern std::ofstream assemblyLogFile;

    extern int syntaxErrorCount;

}

@parser::members {
    void writeIntoparserLogFile(const std::string message) {
        if (!parserLogFile) {
            std::cout << "Error opening parserLogFile.txt" << std::endl;
            return;
        }

        parserLogFile << message << std::endl;
        parserLogFile.flush();
    }

    void writeIntoErrorFile(const std::string message) {
        if (!errorFile) {
            std::cout << "Error opening errorFile.txt" << std::endl;
            return;
        }
        errorFile << message << std::endl;
        errorFile.flush();
    }

	void writeIntoAssemblyFile(const std::string code) {
		if(!assemblyLogFile) {
			std::cout << "Error opening assemblyLog.txt" << std::endl;
            return;
		}
		assemblyLogFile << code << std::endl;
		assemblyLogFile.flush();
	}

	SymbolTable symbolTable = SymbolTable(7, &parserLogFile, "SDBM");
	int in_func_check = 0;
	int in_loop_check = 0;
	int in_new_scope = 0;
	int just_in = 0;
	int SemanticErrorCount = 0;
	int code_seg_start = 0;
	int label_count = 0;
	int return_present = 0;
	int scope_variable_count = 0;
	int scope_parameter_count = 0;
	int variable_offset = 0;
	string running_function = "";

	enum REGISTERS {AX, BX, CX, DX};
	std::vector<bool> free_reg = vector<bool>(4);
	std::vector<string> exit_labels;
	std::vector<string> else_labels;
	std::vector<string> loop_start_labels;
	std::vector<string> loop_statement_labels;
	std::vector<string> inc_dec_labels;

	bool checkFloat(std::string str){
		bool float_check = true;
		int point = 0;
		int i = 0;
		
		for(; point == 0 && i<str.size(); i++){
			if(0 <= str[i] - '0'  && str[i] - '0' <= 9  ) {
					continue;
			}
			else if(str[i] == '.')
				point = 1;
			else 
				float_check = false;
		}

		if(i == str.size()){
			float_check = false;
		}

		for(; i<str.size(); i++){
			if(0<= str[i] - '0' <= 9)
				continue;
			else
				float_check = false;
		}

		return float_check;

	}

	std::string next_label(){
		label_count++;
		std::string nxt_lbl = "L" + std::to_string(label_count);
		
		return nxt_lbl;
	}

}


start
	: program {
		std::ifstream printFile("print.asm");
		std::string print_assembly = "";
		std::string line; 
		while(std::getline(printFile, line)){
			print_assembly += line + "\n";
		}
		printFile.close();
		writeIntoAssemblyFile(print_assembly);
		writeIntoAssemblyFile("END main");

		writeIntoparserLogFile("Line " + std::to_string($program.info.line_no)
			+ ": start : program\n");
		symbolTable.Print_All();
		writeIntoparserLogFile("Total lines: " + std::to_string($program.info.line_no));
		writeIntoparserLogFile("Total number of errors: " + std::to_string(syntaxErrorCount + SemanticErrorCount));
	}
	;

program returns [Info info]
	: p=program unit {
			$info.set_line($p.info)
				->set_line($unit.info);
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": program : program unit\n\n"
				+ $info.line + "\n");
	} 
	| unit{
			$info.set_line($unit.info);
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": program : unit\n\n"
				+ $info.line + "\n");
	}
	;
	
unit returns [Info info]
	 : vd=var_declaration {
			$info.set_line($vd.info);
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": unit : var_declaration\n\n"
				+ $info.line + "\n");
	 }
     | fd=func_declaration {
			$info.set_line($fd.info);
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": unit : func_declaration\n\n"
				+ $info.line + "\n");
	 }
     | fdn=func_definition {
			$info.set_line($fdn.info);
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": unit : func_definition\n\n"
				+ $info.line + "\n");
	 }
     ;
     
func_declaration returns [Info info] 
		: t=type_specifier ID LPAREN pl=parameter_list RPAREN SEMICOLON {
				SymbolInfo *temp = new SymbolInfo($ID->getText(), "ID", $t.info.line, false, true);
				for(int i = 0; i<$pl.params.size(); i++){
					temp->set_extra_info($pl.params[i].name, "ID", $pl.params[i].type, false, false);
				}
				symbolTable.Insert(temp);

				$info.set_line($t.info, 1)
					->set_line($ID->getText(), $ID->getLine())
					->set_line("(", $LPAREN->getLine())
					->set_line($pl.info)
					->set_line(")", $RPAREN->getLine())
					->set_line(";", $SEMICOLON->getLine(), 0, 1);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n"
					+ $info.line + "\n");
	 	}
		| t=type_specifier ID LPAREN RPAREN SEMICOLON {
				symbolTable.Insert($ID->getText(), "ID", $t.info.line, false, true);

				$info.set_line($t.info, 1)
					->set_line($ID->getText(), $ID->getLine())
					->set_line("(", $LPAREN->getLine())
					->set_line(")", $RPAREN->getLine())
					->set_line(";", $SEMICOLON->getLine(), 0, 1);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n\n"
					+ $info.line + "\n");
	 	}
		;
		 
func_definition returns [Info info]
		: t=type_specifier ID LPAREN pl=parameter_list RPAREN {
				SymbolInfo *temp = symbolTable.Look_Up($ID->getText());
				running_function = $ID->getText();
				
				if(temp != NULL){
					if(!temp->get_is_func()){
						writeIntoparserLogFile("Error at line" + std::to_string($ID->getLine()) 
							+ ": Multiple declaration of " + $ID->getText() + "\n");
						writeIntoErrorFile("Error at line" + std::to_string($ID->getLine()) 
							+ ": Multiple declaration of " + $ID->getText() + "\n");
					}else{
						bool same = temp->get_type_specifier() == $t.info.line;
						int i = 0;
						SymbolInfo *temp1 = temp;
						while(temp1->get_extra_info()){
							if(i >= $pl.params.size()){
								same = false;
								break;
							}
							same &= temp1->get_extra_info()->get_variable_name() == $pl.params[i].name;
							same &= temp1->get_extra_info()->get_type_specifier() == $pl.params[i].type;

							temp1 = temp1->get_extra_info();
							i++;
						}

						if(i<$pl.params.size()){
							same = false;
						}

						if(same && temp->get_is_defined()){
							writeIntoparserLogFile("Error at Line " + std::to_string($ID->getLine())
								+ ": Multiple definition of function " + $ID->getText() + "\n");
							writeIntoErrorFile("Error at Line " + std::to_string($ID->getLine())
								+ ": Multiple definition of function " + $ID->getText() + "\n");
						
						}else if(same && !temp->get_is_defined()){
							temp->set_is_defined(true);
							temp->set_total_parameter($pl.params.size());
							symbolTable.Enter_Scope();
							symbolTable.set_curr_parameter_count($pl.params.size());
							symbolTable.set_initial_var_offset(variable_offset);
							in_func_check = 1;
							just_in = 1;

							scope_parameter_count = $pl.params.size();
							for(int i = 0; i<$pl.params.size(); i++){
								SymbolInfo *temp = new SymbolInfo($pl.params[i].name, "ID", $t.info.line);
								temp->set_total_parameter($pl.params.size());
								temp->set_is_argument(true);
								symbolTable.Insert(temp);

							}

							if(code_seg_start == 0){
								writeIntoAssemblyFile(".CODE");
								code_seg_start = 1;

							}

							writeIntoAssemblyFile($ID->getText() + " PROC");
							writeIntoAssemblyFile("\tPUSH BP");
							writeIntoAssemblyFile("\tMOV BP, SP");

						}else{
							writeIntoparserLogFile("Error at Line " + std::to_string($ID->getLine())
								+ ": Multiple declaration of function " + $ID->getText() + "\n");
							writeIntoErrorFile("Error at Line " + std::to_string($ID->getLine())
								+ ": Multiple declaration of function " + $ID->getText() + "\n");
						}
					}

				}else{
					symbolTable.Insert($ID->getText(), "ID", $t.info.line, false, true, true);
					SymbolInfo *temp = symbolTable.Look_Up($ID->getText());
					temp->set_total_parameter($pl.params.size());
					symbolTable.Enter_Scope();
					symbolTable.set_curr_parameter_count($pl.params.size());
					symbolTable.set_initial_var_offset(variable_offset);
					in_func_check = 1;
					just_in = 1;
				
					scope_parameter_count = $pl.params.size();
					for(int i = 0; i<$pl.params.size(); i++){
						SymbolInfo *temp = new SymbolInfo($pl.params[i].name, "ID", $t.info.line);
						cout << "param no " << $pl.params.size() << endl;
						temp->set_total_parameter($pl.params.size());
						temp->set_is_argument(true);
						symbolTable.Insert(temp);

					}

					if(code_seg_start == 0){
						writeIntoAssemblyFile(".CODE");
						code_seg_start = 1;
					}

					writeIntoAssemblyFile($ID->getText() + " PROC");
					writeIntoAssemblyFile("\tPUSH BP");
					writeIntoAssemblyFile("\tMOV BP, SP");
				}
			
		}
		 cs=compound_statement {
				if(!return_present){
					writeIntoAssemblyFile("\tPOP BP");
					
					if(running_function != "main"){
						writeIntoAssemblyFile("\tRET " + std::to_string(scope_parameter_count*2));

					}else{
						writeIntoAssemblyFile("\tMOV AX, 4CH");
						writeIntoAssemblyFile("\tINT 21H");
					}

				}

				scope_variable_count = 0;
				scope_parameter_count = 0;

				writeIntoAssemblyFile($ID->getText() + " ENDP");

				if(in_func_check == 1){
					in_func_check = 0;

				}
				
				$info.set_line($t.info, 1)
					->set_line($ID->getText(), $ID->getLine())
					->set_line("(", $LPAREN->getLine())
					->set_line($pl.info)
					->set_line(")", $RPAREN->getLine())
					->set_line($cs.info, 0, 1);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n"
					+ $info.line + "\n");

	 	}
		| t=type_specifier ID LPAREN RPAREN {
				symbolTable.Insert($ID->getText(), "ID", $t.info.line, false, true);
				symbolTable.Enter_Scope();
				symbolTable.set_initial_var_offset(variable_offset);
				in_func_check = 1;
				just_in = 1;
				running_function = $ID->getText();

				if(code_seg_start == 0){
					writeIntoAssemblyFile(".CODE");
					code_seg_start = 1;
				}

				writeIntoAssemblyFile($ID->getText() + " PROC");
				if($ID->getText() == "main"){
					writeIntoAssemblyFile("\tMOV AX, @DATA");
					writeIntoAssemblyFile("\tMOV DS, AX");
				}
				writeIntoAssemblyFile("\tPUSH BP");
				writeIntoAssemblyFile("\tMOV BP, SP");

		}  
		cs=compound_statement {
				// std::cout<<"variable count "<<symbolTable.get_curr_scope_variable_no()<<std::endl;
				// std::cout<<"variable count "<<symbolTable.get_curr_scope_id()<<std::endl;
				if(!return_present){
					writeIntoAssemblyFile("\tPOP BP");
					
					if(running_function != "main"){
						writeIntoAssemblyFile("\tRET " + std::to_string(scope_parameter_count*2));

					}else{
						writeIntoAssemblyFile("\tMOV AX, 4CH");
						writeIntoAssemblyFile("\tINT 21H");
					}
				}
				
				scope_variable_count = 0;

				writeIntoAssemblyFile($ID->getText() + " ENDP");

				if(in_func_check == 1){
					in_func_check = 0;

				}

				$info.set_line($t.info, 1)
					->set_line($ID->getText(), $ID->getLine())
					->set_line("(", $LPAREN->getLine())
					->set_line(")", $RPAREN->getLine())
					->set_line($cs.info, 0, 1);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n"
					+ $info.line + "\n");

	 	}
		| t=type_specifier ID LPAREN plr=parameter_list_err RPAREN cs=compound_statement{
				$info.set_line($t.info, 1)
					->set_line($ID->getText(), $ID->getLine())
					->set_line("(", $LPAREN->getLine())
					->set_line($plr.info)
					->set_line(")", $RPAREN->getLine())
					->set_line($cs.info, 0, 1);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": func_definition : type_specifier ID LPAREN parameter_list_err RPAREN compound_statement\n\n"
					+ $info.line + "\n");
				writeIntoErrorFile("Error at line " + std::to_string($ID->getLine()) 
					+ ": syntax error, unexpected ADDOP, expecting RPAREN or COMMA\n");
		} 
 		;				

parameter_list_err returns [Info info] // hello
		: plr=parameter_list_err COMMA t=type_specifier ID{
				$info.set_line($plr.info)
					->set_line(",", $COMMA->getLine())
					->set_line($t.info)
					->set_line($ID->getText(), $ID->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": parameter_list_err : parameter_list_err COMMA type_specifier_err\n\n"
					+ $info.line + "\n"); 
					
		}
		| t=type_specifier ID ADDOP {
				$info.set_line($t.info, 1)
					->set_line($ID->getText(), $ID->getLine())
					->set_line($ADDOP->getText(), $ADDOP->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": parameter_list_err : type_specifier ID ADDOP\n\n"
					+ $info.line + "\n");

		}
		| t=type_specifier ID MULOP {
				$info.set_line($t.info, 1)
					->set_line($ID->getText(), $ID->getLine())
					->set_line($MULOP->getText(), $MULOP->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": parameter_list_err : type_specifier ID MULOP\n\n"
					+ $info.line + "\n");

		}
		| t=type_specifier ADDOP {
				$info.set_line($t.info, 1)
					->set_line($ADDOP->getText(), $ADDOP->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": parameter_list_err : type_specifier ID MULOP\n\n"
					+ $info.line + "\n");

		}
		;

parameter_list returns [Info info, std::vector<Param> params]  
		: pl=parameter_list COMMA t=type_specifier ID {
				$params = $pl.params;
				Param p;
				p.type = $t.info.line;
				p.name = $ID->getText();
				$params.push_back(p);
				$info.set_line($pl.info)
					->set_line(",", $COMMA->getLine())
					->set_line($t.info, 1)
					->set_line($ID->getText(), $ID->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": parameter_list : parameter_list COMMA type_specifier ID\n\n"
					+ $info.line + "\n");

	    }
		| pl=parameter_list COMMA t=type_specifier {
				$info.set_line($pl.info)
					->set_line(",", $COMMA->getLine())
					->set_line($t.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": parameter_list : parameter_list COMMA type_specifier\n\n"
					+ $info.line + "\n");

	 	}
 		| t=type_specifier ID {
				Param p;
				p.type = $t.info.line;
				p.name = $ID->getText();
				$params.push_back(p);
				// std::cout<<p.type<<" "<<p.name<<endl;
				$info.set_line($t.info, 1)
					->set_line($ID->getText(), $ID->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": parameter_list : type_specifier ID\n\n"
					+ $info.line + "\n");

	 	}
		| t=type_specifier {
				$info.set_line($t.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": parameter_list : type_specifier\n\n"
					+ $info.line + "\n");

	 	}
 		;

 		
compound_statement returns [Info info] 
	: LCURL {
			if(just_in == 1){
				in_new_scope++;
				just_in = 0;
				symbolTable.set_initial_var_offset(variable_offset);

			}else{
				in_new_scope++;
				symbolTable.Enter_Scope();
				symbolTable.set_initial_var_offset(variable_offset);
			
			}

	} 
	ss=statements RCURL {
			$info.set_line($LCURL->getText(), $LCURL->getLine(), 0, 1)
				->set_line($ss.info)
				->set_line($RCURL->getText(), $RCURL->getLine());
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": compound_statement : LCURL statements RCURL\n\n"
				+ $info.line + "\n");

			symbolTable.Print_All();
			in_new_scope--;

			writeIntoAssemblyFile("\tADD SP, " + std::to_string(variable_offset - symbolTable.get_initial_var_offset()));
			variable_offset = symbolTable.get_initial_var_offset();
			
			symbolTable.Exit_Scope();
			
			// std::cout<<"reached end of cmpnd_stat"<<std::endl;

	}
	| LCURL {
			if(just_in == 1){
				in_new_scope++;
				just_in = 0;

			}else{
				in_new_scope++;
				symbolTable.Enter_Scope();
				symbolTable.set_initial_var_offset(variable_offset);

			}

	} RCURL {
			in_new_scope--;
			writeIntoAssemblyFile("\tADD SP, " + std::to_string(variable_offset - symbolTable.get_initial_var_offset()));
			variable_offset = symbolTable.get_initial_var_offset();
			
			symbolTable.Exit_Scope();
			
			$info.set_line($LCURL->getText(), $LCURL->getLine())
				->set_line($RCURL->getText(), $RCURL->getLine());
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": compound_statement : LCURL RCURL\n\n"
				+ $info.line + "\n");
			
	}
	;
 		    
var_declaration returns [Info info]
    : t=type_specifier dl=declaration_list sm=SEMICOLON {
			for(int i = 0; i<$dl.IDs.size(); i++){
				if(symbolTable.get_curr_scope_id() != 1){
					variable_offset += $dl.IDs[i].array_size*2;
				}

				SymbolInfo *temp = new SymbolInfo($dl.IDs[i].name, "ID", $t.info.line, $dl.IDs[i].is_array);
				temp->set_variable_offset(variable_offset);
				temp->set_variable_size($dl.IDs[i].array_size);
				bool inserted = symbolTable.Insert(temp);
				
				if(!inserted){
					writeIntoparserLogFile("Error at line " + std::to_string($sm->getLine()) 
						+ ": Multiple declaration of " + $dl.IDs[i].name + "\n");
					writeIntoErrorFile("Error at line " + std::to_string($sm->getLine()) 
						+ ": Multiple declaration of " + $dl.IDs[i].name + "\n");
					syntaxErrorCount++;

				}else{
					if(symbolTable.get_curr_scope_id() == 1){

						if($dl.IDs[i].is_array){
							writeIntoAssemblyFile("\t" + $dl.IDs[i].name + " DW " + std::to_string($dl.IDs[i].array_size) +" DUP (0000H)");
						}else{
							writeIntoAssemblyFile("\t" + $dl.IDs[i].name + " DW 1 DUP (0000H)");
						}

					}else{

						if($dl.IDs[i].is_array){
							writeIntoAssemblyFile("\tSUB SP, " + std::to_string($dl.IDs[i].array_size*2));
						}else{
							writeIntoAssemblyFile("\tSUB SP, 2");
						}

					}
				}
			}

			$info.set_line($t.info, 1)
				->set_line($dl.info)
				->set_line(";", $sm->getLine(), 0, 1);
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": var_declaration : type_specifier declaration_list SEMICOLON\n\n"
				+ $info.line + "\n");

	 }
    | t=type_specifier dlr=declaration_list_err sm=SEMICOLON {
			$info.set_line($t.info)
				->set_line($dlr.info)
				->set_line($sm->getText(), $sm->getLine());

			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": var_declaration : type_specifier declaration_list_err SEMICOLON\n\n"
				+ $info.line + "\n");
			writeIntoErrorFile("Error at line " + std::to_string($info.line_no) 
				+ ": syntax error, unexpected ADDOP, expecting COMMA or SEMICOLON\n");
			syntaxErrorCount++;

      }
    ;

declaration_list_err returns [Info info]
	: id1=ID ADDOP id2=ID {
			$info.set_line($id1->getText(), $id1->getLine())
				->set_line($ADDOP->getText(), $ADDOP->getLine())
				->set_line($id2->getText(), $id2->getLine());
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": declaration_list_err : ID ADDOP ID\n\n"
				+ $info.line + "\n");

    }
	| id1=ID ADDOP {
			$info.set_line($id1->getText(), $id1->getLine())
				->set_line($ADDOP->getText(), $ADDOP->getLine());
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": declaration_list_err : ID ADDOP\n\n"
				+ $info.line + "\n");

	}
	| id1=ID MULOP id2=ID {
			$info.set_line($id1->getText(), $id1->getLine())
				->set_line($MULOP->getText(), $MULOP->getLine())
				->set_line($id2->getText(), $id2->getLine());
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": declaration_list_err : ID MULOP ID\n\n"
				+ $info.line + "\n");

	}
	| id1=ID MULOP {
			$info.set_line($id1->getText(), $id1->getLine())
				->set_line($MULOP->getText(), $MULOP->getLine());
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": declaration_list_err : ID MULOP\n\n"
				+ $info.line + "\n");

	}
	| dlr=declaration_list_err COMMA ID{
			$info.set_line($dlr.info)
				->set_line($COMMA->getText(), $COMMA->getLine())
				->set_line($ID->getText(), $ID->getLine());
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": declaration_list_err : declaration_list_err COMMA ID\n\n"
				+ $info.line + "\n");

	}
	;

 		 
type_specifier returns [Info info]	
        : INT {
				$info.line = $INT->getText();
				$info.line_no = $INT->getLine();
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": type_specifier : INT\n\n" + $info.line + "\n");

        }
 		| FLOAT {
				$info.line = $FLOAT->getText();
				$info.line_no = $FLOAT->getLine();
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": type_specifier : FLOAT\n\n" + $info.line + "\n");

        }
 		| VOID {
				$info.line = $VOID->getText();
				$info.line_no = $VOID->getLine();
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": type_specifier : VOID\n\n" + $info.line + "\n");

        }
 		;

 		
declaration_list returns [Info info, vector<Param> IDs] 
		: dl=declaration_list COMMA ID {
				$IDs = $dl.IDs;
				$IDs.push_back(Param($ID->getText()));

				$info.set_line($dl.info)
					->set_line(",", $COMMA->getLine())
					->set_line($ID->getText(), $ID->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": declaration_list : declaration_list COMMA ID\n\n"
					+ $info.line + "\n");

		}
		| dl=declaration_list COMMA ID LTHIRD CONST_INT RTHIRD {
				$IDs = $dl.IDs;
		
				Param t($ID->getText(), true);
				t.array_size = stoi($CONST_INT->getText());
				$IDs.push_back(t);

				$info.set_line($dl.info)
					->set_line(",", $COMMA->getLine())
					->set_line($ID->getText(), $ID->getLine())
					->set_line("[", $LTHIRD->getLine())
					->set_line($CONST_INT->getText(), $CONST_INT->getLine())
					->set_line("]", $RTHIRD->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n"
					+ $info.line + "\n");

		}
		| ID {
				$IDs.push_back(Param($ID->getText()));

				$info.set_line($ID->getText(), $ID->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": declaration_list : ID\n\n"
					+ $info.line + "\n");

		}
		| ID LTHIRD CONST_INT RTHIRD {
				Param t($ID->getText(), true);
				t.array_size = stoi($CONST_INT->getText());
				$IDs.push_back(t);

				$info.set_line($ID->getText(), $ID->getLine())
					->set_line("[", $LTHIRD->getLine())
					->set_line($CONST_INT->getText(), $CONST_INT->getLine())
					->set_line("]", $RTHIRD->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": declaration_list : ID LTHIRD CONST_INT RTHIRD\n\n"
					+ $info.line + "\n");

		}
		;
 		  
statements returns [Info info]
	   : s=statement {
				$info.set_line($s.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": statements : statement\n\n"
					+ $info.line + "\n");

		}
	   | ss=statements {
				writeIntoAssemblyFile(next_label() + ":");

	   } s=statement {
				$info.set_line($ss.info)
					->set_line($s.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": statements : statements statement\n\n"
					+ $info.line + "\n");

	   }
	   ;
	   
statement returns [Info info]
      : vd=var_declaration {
				$info.set_line($vd.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": statement : var_declaration\n\n"
					+ $info.line + "\n");

	  }
	  | es=expression_statement {
				$info.set_line($es.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": statement : expression_statement\n\n"
					+ $info.line + "\n");

	  }
	  | c=compound_statement {
				$info.set_line($c.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": statement : compound_statement\n\n"
					+ $info.line + "\n");

	  }
	  | FOR LPAREN es1=expression_statement {
				loop_start_labels.push_back(next_label());
				writeIntoAssemblyFile(loop_start_labels.back() + ":");

	  } es2=expression_statement {
				writeIntoAssemblyFile("\tCMP AX, 0");
				
				exit_labels.push_back(next_label());
				writeIntoAssemblyFile("\tJE " + exit_labels.back());
				
				loop_statement_labels.push_back(next_label());
				writeIntoAssemblyFile("\tJMP " + loop_statement_labels.back());

				inc_dec_labels.push_back(next_label());
				writeIntoAssemblyFile(inc_dec_labels.back() + ":");

	  } e=expression {
				writeIntoAssemblyFile("\tPOP AX");
				writeIntoAssemblyFile("\tJMP " + loop_start_labels.back());
				loop_start_labels.pop_back();

				writeIntoAssemblyFile(loop_statement_labels.back() + ":");
				loop_statement_labels.pop_back();

	  } RPAREN {
				in_loop_check ++;
				just_in = 1;
				symbolTable.Enter_Scope();
				symbolTable.set_initial_var_offset(variable_offset);

	  } s=statement {
				if(in_loop_check > 0){
					in_loop_check--;
				}

				writeIntoAssemblyFile("\tJMP " + inc_dec_labels.back());
				inc_dec_labels.pop_back();

				writeIntoAssemblyFile(exit_labels.back() + ":");
				exit_labels.pop_back();

				$es1.info.line.pop_back();
				$es2.info.line.pop_back();
				$info.set_line("for", $FOR->getLine());
				$info.set_line("(", $LPAREN->getLine());
				$info.set_line($es1.info);
				$info.set_line($es2.info);
				$info.set_line($e.info);
				$info.set_line(")", $RPAREN->getLine());
				$info.set_line($s.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n"
					+ $info.line + "\n");

	   }
	  | IF LPAREN e=expression RPAREN {
				in_new_scope++;
				just_in = 1;
				symbolTable.Enter_Scope();
				symbolTable.set_initial_var_offset(variable_offset);

				writeIntoAssemblyFile("\tPOP AX");
				writeIntoAssemblyFile("\tCMP AX, 0");
				exit_labels.push_back(next_label());
				writeIntoAssemblyFile("\tJE " + exit_labels.back());

	  } s=statement {
				if(in_new_scope > 0){
					in_new_scope--;
				}
				writeIntoAssemblyFile(exit_labels.back() + ":");
				exit_labels.pop_back();

				$info.set_line("if", $IF->getLine());
				$info.set_line("(", $LPAREN->getLine());
				$info.set_line($e.info);
				$info.set_line(")", $RPAREN->getLine());
				$info.set_line($s.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": statement : IF LPAREN expression RPAREN statement\n\n"
					+ $info.line + "\n");

	   }
	  | IF LPAREN e=expression RPAREN {
				in_new_scope++;
				just_in = 1;
				symbolTable.Enter_Scope();
				symbolTable.set_initial_var_offset(variable_offset);

				writeIntoAssemblyFile("\tPOP AX");
				writeIntoAssemblyFile("\tCMP AX, 0");
				else_labels.push_back(next_label());
				writeIntoAssemblyFile("\tJE " + else_labels.back());

	  } s1=statement {
				if(in_new_scope > 0){
					in_new_scope--;

				}
	  } ELSE {
				in_new_scope++;
				just_in = 1;
				symbolTable.Enter_Scope();
				symbolTable.set_initial_var_offset(variable_offset);

				exit_labels.push_back(next_label());
				writeIntoAssemblyFile("\tJMP " + exit_labels.back());
				
				writeIntoAssemblyFile(else_labels.back() + ":");
				else_labels.pop_back();
				
	  } s2=statement {
				if(in_new_scope > 0){
					in_new_scope--;

				}

				writeIntoAssemblyFile(exit_labels.back() + ":");
				exit_labels.pop_back();

				$info.set_line("if", $IF->getLine())
					->set_line("(", $LPAREN->getLine())
					->set_line($e.info)
					->set_line(")", $RPAREN->getLine())
					->set_line($s1.info)
					->set_line("else ", $ELSE->getLine())
					->set_line($s2.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": statement : IF LPAREN expression RPAREN statement ELSE statement\n\n"
					+ $info.line + "\n");
	   }
	  | WHILE LPAREN {
				loop_start_labels.push_back(next_label());
				writeIntoAssemblyFile(loop_start_labels.back() + ":");

	  } e=expression RPAREN{
				writeIntoAssemblyFile("\tPOP AX");
				writeIntoAssemblyFile("\tCMP AX, 0");

				exit_labels.push_back(next_label());
				writeIntoAssemblyFile("\tJE " + exit_labels.back());

				in_loop_check++;
				just_in = 1;
				symbolTable.Enter_Scope();
				symbolTable.set_initial_var_offset(variable_offset);

	  } s=statement {
				if(in_loop_check>0){
					in_loop_check--;

				}

				writeIntoAssemblyFile("\tJMP " + loop_start_labels.back());
				loop_start_labels.pop_back();

				writeIntoAssemblyFile(exit_labels.back() + ":");
				exit_labels.pop_back();

				$info.set_line("while", $WHILE->getLine())
					->set_line("(", $LPAREN->getLine())
					->set_line($e.info)
					->set_line(")", $RPAREN->getLine())
					->set_line($s.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": statement : WHILE LPAREN expression RPAREN statement\n\n"
					+ $info.line + "\n");

	   }
		| DO {
				in_loop_check++;
				just_in = 1;
				symbolTable.Enter_Scope();
				symbolTable.set_initial_var_offset(variable_offset);

		}compound_statement WHILE LPAREN expression RPAREN  SEMICOLON{
				if(in_loop_check>0){
						in_loop_check--;

					}

		} 
	  | PRINTLN LPAREN ID RPAREN SEMICOLON {
				// cout<<"5.5 PRINTLN "<<$PRINTLN->getText()<<endl;
				SymbolInfo *temp = symbolTable.Look_Up($ID->getText());

				if(temp == NULL){
					writeIntoparserLogFile("Error at line " + std::to_string($ID->getLine()) 
						+ ": Undeclared variable " + $ID->getText() + "\n");
					writeIntoErrorFile("Error at line " + std::to_string($ID->getLine()) 
						+ ": Undeclared variable " + $ID->getText() + "\n");
					syntaxErrorCount++;

				}else if(temp->get_scope() == 1){
					writeIntoAssemblyFile("\tMOV AX, " + $ID->getText());

					writeIntoAssemblyFile("\tCALL print_output");
					writeIntoAssemblyFile("\tCALL new_line");

				}else{
					if(temp->get_is_argument()){
						writeIntoAssemblyFile("\tMOV AX, [BP+" + std::to_string((temp->get_total_parameter() + 2 - temp->get_info_no())*2) + "]");
					
					}else{
						writeIntoAssemblyFile("\tMOV AX, [BP-" + std::to_string(temp->get_variable_offset()) + "]");

					}
					writeIntoAssemblyFile("\tCALL print_output");
					writeIntoAssemblyFile("\tCALL new_line");

				}

				$info.set_line($PRINTLN->getText(), $PRINTLN->getLine())
					->set_line("(", $LPAREN->getLine())
					->set_line($ID->getText(), $ID->getLine())
					->set_line(")", $RPAREN->getLine())
					->set_line(";", $SEMICOLON->getLine(), 0, 1);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n"
					+ $info.line + "\n");

	   }
	  | RETURN e=expression SEMICOLON {
				return_present = 1;

				writeIntoAssemblyFile("\tPOP DX");
				writeIntoAssemblyFile("\tMOV AX, DX");
				
				writeIntoAssemblyFile("\tADD SP, " + std::to_string(variable_offset));
				writeIntoAssemblyFile("\tPOP BP");
				cout << "running_function" << running_function << endl;
				if(running_function == "main"){
					writeIntoAssemblyFile("\tMOV AX, 4CH");
					writeIntoAssemblyFile("\tINT 21H");
				
				}else{
					writeIntoAssemblyFile("\tRET " + std::to_string(scope_parameter_count*2));

				}

				$info.set_line("return", $RETURN->getLine(), 1, 0)
					->set_line($e.info)
					->set_line(";", $SEMICOLON->getLine(), 0, 1);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": statement : RETURN expression SEMICOLON\n\n"
					+ $info.line + "\n");

	   }
	   | CONTINUE SEMICOLON {
				if(in_loop_check == 0){
					writeIntoErrorFile("Line No. " + std::to_string($CONTINUE->getLine()) 
						+ ": Continue outside loop\n");
				}

				$info.set_line("continue", $CONTINUE->getLine())
					->set_line(";", $SEMICOLON->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": statement : CONTINUE SEMICOLON SEMICOLON\n\n"
					+ $info.line + "\n");

		}
		| BREAK SEMICOLON {
				if(in_loop_check == 0){
					writeIntoErrorFile("Line No. " + std::to_string($BREAK->getLine()) 
						+ ": break outside loop\n");
				}

				$info.set_line("break", $BREAK->getLine())
					->set_line(";", $SEMICOLON->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": statement : BREAK SEMICOLON SEMICOLON\n\n"
					+ $info.line + "\n");

		}
	    ;
	  
expression_statement returns [Info info] 
		: SEMICOLON	{
				$info.set_line(";", $SEMICOLON->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": expression_statement : SEMICOLON\n\n"
					+ $info.line + "\n");
					
		}		
		| e=expression SEMICOLON {
				writeIntoAssemblyFile("\tPOP AX");

				$info.set_line($e.info)
					->set_line(";", $SEMICOLON->getLine(), 0, 1);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": expression_statement : expression SEMICOLON\n\n"
					+ $info.line + "\n");

		}
		| er=expression_err SEMICOLON {
				$info.set_line($er.info)
					->set_line(";", $SEMICOLON->getLine(), 0, 1);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": expression_statement : expression_err SEMICOLON\n\n"
					+ $info.line + "\n");
				writeIntoErrorFile("Error at line " + std::to_string($info.line_no) 
					+ ": syntax error, unexpected ASSIGNOP");
					syntaxErrorCount++;
		}
		;
	  
variable returns [Info info, Param param]
		: ID {
				SymbolInfo *temp = symbolTable.Look_Up($ID->getText());
				cout << 5.1 << " " << $ID->getText() << endl;

				if(temp == NULL){
					Param t($ID->getText());
					cout << t.name << endl;
					$param = t;
				}else if(temp->get_is_array()){
					writeIntoparserLogFile("Error at line " + std::to_string($ID->getLine()) 
						+ ": Type mismatch, " + $ID->getText() + " is an array\n");
					writeIntoErrorFile("Error at line " + std::to_string($ID->getLine()) 
						+ ": Type mismatch, " + $ID->getText() + " is an array\n");
					syntaxErrorCount++;
				}else{
					Param t(temp->get_type_specifier(), temp->get_variable_name(), temp->get_is_array(), temp->get_is_func());
					$param = t;
					cout << t.name << endl;

				}

				$info.set_line($ID->getText(), $ID->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": variable : ID\n\n"
					+ $info.line + "\n");
		} 		
		| ID LTHIRD e=expression RTHIRD {
				SymbolInfo *temp = symbolTable.Look_Up($ID->getText());
				cout<<5.2<<endl;

				if(temp == NULL){
					Param t("error", $ID->getText(), false, false);
					$param = t;
					writeIntoErrorFile("Error at line " + std::to_string($ID->getLine()) 
						+ ": Undeclared variable " + $ID->getText() + "\n");
					syntaxErrorCount++;
				}else{
					Param t(temp->get_type_specifier(), temp->get_variable_name(), temp->get_is_array(), temp->get_is_func());
					$param = t;

					if(!temp->get_is_array()){
						writeIntoparserLogFile("Error at line " + std::to_string($ID->getLine()) 
							+ ": Type mismatch," + $ID->getText() + " is not an array\n");
						writeIntoErrorFile("Error at line " + std::to_string($ID->getLine()) 
							+ ": Type mismatch," + $ID->getText() + " is not an array\n");
						syntaxErrorCount++;
					}

				}

				if(checkFloat($e.info.line)){
					Param t("error", $ID->getText(), false, false);
					$param = t;
					writeIntoErrorFile("Error at line " + std::to_string($ID->getLine()) 
						+ ": Expression inside third brackets not an integer\n");
					SemanticErrorCount++;
				}

				$info.set_line($ID->getText(), $ID->getLine())
					->set_line("[", $LTHIRD->getLine())
					->set_line($e.info)
					->set_line("]", $RTHIRD->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": variable : ID LTHIRD expression RTHIRD\n\n");
				if(checkFloat($e.info.line)){
					writeIntoparserLogFile("Error at line " + std::to_string($e.info.line_no) 
						+ ": Expression inside third brackets not an integer\n\n"
						+ $info.line +"\n");
				}else{
					writeIntoparserLogFile($info.line + "\n");
				}

		}
		|ID LTHIRD er=expression_err RTHIRD {
				$info.set_line($ID->getText(), $ID->getLine())
					->set_line("[", $LTHIRD->getLine())
					->set_line($er.info)
					->set_line("]", $RTHIRD->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": variable : ID LTHIRD expression_err RTHIRD\n\n");
				writeIntoErrorFile("Error at line " + std::to_string($info.line_no) 
					+ ": syntax error, unexpected ASSIGNOP\n");
					syntaxErrorCount++;
		}  
		;
	 
 expression returns [Info info, Param param]
 	   : le=logic_expression {
				$param = $le.param;
				$info.set_line($le.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": expression : logic_expression\n\n"
					+ $info.line + "\n");

	   }	
	   | var=variable ASSIGNOP le=logic_expression {
				// cout<<"ASSIGNOP "<<$param.type<<" "<<endl;
				// cout<<"ASSIGNOP "<<$le.param.type<<" "<<endl;

				SymbolInfo *temp = symbolTable.Look_Up($var.param.name);
				cout<<5.3<<endl;

				if(temp == NULL){
					Param t("error", $var.param.name, false, false);
					$param = t;
					writeIntoparserLogFile("Error at line " + std::to_string($ASSIGNOP->getLine()) 
						+ ": Undeclared variable " + $var.param.name + "\n");
					writeIntoErrorFile("Error at line " + std::to_string($ASSIGNOP->getLine()) 
						+ ": Undeclared variable " + $var.param.name + "\n");
					syntaxErrorCount++;

				}else if($variable.param.type != $le.param.type 
					&& $var.param.type != "error"
					&& $le.param.type != "error"
					&& !($var.param.type == "bool" && $le.param.type == "int")
					&& !($var.param.type == "int" && $le.param.type == "bool")){

					// cout<<"ASSIGNOP1 "<<$var.param.type<<" "<<$var.info.line<<endl;
					// cout<<"ASSIGNOP1 "<<$le.param.type<<" "<<$le.info.line<<endl;
					writeIntoErrorFile("Error at line " + std::to_string($ASSIGNOP->getLine()) 
						+ ": Type Mismatch\n");
					SemanticErrorCount++;

				}else{
					Param t(temp->get_type_specifier(), temp->get_variable_name(), temp->get_is_array(), temp->get_is_func());
					$param = t;

					writeIntoAssemblyFile("\tPOP AX");

					if(temp->get_scope() == 1){
						if(temp->get_is_array()){
							writeIntoAssemblyFile("\tPOP DX");
							writeIntoAssemblyFile("\tPUSH AX");
							writeIntoAssemblyFile("\tMOV AX, DX");
							writeIntoAssemblyFile("\tCWD");
							writeIntoAssemblyFile("\tMOV CX, 2");
							writeIntoAssemblyFile("\tMUL CX");
							writeIntoAssemblyFile("\tMOV BX, AX");
							writeIntoAssemblyFile("\tPOP AX");
							writeIntoAssemblyFile("\tMOV " + temp->get_variable_name() + "[BX], AX");

						}else{
							writeIntoAssemblyFile("\tMOV " + $var.param.name + ", AX");
						}

					}else{
						if(temp->get_is_argument()){
							writeIntoAssemblyFile("\tMOV [BP+" + std::to_string((temp->get_total_parameter() + 2 - temp->get_info_no())*2) + "], AX");
						
						}else if(temp->get_is_array()){
							writeIntoAssemblyFile("\tPOP DX");
							writeIntoAssemblyFile("\tPUSH AX");
							writeIntoAssemblyFile("\tMOV AX, DX");
							writeIntoAssemblyFile("\tCWD");
							writeIntoAssemblyFile("\tMOV CX, 2");
							writeIntoAssemblyFile("\tMUL CX");
							writeIntoAssemblyFile("\tMOV BX, " + std::to_string(temp->get_variable_offset()));
							writeIntoAssemblyFile("\tSUB BX, AX");
							writeIntoAssemblyFile("\tMOV SI, BX");
							writeIntoAssemblyFile("\tNEG SI");
							writeIntoAssemblyFile("\tPOP AX");
							writeIntoAssemblyFile("\tMOV [BP+SI], AX");

						}else{
							cout << "total para " << temp->get_total_parameter() << " info no " << temp->get_info_no() <<endl;
							writeIntoAssemblyFile("\tMOV [BP-" + std::to_string(temp->get_variable_offset()) + "], AX");

						}
					}

					writeIntoAssemblyFile("\tPUSH AX");
				}

				$info.set_line($variable.info)
					->set_line($ASSIGNOP->getText(), $ASSIGNOP->getLine())
					->set_line($le.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": expression : variable ASSIGNOP logic_expression\n\n"
					+ $info.line + "\n");

	   } 	
	   ;

expression_err returns [Info info]
	: variable ADDOP ASSIGNOP le=logic_expression {
			$info.set_line($variable.info)
					->set_line($ADDOP->getText(), $ADDOP->getLine())
					->set_line($ASSIGNOP->getText(), $ASSIGNOP->getLine())
					->set_line($le.info);
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": expression_err : variable ADDOP ASSIGNOP logic_expression\n\n"
				+ $info.line + "\n");
	}
	| variable ASSIGNOP ADDOP le=logic_expression {
			$info.set_line($variable.info)
					->set_line($ASSIGNOP->getText(), $ASSIGNOP->getLine())
					->set_line($ADDOP->getText(), $ADDOP->getLine())
					->set_line($le.info);
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": expression_err : variable ASSIGNOP ADDOP logic_expression\n\n"
				+ $info.line + "\n");
	}
	| variable MULOP ASSIGNOP le=logic_expression {
			$info.set_line($variable.info)
					->set_line($MULOP->getText(), $MULOP->getLine())
					->set_line($ASSIGNOP->getText(), $ASSIGNOP->getLine())
					->set_line($le.info);
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": expression : variable ASSIGNOP logic_expression\n\n"
				+ $info.line + "\n");
	}
	| variable ASSIGNOP MULOP le=logic_expression {
			$info.set_line($variable.info)
					->set_line($ASSIGNOP->getText(), $ASSIGNOP->getLine())
					->set_line($MULOP->getText(), $MULOP->getLine())
					->set_line($le.info);
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": expression : variable ASSIGNOP logic_expression\n\n"
				+ $info.line + "\n");
	}
	;
			
logic_expression returns [Info info, Param param]
		 : re=rel_expression {
				$param = $re.param;
				// cout<<"logic_expression "<<$param.type<<" "<<$param.value<<endl;

				$info.set_line($re.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": logic_expression : rel_expression\n\n"
					+ $info.line + "\n");

		 } 	
		 | re1=rel_expression LOGICOP re2=rel_expression {
				if($re1.param.type == "void"){
					Param t("error", "logic_expression", false, false);
					$param = t;
					writeIntoErrorFile("Error at Line " + std::to_string($re1.info.line_no) 
						+ ": simple_expression " + $re1.info.line + " cannot be void\n");
					SemanticErrorCount++;

				}else if($re2.param.type == "void"){
					Param t("error", "logic_expression", false, false);
					$param = t;
					writeIntoErrorFile("Error at Line " + std::to_string($re2.info.line_no) 
						+ ": term " + $re2.info.line + " cannot be void\n");
					SemanticErrorCount++;

				}else{
					Param t("bool", "logic_expression", false, false);
					$param = t;

				}

				writeIntoAssemblyFile("\tPOP AX");
				writeIntoAssemblyFile("\tPOP DX");
				writeIntoAssemblyFile("\tCMP DX, 0");

				string false_label = next_label();
				string exit_label = next_label();

				if($LOGICOP->getText() == "||"){
					string check2_label = next_label();

					writeIntoAssemblyFile("\tJE " + check2_label);
					
					writeIntoAssemblyFile("\tPUSH 1");
					writeIntoAssemblyFile("\tJMP " + exit_label);

					writeIntoAssemblyFile(check2_label + ":");
					writeIntoAssemblyFile("\tCMP AX, 0");
					writeIntoAssemblyFile("\tJE " + false_label);
					
					writeIntoAssemblyFile("\tPUSH 1");
					writeIntoAssemblyFile("JMP " + exit_label);
				
				}else if($LOGICOP->getText() == "&&"){

					writeIntoAssemblyFile("\tJE " + false_label);
					writeIntoAssemblyFile("\tCMP AX, 0");
					writeIntoAssemblyFile("\tJE " + false_label);

					writeIntoAssemblyFile("\tPUSH 1");
					writeIntoAssemblyFile("\tJMP " + exit_label);

				}

				writeIntoAssemblyFile(false_label + ":");
				writeIntoAssemblyFile("PUSH 0");
				writeIntoAssemblyFile(exit_label + ":");

				$info.set_line($re1.info)
					->set_line($LOGICOP->getText(), $LOGICOP->getLine())
					->set_line($re2.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": logic_expression : rel_expression LOGICOP rel_expression\n\n"
					+ $info.line + "\n");

		 } 	
		 ;
			
rel_expression	returns [Info info, Param param]
        : se=simple_expression {
				$param = $se.param;
				// cout<<"rel "<<$param.type<<" "<<$param.value<<endl;

				$info.set_line($se.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": rel_expression : simple_expression\n\n"
					+ $info.line + "\n");
		} 
		| se1=simple_expression RELOP se2=simple_expression {
				if($se1.param.type == "void"){
					Param t("error", "rel_expression", false, false);
					$param = t;
					writeIntoErrorFile("Error at Line " + std::to_string($se1.info.line_no) 
						+ ": simple_expression " + $se1.info.line + " cannot be void\n");
					SemanticErrorCount++;
				}else if($se2.param.type == "void"){
					Param t("error", "rel_expression", false, false);
					$param = t;
					writeIntoErrorFile("Error at Line " + std::to_string($se2.info.line_no) 
						+ ": term " + $se2.info.line + " cannot be void\n");
					SemanticErrorCount++;
				}else{
					Param t("bool", "rel_expression", false, false);
					$param = t;
				}

				writeIntoAssemblyFile("\tPOP AX");
				writeIntoAssemblyFile("\tPOP DX");
				writeIntoAssemblyFile("\tCMP DX, AX");
				
				string truth_label = next_label();
				if($RELOP->getText() == ">"){
					writeIntoAssemblyFile("\tJG " + truth_label);
				}else if($RELOP->getText() == "<"){
					writeIntoAssemblyFile("\tJL " + truth_label);
				}else if($RELOP->getText() == ">="){
					writeIntoAssemblyFile("\tJGE " + truth_label);
				}else if($RELOP->getText() == "<="){
					writeIntoAssemblyFile("\tJLE " + truth_label);
				}else if($RELOP->getText() == "=="){
					writeIntoAssemblyFile("\tJE " + truth_label);
				}else if($RELOP->getText() == "!="){
					writeIntoAssemblyFile("\tJNE " + truth_label);
				}

				writeIntoAssemblyFile("\tPUSH 0");
				string exit_label = next_label();
				writeIntoAssemblyFile("\tJMP "+ exit_label);

				writeIntoAssemblyFile(truth_label + ":");
				writeIntoAssemblyFile("\tPUSH 1");
				writeIntoAssemblyFile(exit_label + ":");

				$info.set_line($se1.info)
					->set_line($RELOP->getText(), $RELOP->getLine())
					->set_line($se2.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": rel_expression : simple_expression RELOP simple_expression\n\n"
					+ $info.line + "\n");
		}	
		;
				
simple_expression returns [Info info, Param param]
		  : term {
				$param = $term.param;
				// cout<<"simple_expression "<<$param.type<<" "<<$term.info.line<<endl;


				$info.set_line($term.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": simple_expression : term\n\n"
					+ $info.line + "\n");
		  } 
		  | se=simple_expression ADDOP term {
				if($se.param.type == "void"){
					Param t("error", "simple_expression", false, false);
					$param = t;
					writeIntoErrorFile("Error at Line " + std::to_string($se.info.line_no) 
						+ ": simple_expression " + $se.info.line + " cannot be void\n");
					SemanticErrorCount++;
				}else if($term.param.type == "void"){
					Param t("error", "simple_expression", false, false);
					$param = t;
					writeIntoErrorFile("Error at Line " + std::to_string($term.info.line_no) 
						+ ": term " + $term.info.line + " cannot be void\n");
					SemanticErrorCount++;
				}else if($se.param.type == "float" || $term.param.type ==  "float"){
					Param t("float", "simple_expression", false, false);
					$param = t;
				}else{
					Param t("int", "simple_expression", false, false);
					$param = t;
				}

				writeIntoAssemblyFile("\tPOP AX");
				writeIntoAssemblyFile("\tPOP DX");
				if($ADDOP->getText() == "+"){
					writeIntoAssemblyFile("\tADD AX, DX");

				}else if($ADDOP->getText() == "-"){
					writeIntoAssemblyFile("\tSUB DX, AX");
					writeIntoAssemblyFile("\tMOV AX, DX");

				}
				writeIntoAssemblyFile("\tPUSH AX");

				$info.set_line($se.info)
					->set_line($ADDOP->getText(), $ADDOP->getLine())
					->set_line($term.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": simple_expression : simple_expression ADDOP term\n\n"
					+ $info.line + "\n");
		  } 
		  ;
					
term returns [Info info, Param param]
	 :	ue=unary_expression {
				$param = $ue.param;
				// cout<<"term "<<$param.type<<" "<<$param.value<<endl;

				$info.set_line($ue.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": term : unary_expression\n\n"
					+ $info.line + "\n");
	 }
     |  tm=term MULOP ue=unary_expression {

				if($tm.param.type == "error" || $ue.param.type == "error"){
					Param t("error", "term", false, false);
					$param = t;
				}else if($tm.param.type == "void"){
					// cout<<2.1<<endl;
					Param t("error", "term", false, false);
					$param = t;
					writeIntoErrorFile("Error at Line " + std::to_string($tm.info.line_no) 
						+ ": term " + $tm.info.line + " cannot be void\n");
					SemanticErrorCount++;
					
				}else if($ue.param.type == "void"){
					// cout<<2.2<<endl;
					Param t("error", "term", false, false);
					$param = t;
					writeIntoErrorFile("Error at Line " + std::to_string($tm.info.line_no) 
						+ ": term " + $tm.info.line + " cannot be void\n");
					SemanticErrorCount++;
				
				}else if(($tm.param.type == "float" || $ue.param.type ==  "float")
							&& $MULOP->getText() == "%"){
					// cout<<2.3<<" "<<$tm.param.type<<" "<<$ue.param.type<<endl;
					Param t("error", "term", false, false);
					$param = t;
					// cout<<4.3<<" "<<$param.type<<endl;
					writeIntoErrorFile("Error at line " + std::to_string($MULOP->getLine()) 
						+ ": Non-Integer operand on modulus operator\n");
					SemanticErrorCount++;

				}else if(($tm.param.type == "float" || $ue.param.type ==  "float")
							&& $MULOP->getText() != "%"){
					Param t("float", "term", false, false);
					$param = t;			
				}else {
					// cout<<2.4<<endl;
					Param t("int", "term", false, false);
					$param = t;
				}

				writeIntoAssemblyFile("\tPOP CX");
				writeIntoAssemblyFile("\tPOP AX");
				writeIntoAssemblyFile("\tCWD");
				
				if($MULOP->getText() == "*"){
					
					writeIntoAssemblyFile("\tMUL CX");
					writeIntoAssemblyFile("\tPUSH AX");

				}else if($MULOP->getText() == "/"){
					
					writeIntoAssemblyFile("\tDIV CX");
					writeIntoAssemblyFile("\tPUSH AX");
				
				}else if($MULOP->getText() == "%"){

					writeIntoAssemblyFile("\tDIV CX");
					writeIntoAssemblyFile("\tPUSH DX");

				}

				$info.set_line($tm.info)
					->set_line($MULOP->getText(), $MULOP->getLine())
					->set_line($ue.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": term : term MULOP unary_expression\n\n"
					+ $info.line + "\n");
	 }
     ;

unary_expression returns [Info info, Param param]
		 : ADDOP ue=unary_expression {
				writeIntoAssemblyFile("\tPOP AX");
				if($ADDOP->getText() == "-"){
					writeIntoAssemblyFile("\tNEG AX");
				}
				writeIntoAssemblyFile("\tPUSH AX");

				if($ue.param.type == "error"){
					Param t("error", "unary_expression", false, false);
					$param = t;
				}else if($ue.param.type == "void"){
					Param t("error", "unary_expression", false, false);
					$param = t;
					writeIntoErrorFile("Error at Line " + std::to_string($ADDOP->getLine())
						+ ": unary_expression is void\n");
					SemanticErrorCount++;
					
				}else
					$param = $ue.param;
				$info.set_line($ADDOP->getText(), $ADDOP->getLine())
					->set_line($ue.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": unary_expression : ADDOP unary_expression\n\n"
					+ $info.line + "\n");
		 }	  
		 | NOT ue=unary_expression {
				if($ue.param.type == "error"){
					Param t("error", "unary_expression", false, false);
					$param = t;
				}else if($ue.param.type == "void"){
					Param t("error", "unary_expression", false, false);
					$param = t;
					writeIntoErrorFile("Error at Line " + std::to_string($ue.info.line_no) 
						+ ": unary_expression " + $ue.info.line + " cannot be void\n");
					SemanticErrorCount++;
				
				}else
					$param = $ue.param;

				$info.set_line($NOT->getText(), $NOT->getLine())
					->set_line($ue.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": unary_expression : NOT unary_expression\n\n"
					+ $info.line + "\n");
		 } 
		 | factor {
				$param = $factor.param;
				// cout<<"factor "<<$param.type<<" "<<$param.value<<endl;

				$info.set_line($factor.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": unary_expression : factor\n\n"
					+ $info.line + "\n");
	 	 } 
		 ;
	
factor	returns [Info info, Param param]
    : variable {
				$param = $variable.param;

				SymbolInfo *temp = symbolTable.Look_Up($variable.param.name);
				cout << 5.4 << $variable.param.name << endl;
				if(temp != NULL){
					if(temp->get_scope() == 1){
						if(temp->get_is_array()){
							writeIntoAssemblyFile("\tPOP AX");
							writeIntoAssemblyFile("\tCWD");
							writeIntoAssemblyFile("\tMOV CX, 2");
							writeIntoAssemblyFile("\tMUL CX");
							writeIntoAssemblyFile("\tMOV BX, AX");
							writeIntoAssemblyFile("\tMOV AX, " + temp->get_variable_name() + "[BX]");

						}else{
							writeIntoAssemblyFile("\tMOV AX, " + $variable.param.name);
						}
						writeIntoAssemblyFile("\tPUSH AX");
					}else{
						if(temp->get_is_argument()){
							writeIntoAssemblyFile("\tMOV AX, [BP+" + std::to_string((temp->get_total_parameter() + 2 - temp->get_info_no())*2) + "]");
						
						}else if(temp->get_is_array()){
							writeIntoAssemblyFile("\tPOP AX");
							writeIntoAssemblyFile("\tCWD");
							writeIntoAssemblyFile("\tMOV CX, 2");
							writeIntoAssemblyFile("\tMUL CX");
							writeIntoAssemblyFile("\tMOV BX, " + std::to_string(temp->get_variable_offset()));
							writeIntoAssemblyFile("\tSUB BX, AX");
							writeIntoAssemblyFile("\tMOV SI, BX");
							writeIntoAssemblyFile("\tNEG SI");
							writeIntoAssemblyFile("\tMOV AX, [BP+SI]");

						}else{
							cout<< "curr param count " << symbolTable.get_curr_parameter_count() << endl;
							writeIntoAssemblyFile("\tMOV AX, [BP-" + std::to_string(temp->get_variable_offset()) + "]");

						}
						writeIntoAssemblyFile("\tPUSH AX");
					}
				}

				$info.set_line($variable.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": factor : variable\n\n"
					+ $info.line + "\n");
	} 
	| ID LPAREN argument_list RPAREN {
				SymbolInfo *temp = symbolTable.Look_Up($ID->getText());

				if(temp == NULL){
					Param t("error", $ID->getText(), false, false);
					$param = t;
					writeIntoErrorFile("Error at line " + std::to_string($ID->getLine()) 
						+ ": No function named " + $ID->getText() + " found\n");
					syntaxErrorCount++;
				
				}else{
					if(!temp->get_is_func()){
						Param t("error", $ID->getText(), false, false);
						$param = t;
						writeIntoErrorFile("Error at line " + std::to_string($ID->getLine()) 
							+ ": " + $ID->getText() + " is not a function\n");
						SemanticErrorCount++;
						
					}else{
						Param t(temp->get_type_specifier(), temp->get_variable_name(), false, true);
						$param = t;

						writeIntoAssemblyFile("\tCALL " + $ID->getText());
						writeIntoAssemblyFile("\tPUSH AX");

					}
				}

				$info.set_line($ID->getText(), $ID->getLine())
					->set_line("(", $LPAREN->getLine())
					->set_line($argument_list.info)
					->set_line(")", $RPAREN->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": factor : ID LPAREN argument_list RPAREN\n\n"
					+ $info.line + "\n");
	}
	| LPAREN e=expression RPAREN {
				$param = $e.param;
				$info.set_line("(", $LPAREN->getLine())
					->set_line($e.info)
					->set_line(")", $RPAREN->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": factor : LPAREN expression RPAREN\n\n"
					+ $info.line + "\n");
	}
	| CONST_INT {
			writeIntoAssemblyFile("\tPUSH " + $CONST_INT->getText());

			$param.type = "int";
			$param.value = $CONST_INT->getText();
			$info.set_line($CONST_INT->getText(), $CONST_INT->getLine());
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": factor : CONST_INT\n\n"
				+ $info.line + "\n");
	} 
	| CONST_FLOAT {
			writeIntoAssemblyFile("\tPUSH " + $CONST_FLOAT->getText());

			$param.type = "float";
			$param.value = $CONST_FLOAT->getText();
			$info.set_line($CONST_FLOAT->getText(), $CONST_FLOAT->getLine());
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": factor : CONST_FLOAT\n\n"
				+ $info.line + "\n");
	}
	| var=variable INCOP {
			SymbolInfo *temp = symbolTable.Look_Up($variable.param.name);
			cout<<5.5<<endl;

			if(temp != NULL){
				if(temp->get_scope() == 1){
					if(temp->get_is_array()){
						writeIntoAssemblyFile("\tPOP AX");
						writeIntoAssemblyFile("\tCWD");
						writeIntoAssemblyFile("\tMOV CX, 2");
						writeIntoAssemblyFile("\tMUL CX");
						writeIntoAssemblyFile("\tMOV BX, AX");
						writeIntoAssemblyFile("\tMOV AX, " + temp->get_variable_name() + "[BX]");

					}else{
						writeIntoAssemblyFile("\tMOV AX, " + $variable.param.name);

					}
					
					writeIntoAssemblyFile("\tPUSH AX");
					writeIntoAssemblyFile("\tADD AX, 1");
					
					if(temp->get_is_array()){
						writeIntoAssemblyFile("\tMOV " + temp->get_variable_name() + "[BX], AX");

					}else{
						writeIntoAssemblyFile("\tMOV " + $var.param.name + ", AX");
					}

				}else{
					if(temp->get_is_argument()){
						writeIntoAssemblyFile("\tMOV AX, [BP+" + std::to_string((temp->get_total_parameter() + 2 - temp->get_info_no())*2) + "]");
					
					}else if(temp->get_is_array()){
						writeIntoAssemblyFile("\tPOP AX");
						writeIntoAssemblyFile("\tCWD");
						writeIntoAssemblyFile("\tMOV CX, 2");
						writeIntoAssemblyFile("\tMUL CX");
						writeIntoAssemblyFile("\tMOV BX, " + std::to_string(temp->get_variable_offset()));
						writeIntoAssemblyFile("\tSUB BX, AX");
						writeIntoAssemblyFile("\tMOV SI, BX");
						writeIntoAssemblyFile("\tNEG SI");
						writeIntoAssemblyFile("\tMOV AX, [BP+SI]");

					}else{
						cout<< "curr param count " << symbolTable.get_curr_parameter_count() << endl;
						writeIntoAssemblyFile("\tMOV AX, [BP-" + std::to_string(temp->get_variable_offset()) + "]");

					}

					writeIntoAssemblyFile("\tPUSH AX");
					writeIntoAssemblyFile("\tADD AX, 1");
					
					if(temp->get_is_argument()){
						writeIntoAssemblyFile("\tMOV [BP+" + std::to_string((temp->get_total_parameter() + 2 - temp->get_info_no())*2) + "], AX");
					
					}else if(temp->get_is_array()){
						writeIntoAssemblyFile("\tMOV [BP+SI], AX");

					}else{
						cout << "total para " << temp->get_total_parameter() << " info no " << temp->get_info_no() <<endl;
						writeIntoAssemblyFile("\tMOV [BP-" + std::to_string(temp->get_variable_offset()) + "], AX");

					}

				}

			}

			if($variable.param.type == "error"){
				Param t("error", "variable", false, false);
				$param = t;
			}else if($variable.param.type == "void"){
				Param t("error", "variable", false, false);
				$param = t;
				writeIntoErrorFile("Error at Line " 
					+ std::to_string($variable.info.line_no) + ": Can not increment void variable "
					+ $variable.info.line + "\n");
				SemanticErrorCount++;
				
			}else{
				
				$param = $variable.param;
			}
			$info.set_line($variable.info)
				->set_line($INCOP->getText(), $INCOP->getLine());
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": factor : variable INCOP\n\n"
				+ $info.line + "\n");
	} 
	| var=variable DECOP {
			SymbolInfo *temp = symbolTable.Look_Up($variable.param.name);

			if(temp != NULL){

				if(temp->get_scope() == 1){
					if(temp->get_is_array()){
						writeIntoAssemblyFile("\tPOP AX");
						writeIntoAssemblyFile("\tCWD");
						writeIntoAssemblyFile("\tMOV CX, 2");
						writeIntoAssemblyFile("\tMUL CX");
						writeIntoAssemblyFile("\tMOV BX, AX");
						writeIntoAssemblyFile("\tMOV AX, " + temp->get_variable_name() + "[BX]");

					}else{
						writeIntoAssemblyFile("\tMOV AX, " + $variable.param.name);

					}

					writeIntoAssemblyFile("\tPUSH AX");
					
					writeIntoAssemblyFile("\tSUB AX, 1");
					if(temp->get_is_array()){
						writeIntoAssemblyFile("\tMOV " + temp->get_variable_name() + "[BX], AX");

					}else{
						writeIntoAssemblyFile("\tMOV " + $var.param.name + ", AX");
					}

				}else{
					if(temp->get_is_argument()){
						writeIntoAssemblyFile("\tMOV AX, [BP+" + std::to_string((temp->get_total_parameter() + 2 - temp->get_info_no())*2) + "]");
					
					}else if(temp->get_is_array()){
						writeIntoAssemblyFile("\tPOP AX");
						writeIntoAssemblyFile("\tCWD");
						writeIntoAssemblyFile("\tMOV CX, 2");
						writeIntoAssemblyFile("\tMUL CX");
						writeIntoAssemblyFile("\tMOV BX, " + std::to_string(temp->get_variable_offset()));
						writeIntoAssemblyFile("\tSUB BX, AX");
						writeIntoAssemblyFile("\tMOV SI, BX");
						writeIntoAssemblyFile("\tNEG SI");
						writeIntoAssemblyFile("\tMOV AX, [BP+SI]");

					}else{
						cout<< "curr param count " << symbolTable.get_curr_parameter_count() << endl;
						writeIntoAssemblyFile("\tMOV AX, [BP-" + std::to_string(temp->get_variable_offset()) + "]");

					}
					writeIntoAssemblyFile("\tPUSH AX");
					
					writeIntoAssemblyFile("\tSUB AX, 1");
					if(temp->get_is_argument()){
						writeIntoAssemblyFile("\tMOV [BP+" + std::to_string((temp->get_total_parameter() + 2 - temp->get_info_no())*2) + "], AX");
					
					}else if(temp->get_is_array()){
						writeIntoAssemblyFile("\tMOV [BP+SI], AX");

					}else{
						cout << "total para " << temp->get_total_parameter() << " info no " << temp->get_info_no() <<endl;
						writeIntoAssemblyFile("\tMOV [BP-" + std::to_string(temp->get_variable_offset()) + "], AX");

					}

				}

			}

			if($variable.param.type == "error"){
				Param t("error", "variable", false, false);
				$param = t;

			}if($variable.param.type == "void"){
				Param t("error", "variable", false, false);
				$param = t;
				writeIntoErrorFile("Error at Line " 
					+ std::to_string($variable.info.line_no) + ": Can not decrement void variable "
					+ $variable.info.line + "\n");
				SemanticErrorCount++;

			}else{
				$param = $variable.param;
			
			}

			$info.set_line($variable.info)
				->set_line($DECOP->getText(), $DECOP->getLine());
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": factor : variable DECOP\n\n"
				+ $info.line + "\n");
	}
	;
	
argument_list returns [Info info]
		: arguments {
				$info.set_line($arguments.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": argument_list : arguments\n\n"
					+ $info.line + "\n");

		}
		|
		;
	
arguments returns [Info info]
		  : args=arguments COMMA le=logic_expression {
				// actually this writeIntoAssemblyFile is not needed as POP and PUSH are 
				// opposite actions, and they nullify each others actions
				// if used sequentially
				writeIntoAssemblyFile("\tPOP AX"); 
				writeIntoAssemblyFile("\tPUSH AX");

				$info.set_line($args.info)
					->set_line($COMMA->getText(), $COMMA->getLine())
					->set_line($le.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": arguments : arguments COMMA logic_expression\n\n"
					+ $info.line + "\n");

		  }
	      | le=logic_expression {
				// actually this writeIntoAssemblyFile is not needed as POP and PUSH are 
				// opposite actions, and they nullify each others actions
				// if used sequentially
				writeIntoAssemblyFile("\tPOP AX");
				writeIntoAssemblyFile("\tPUSH AX");

				$info.set_line($le.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": arguments : logic_expression\n\n"
					+ $info.line + "\n");

		  }
	      ;
