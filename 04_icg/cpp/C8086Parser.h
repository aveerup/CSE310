
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



// Generated from C8086Parser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  C8086Parser : public antlr4::Parser {
public:
  enum {
    LINE_COMMENT = 1, BLOCK_COMMENT = 2, STRING = 3, WS = 4, IF = 5, ELSE = 6, 
    FOR = 7, WHILE = 8, PRINTLN = 9, RETURN = 10, INT = 11, FLOAT = 12, 
    VOID = 13, BREAK = 14, CONTINUE = 15, DO = 16, LPAREN = 17, RPAREN = 18, 
    LCURL = 19, RCURL = 20, LTHIRD = 21, RTHIRD = 22, SEMICOLON = 23, COMMA = 24, 
    ADDOP = 25, SUBOP = 26, MULOP = 27, INCOP = 28, DECOP = 29, NOT = 30, 
    RELOP = 31, LOGICOP = 32, ASSIGNOP = 33, ID = 34, CONST_INT = 35, CONST_FLOAT = 36
  };

  enum {
    RuleStart = 0, RuleProgram = 1, RuleUnit = 2, RuleFunc_declaration = 3, 
    RuleFunc_definition = 4, RuleParameter_list_err = 5, RuleParameter_list = 6, 
    RuleCompound_statement = 7, RuleVar_declaration = 8, RuleDeclaration_list_err = 9, 
    RuleType_specifier = 10, RuleDeclaration_list = 11, RuleStatements = 12, 
    RuleStatement = 13, RuleExpression_statement = 14, RuleVariable = 15, 
    RuleExpression = 16, RuleExpression_err = 17, RuleLogic_expression = 18, 
    RuleRel_expression = 19, RuleSimple_expression = 20, RuleTerm = 21, 
    RuleUnary_expression = 22, RuleFactor = 23, RuleArgument_list = 24, 
    RuleArguments = 25
  };

  explicit C8086Parser(antlr4::TokenStream *input);

  C8086Parser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~C8086Parser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


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



  class StartContext;
  class ProgramContext;
  class UnitContext;
  class Func_declarationContext;
  class Func_definitionContext;
  class Parameter_list_errContext;
  class Parameter_listContext;
  class Compound_statementContext;
  class Var_declarationContext;
  class Declaration_list_errContext;
  class Type_specifierContext;
  class Declaration_listContext;
  class StatementsContext;
  class StatementContext;
  class Expression_statementContext;
  class VariableContext;
  class ExpressionContext;
  class Expression_errContext;
  class Logic_expressionContext;
  class Rel_expressionContext;
  class Simple_expressionContext;
  class TermContext;
  class Unary_expressionContext;
  class FactorContext;
  class Argument_listContext;
  class ArgumentsContext; 

  class  StartContext : public antlr4::ParserRuleContext {
  public:
    C8086Parser::ProgramContext *programContext = nullptr;
    StartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ProgramContext *program();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StartContext* start();

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    C8086Parser::ProgramContext *p = nullptr;
    C8086Parser::UnitContext *unitContext = nullptr;
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnitContext *unit();
    ProgramContext *program();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ProgramContext* program();
  ProgramContext* program(int precedence);
  class  UnitContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    C8086Parser::Var_declarationContext *vd = nullptr;
    C8086Parser::Func_declarationContext *fd = nullptr;
    C8086Parser::Func_definitionContext *fdn = nullptr;
    UnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Var_declarationContext *var_declaration();
    Func_declarationContext *func_declaration();
    Func_definitionContext *func_definition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UnitContext* unit();

  class  Func_declarationContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    C8086Parser::Type_specifierContext *t = nullptr;
    antlr4::Token *idToken = nullptr;
    antlr4::Token *lparenToken = nullptr;
    C8086Parser::Parameter_listContext *pl = nullptr;
    antlr4::Token *rparenToken = nullptr;
    antlr4::Token *semicolonToken = nullptr;
    Func_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();
    Type_specifierContext *type_specifier();
    Parameter_listContext *parameter_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Func_declarationContext* func_declaration();

  class  Func_definitionContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    C8086Parser::Type_specifierContext *t = nullptr;
    antlr4::Token *idToken = nullptr;
    antlr4::Token *lparenToken = nullptr;
    C8086Parser::Parameter_listContext *pl = nullptr;
    antlr4::Token *rparenToken = nullptr;
    C8086Parser::Compound_statementContext *cs = nullptr;
    C8086Parser::Parameter_list_errContext *plr = nullptr;
    Func_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    Type_specifierContext *type_specifier();
    Parameter_listContext *parameter_list();
    Compound_statementContext *compound_statement();
    Parameter_list_errContext *parameter_list_err();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Func_definitionContext* func_definition();

  class  Parameter_list_errContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    C8086Parser::Parameter_list_errContext *plr = nullptr;
    C8086Parser::Type_specifierContext *t = nullptr;
    antlr4::Token *idToken = nullptr;
    antlr4::Token *addopToken = nullptr;
    antlr4::Token *mulopToken = nullptr;
    antlr4::Token *commaToken = nullptr;
    Parameter_list_errContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ADDOP();
    Type_specifierContext *type_specifier();
    antlr4::tree::TerminalNode *MULOP();
    antlr4::tree::TerminalNode *COMMA();
    Parameter_list_errContext *parameter_list_err();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Parameter_list_errContext* parameter_list_err();
  Parameter_list_errContext* parameter_list_err(int precedence);
  class  Parameter_listContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    std::vector<Param> params;
    C8086Parser::Parameter_listContext *pl = nullptr;
    C8086Parser::Type_specifierContext *t = nullptr;
    antlr4::Token *idToken = nullptr;
    antlr4::Token *commaToken = nullptr;
    Parameter_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    Type_specifierContext *type_specifier();
    antlr4::tree::TerminalNode *COMMA();
    Parameter_listContext *parameter_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Parameter_listContext* parameter_list();
  Parameter_listContext* parameter_list(int precedence);
  class  Compound_statementContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    antlr4::Token *lcurlToken = nullptr;
    C8086Parser::StatementsContext *ss = nullptr;
    antlr4::Token *rcurlToken = nullptr;
    Compound_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LCURL();
    antlr4::tree::TerminalNode *RCURL();
    StatementsContext *statements();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Compound_statementContext* compound_statement();

  class  Var_declarationContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    C8086Parser::Type_specifierContext *t = nullptr;
    C8086Parser::Declaration_listContext *dl = nullptr;
    antlr4::Token *sm = nullptr;
    C8086Parser::Declaration_list_errContext *dlr = nullptr;
    Var_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_specifierContext *type_specifier();
    Declaration_listContext *declaration_list();
    antlr4::tree::TerminalNode *SEMICOLON();
    Declaration_list_errContext *declaration_list_err();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Var_declarationContext* var_declaration();

  class  Declaration_list_errContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    C8086Parser::Declaration_list_errContext *dlr = nullptr;
    antlr4::Token *id1 = nullptr;
    antlr4::Token *addopToken = nullptr;
    antlr4::Token *id2 = nullptr;
    antlr4::Token *mulopToken = nullptr;
    antlr4::Token *commaToken = nullptr;
    antlr4::Token *idToken = nullptr;
    Declaration_list_errContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ADDOP();
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    antlr4::tree::TerminalNode *MULOP();
    antlr4::tree::TerminalNode *COMMA();
    Declaration_list_errContext *declaration_list_err();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Declaration_list_errContext* declaration_list_err();
  Declaration_list_errContext* declaration_list_err(int precedence);
  class  Type_specifierContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    antlr4::Token *intToken = nullptr;
    antlr4::Token *floatToken = nullptr;
    antlr4::Token *voidToken = nullptr;
    Type_specifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *FLOAT();
    antlr4::tree::TerminalNode *VOID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Type_specifierContext* type_specifier();

  class  Declaration_listContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    vector<Param> IDs;
    C8086Parser::Declaration_listContext *dl = nullptr;
    antlr4::Token *idToken = nullptr;
    antlr4::Token *lthirdToken = nullptr;
    antlr4::Token *const_intToken = nullptr;
    antlr4::Token *rthirdToken = nullptr;
    antlr4::Token *commaToken = nullptr;
    Declaration_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LTHIRD();
    antlr4::tree::TerminalNode *CONST_INT();
    antlr4::tree::TerminalNode *RTHIRD();
    antlr4::tree::TerminalNode *COMMA();
    Declaration_listContext *declaration_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Declaration_listContext* declaration_list();
  Declaration_listContext* declaration_list(int precedence);
  class  StatementsContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    C8086Parser::StatementsContext *ss = nullptr;
    C8086Parser::StatementContext *s = nullptr;
    StatementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    StatementsContext *statements();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementsContext* statements();
  StatementsContext* statements(int precedence);
  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    C8086Parser::Var_declarationContext *vd = nullptr;
    C8086Parser::Expression_statementContext *es = nullptr;
    C8086Parser::Compound_statementContext *c = nullptr;
    antlr4::Token *forToken = nullptr;
    antlr4::Token *lparenToken = nullptr;
    C8086Parser::Expression_statementContext *es1 = nullptr;
    C8086Parser::Expression_statementContext *es2 = nullptr;
    C8086Parser::ExpressionContext *e = nullptr;
    antlr4::Token *rparenToken = nullptr;
    C8086Parser::StatementContext *s = nullptr;
    antlr4::Token *ifToken = nullptr;
    C8086Parser::StatementContext *s1 = nullptr;
    antlr4::Token *elseToken = nullptr;
    C8086Parser::StatementContext *s2 = nullptr;
    antlr4::Token *whileToken = nullptr;
    antlr4::Token *printlnToken = nullptr;
    antlr4::Token *idToken = nullptr;
    antlr4::Token *semicolonToken = nullptr;
    antlr4::Token *returnToken = nullptr;
    antlr4::Token *continueToken = nullptr;
    antlr4::Token *breakToken = nullptr;
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Var_declarationContext *var_declaration();
    std::vector<Expression_statementContext *> expression_statement();
    Expression_statementContext* expression_statement(size_t i);
    Compound_statementContext *compound_statement();
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ExpressionContext *expression();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *ELSE();
    antlr4::tree::TerminalNode *WHILE();
    antlr4::tree::TerminalNode *DO();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *PRINTLN();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *RETURN();
    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *BREAK();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementContext* statement();

  class  Expression_statementContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    antlr4::Token *semicolonToken = nullptr;
    C8086Parser::ExpressionContext *e = nullptr;
    C8086Parser::Expression_errContext *er = nullptr;
    Expression_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMICOLON();
    ExpressionContext *expression();
    Expression_errContext *expression_err();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expression_statementContext* expression_statement();

  class  VariableContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    Param param;
    antlr4::Token *idToken = nullptr;
    antlr4::Token *lthirdToken = nullptr;
    C8086Parser::ExpressionContext *e = nullptr;
    antlr4::Token *rthirdToken = nullptr;
    C8086Parser::Expression_errContext *er = nullptr;
    VariableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LTHIRD();
    antlr4::tree::TerminalNode *RTHIRD();
    ExpressionContext *expression();
    Expression_errContext *expression_err();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableContext* variable();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    Param param;
    C8086Parser::Logic_expressionContext *le = nullptr;
    C8086Parser::VariableContext *var = nullptr;
    C8086Parser::VariableContext *variableContext = nullptr;
    antlr4::Token *assignopToken = nullptr;
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Logic_expressionContext *logic_expression();
    antlr4::tree::TerminalNode *ASSIGNOP();
    VariableContext *variable();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExpressionContext* expression();

  class  Expression_errContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    C8086Parser::VariableContext *variableContext = nullptr;
    antlr4::Token *addopToken = nullptr;
    antlr4::Token *assignopToken = nullptr;
    C8086Parser::Logic_expressionContext *le = nullptr;
    antlr4::Token *mulopToken = nullptr;
    Expression_errContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableContext *variable();
    antlr4::tree::TerminalNode *ADDOP();
    antlr4::tree::TerminalNode *ASSIGNOP();
    Logic_expressionContext *logic_expression();
    antlr4::tree::TerminalNode *MULOP();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expression_errContext* expression_err();

  class  Logic_expressionContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    Param param;
    C8086Parser::Rel_expressionContext *re = nullptr;
    C8086Parser::Rel_expressionContext *re1 = nullptr;
    antlr4::Token *logicopToken = nullptr;
    C8086Parser::Rel_expressionContext *re2 = nullptr;
    Logic_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Rel_expressionContext *> rel_expression();
    Rel_expressionContext* rel_expression(size_t i);
    antlr4::tree::TerminalNode *LOGICOP();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Logic_expressionContext* logic_expression();

  class  Rel_expressionContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    Param param;
    C8086Parser::Simple_expressionContext *se = nullptr;
    C8086Parser::Simple_expressionContext *se1 = nullptr;
    antlr4::Token *relopToken = nullptr;
    C8086Parser::Simple_expressionContext *se2 = nullptr;
    Rel_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Simple_expressionContext *> simple_expression();
    Simple_expressionContext* simple_expression(size_t i);
    antlr4::tree::TerminalNode *RELOP();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Rel_expressionContext* rel_expression();

  class  Simple_expressionContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    Param param;
    C8086Parser::Simple_expressionContext *se = nullptr;
    C8086Parser::TermContext *termContext = nullptr;
    antlr4::Token *addopToken = nullptr;
    Simple_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TermContext *term();
    antlr4::tree::TerminalNode *ADDOP();
    Simple_expressionContext *simple_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Simple_expressionContext* simple_expression();
  Simple_expressionContext* simple_expression(int precedence);
  class  TermContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    Param param;
    C8086Parser::TermContext *tm = nullptr;
    C8086Parser::Unary_expressionContext *ue = nullptr;
    antlr4::Token *mulopToken = nullptr;
    TermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Unary_expressionContext *unary_expression();
    antlr4::tree::TerminalNode *MULOP();
    TermContext *term();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TermContext* term();
  TermContext* term(int precedence);
  class  Unary_expressionContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    Param param;
    antlr4::Token *addopToken = nullptr;
    C8086Parser::Unary_expressionContext *ue = nullptr;
    antlr4::Token *notToken = nullptr;
    C8086Parser::FactorContext *factorContext = nullptr;
    Unary_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ADDOP();
    Unary_expressionContext *unary_expression();
    antlr4::tree::TerminalNode *NOT();
    FactorContext *factor();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Unary_expressionContext* unary_expression();

  class  FactorContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    Param param;
    C8086Parser::VariableContext *variableContext = nullptr;
    antlr4::Token *idToken = nullptr;
    antlr4::Token *lparenToken = nullptr;
    C8086Parser::Argument_listContext *argument_listContext = nullptr;
    antlr4::Token *rparenToken = nullptr;
    C8086Parser::ExpressionContext *e = nullptr;
    antlr4::Token *const_intToken = nullptr;
    antlr4::Token *const_floatToken = nullptr;
    C8086Parser::VariableContext *var = nullptr;
    antlr4::Token *incopToken = nullptr;
    antlr4::Token *decopToken = nullptr;
    FactorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableContext *variable();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    Argument_listContext *argument_list();
    antlr4::tree::TerminalNode *RPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *CONST_INT();
    antlr4::tree::TerminalNode *CONST_FLOAT();
    antlr4::tree::TerminalNode *INCOP();
    antlr4::tree::TerminalNode *DECOP();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FactorContext* factor();

  class  Argument_listContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    C8086Parser::ArgumentsContext *argumentsContext = nullptr;
    Argument_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArgumentsContext *arguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Argument_listContext* argument_list();

  class  ArgumentsContext : public antlr4::ParserRuleContext {
  public:
    Info info;
    C8086Parser::ArgumentsContext *args = nullptr;
    C8086Parser::Logic_expressionContext *le = nullptr;
    antlr4::Token *commaToken = nullptr;
    ArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Logic_expressionContext *logic_expression();
    antlr4::tree::TerminalNode *COMMA();
    ArgumentsContext *arguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArgumentsContext* arguments();
  ArgumentsContext* arguments(int precedence);

  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool programSempred(ProgramContext *_localctx, size_t predicateIndex);
  bool parameter_list_errSempred(Parameter_list_errContext *_localctx, size_t predicateIndex);
  bool parameter_listSempred(Parameter_listContext *_localctx, size_t predicateIndex);
  bool declaration_list_errSempred(Declaration_list_errContext *_localctx, size_t predicateIndex);
  bool declaration_listSempred(Declaration_listContext *_localctx, size_t predicateIndex);
  bool statementsSempred(StatementsContext *_localctx, size_t predicateIndex);
  bool simple_expressionSempred(Simple_expressionContext *_localctx, size_t predicateIndex);
  bool termSempred(TermContext *_localctx, size_t predicateIndex);
  bool argumentsSempred(ArgumentsContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

