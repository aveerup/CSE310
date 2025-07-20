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

	SymbolTable symbolTable = SymbolTable(7, &parserLogFile, "SDBM");
	int in_func_check = 0;
	int SemanticErrorCount = 0;
	int in_loop_check = 0;

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

}


start
	: program {
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
						symbolTable.Enter_Scope();
						in_func_check = 1;

						for(int i = 0; i<$pl.params.size(); i++){
						std::cout<<i<<" 1.1 "<<$pl.params[i].name<<endl;
						symbolTable.Insert($pl.params[i].name, "ID", $t.info.line);
				}
					}else{
						writeIntoparserLogFile("Error at Line " + std::to_string($ID->getLine())
							+ ": Multiple declaration of function " + $ID->getText() + "\n");
						writeIntoErrorFile("Error at Line " + std::to_string($ID->getLine())
							+ ": Multiple declaration of function " + $ID->getText() + "\n");
					}
				}
			}else{
				symbolTable.Insert($ID->getText(), "ID", $t.info.line, false, true, true);
				symbolTable.Enter_Scope();
				in_func_check = 1;
			
				for(int i = 0; i<$pl.params.size(); i++){
					std::cout<<i<<" 1.1 "<<$pl.params[i].name<<endl;
					symbolTable.Insert($pl.params[i].name, "ID", $t.info.line);
				}
			}
			
			
		}
		 cs=compound_statement {
			if(in_func_check == 1){
				symbolTable.Exit_Scope();
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
			in_func_check = 1;
		}  
		cs=compound_statement {
			if(in_func_check == 1){
				symbolTable.Exit_Scope();
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
			std::cout<<p.type<<" "<<p.name<<endl;
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
				if(in_func_check == 0)
					symbolTable.Enter_Scope();
				in_func_check = 0;
			} 
			ss=statements RCURL {
				$info.set_line($LCURL->getText(), $LCURL->getLine(), 0, 1)
					->set_line($ss.info)
					->set_line($RCURL->getText(), $RCURL->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": compound_statement : LCURL statements RCURL\n\n"
					+ $info.line + "\n");
					symbolTable.Print_All();
					symbolTable.Exit_Scope();
			}
 		    | LCURL RCURL {
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
			cout<<i<<" 1.2 "<<$dl.IDs[i].name<<endl;
			bool inserted = symbolTable.Insert($dl.IDs[i].name, "ID", $t.info.line, $dl.IDs[i].is_array);
			if(!inserted){
				writeIntoparserLogFile("Error at line " + std::to_string($sm->getLine()) 
					+ ": Multiple declaration of " + $dl.IDs[i].name + "\n");
				writeIntoErrorFile("Error at line " + std::to_string($sm->getLine()) 
					+ ": Multiple declaration of " + $dl.IDs[i].name + "\n");
				syntaxErrorCount++;
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
				$IDs.push_back(Param($ID->getText(), true));
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
				$IDs.push_back(Param($ID->getText(), true));
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
	   | ss=statements s=statement {
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
	  | FOR LPAREN es1=expression_statement es2=expression_statement e=expression RPAREN {
			in_loop_check ++;
	  } s=statement {
				if(in_loop_check > 0)
					in_loop_check--;
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
	  | IF LPAREN e=expression RPAREN s=statement {
				$info.set_line("if", $IF->getLine());
				$info.set_line("(", $LPAREN->getLine());
				$info.set_line($e.info);
				$info.set_line(")", $RPAREN->getLine());
				$info.set_line($s.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": statement : IF LPAREN expression RPAREN statement\n\n"
					+ $info.line + "\n");
	   }
	  | IF LPAREN e=expression RPAREN s1=statement ELSE s2=statement {
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
	  | WHILE LPAREN e=expression RPAREN{
			in_loop_check++;
	  } s=statement {
				if(in_loop_check>0){
					in_loop_check--;
				}
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
		}compound_statement WHILE LPAREN expression RPAREN  SEMICOLON{
			if(in_loop_check>0){
					in_loop_check--;
				}
		} 
	  | PRINTLN LPAREN ID RPAREN SEMICOLON {
				cout<<"5.5 PRINTLN "<<$PRINTLN->getText()<<endl;
				SymbolInfo *temp = symbolTable.Look_Up($ID->getText());
				if(temp == NULL){
					writeIntoparserLogFile("Error at line " + std::to_string($ID->getLine()) 
						+ ": Undeclared variable " + $ID->getText() + "\n");
					writeIntoErrorFile("Error at line " + std::to_string($ID->getLine()) 
						+ ": Undeclared variable " + $ID->getText() + "\n");
					syntaxErrorCount++;
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

		if(temp == NULL){
			Param t($ID->getText());
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
		}

		$info.set_line($ID->getText(), $ID->getLine());
		writeIntoparserLogFile("Line " + std::to_string($info.line_no)
			+ ": variable : ID\n\n"
			+ $info.line + "\n");
	 } 		
	 | ID LTHIRD e=expression RTHIRD {
		SymbolInfo *temp = symbolTable.Look_Up($ID->getText());

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
	|  
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
			cout<<"ASSIGNOP "<<$param.type<<" "<<endl;
			cout<<"ASSIGNOP "<<$le.param.type<<" "<<endl;

			SymbolInfo *temp = symbolTable.Look_Up($var.param.name);

			if(temp == NULL){
				Param t("error", $var.param.name, false, false);
				$param = t;
				writeIntoparserLogFile("Error at line " + std::to_string($ASSIGNOP->getLine()) 
					+ ": Undeclared variable " + $var.param.name + "\n");
				writeIntoErrorFile("Error at line " + std::to_string($ASSIGNOP->getLine()) 
					+ ": Undeclared variable " + $var.param.name + "\n");
				syntaxErrorCount++;
			}else{
				Param t(temp->get_type_specifier(), temp->get_variable_name(), temp->get_is_array(), temp->get_is_func());
				$param = t;
			}

			if($variable.param.type != $le.param.type 
				&& $var.param.type != "error"
				&& $le.param.type != "error"
				&& !($var.param.type == "bool" && $le.param.type == "int")
				&& !($var.param.type == "int" && $le.param.type == "bool")){

				cout<<"ASSIGNOP1 "<<$var.param.type<<" "<<$var.info.line<<endl;
				cout<<"ASSIGNOP1 "<<$le.param.type<<" "<<$le.info.line<<endl;
				writeIntoErrorFile("Error at line " + std::to_string($ASSIGNOP->getLine()) 
					+ ": Type Mismatch\n");
				SemanticErrorCount++;
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
				cout<<"logic_expression "<<$param.type<<" "<<$param.value<<endl;

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
				cout<<"rel "<<$param.type<<" "<<$param.value<<endl;

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
				cout<<"simple_expression "<<$param.type<<" "<<$term.info.line<<endl;


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
				cout<<"term "<<$param.type<<" "<<$param.value<<endl;

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
					cout<<2.1<<endl;
					Param t("error", "term", false, false);
					$param = t;
					writeIntoErrorFile("Error at Line " + std::to_string($tm.info.line_no) 
						+ ": term " + $tm.info.line + " cannot be void\n");
					SemanticErrorCount++;
					
				}else if($ue.param.type == "void"){
					cout<<2.2<<endl;
					Param t("error", "term", false, false);
					$param = t;
					writeIntoErrorFile("Error at Line " + std::to_string($tm.info.line_no) 
						+ ": term " + $tm.info.line + " cannot be void\n");
					SemanticErrorCount++;
				
				}else if(($tm.param.type == "float" || $ue.param.type ==  "float")
							&& $MULOP->getText() == "%"){
					cout<<2.3<<" "<<$tm.param.type<<" "<<$ue.param.type<<endl;
					Param t("error", "term", false, false);
					$param = t;
					cout<<4.3<<" "<<$param.type<<endl;
					writeIntoErrorFile("Error at line " + std::to_string($MULOP->getLine()) 
						+ ": Non-Integer operand on modulus operator\n");
					SemanticErrorCount++;

				}else if(($tm.param.type == "float" || $ue.param.type ==  "float")
							&& $MULOP->getText() != "%"){
					Param t("float", "term", false, false);
					$param = t;			
				}else {
					cout<<2.4<<endl;
					Param t("int", "term", false, false);
					$param = t;
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
			cout<<"factor "<<$param.type<<" "<<$param.value<<endl;

			$info.set_line($factor.info);
			writeIntoparserLogFile("Line " + std::to_string($info.line_no)
				+ ": unary_expression : factor\n\n"
				+ $info.line + "\n");
	 	 } 
		 ;
	
factor	returns [Info info, Param param]
    : variable {
				$param = $variable.param;

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
				$param.type = "int";
				$param.value = $CONST_INT->getText();
				$info.set_line($CONST_INT->getText(), $CONST_INT->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": factor : CONST_INT\n\n"
					+ $info.line + "\n");
	} 
	| CONST_FLOAT {
				$param.type = "float";
				$param.value = $CONST_FLOAT->getText();
				$info.set_line($CONST_FLOAT->getText(), $CONST_FLOAT->getLine());
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": factor : CONST_FLOAT\n\n"
					+ $info.line + "\n");
	}
	| variable INCOP {
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
	| variable DECOP {
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
				$info.set_line($args.info)
					->set_line($COMMA->getText(), $COMMA->getLine())
					->set_line($le.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": arguments : arguments COMMA logic_expression\n\n"
					+ $info.line + "\n");
		  }
	      | le=logic_expression {
				$info.set_line($le.info);
				writeIntoparserLogFile("Line " + std::to_string($info.line_no)
					+ ": arguments : logic_expression\n\n"
					+ $info.line + "\n");
		  }
	      ;
