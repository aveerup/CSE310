
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




// Generated from C8086Parser.g4 by ANTLR 4.13.2


#include "C8086ParserListener.h"

#include "C8086Parser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct C8086ParserStaticData final {
  C8086ParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  C8086ParserStaticData(const C8086ParserStaticData&) = delete;
  C8086ParserStaticData(C8086ParserStaticData&&) = delete;
  C8086ParserStaticData& operator=(const C8086ParserStaticData&) = delete;
  C8086ParserStaticData& operator=(C8086ParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag c8086parserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<C8086ParserStaticData> c8086parserParserStaticData = nullptr;

void c8086parserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (c8086parserParserStaticData != nullptr) {
    return;
  }
#else
  assert(c8086parserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<C8086ParserStaticData>(
    std::vector<std::string>{
      "start", "program", "unit", "func_declaration", "func_definition", 
      "parameter_list_err", "parameter_list", "compound_statement", "var_declaration", 
      "declaration_list_err", "type_specifier", "declaration_list", "statements", 
      "statement", "expression_statement", "variable", "expression", "expression_err", 
      "logic_expression", "rel_expression", "simple_expression", "term", 
      "unary_expression", "factor", "argument_list", "arguments"
    },
    std::vector<std::string>{
      "", "", "", "", "", "'if'", "'else'", "'for'", "'while'", "", "'return'", 
      "'int'", "'float'", "'void'", "'break'", "'continue'", "'do'", "'('", 
      "')'", "'{'", "'}'", "'['", "']'", "';'", "','", "", "", "", "'++'", 
      "'--'", "'!'", "", "", "'='"
    },
    std::vector<std::string>{
      "", "LINE_COMMENT", "BLOCK_COMMENT", "STRING", "WS", "IF", "ELSE", 
      "FOR", "WHILE", "PRINTLN", "RETURN", "INT", "FLOAT", "VOID", "BREAK", 
      "CONTINUE", "DO", "LPAREN", "RPAREN", "LCURL", "RCURL", "LTHIRD", 
      "RTHIRD", "SEMICOLON", "COMMA", "ADDOP", "SUBOP", "MULOP", "INCOP", 
      "DECOP", "NOT", "RELOP", "LOGICOP", "ASSIGNOP", "ID", "CONST_INT", 
      "CONST_FLOAT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,36,520,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,1,0,1,0,1,0,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,5,1,64,8,1,10,1,12,1,67,9,1,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,3,2,78,8,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,3,3,95,8,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,
  	1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,3,4,122,8,4,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,139,8,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,5,5,147,8,5,10,5,12,5,150,9,5,1,6,1,6,1,6,1,6,
  	1,6,1,6,1,6,1,6,3,6,160,8,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,
  	6,5,6,173,8,6,10,6,12,6,176,9,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,
  	7,187,8,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,199,8,8,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,216,8,9,1,9,1,
  	9,1,9,1,9,5,9,222,8,9,10,9,12,9,225,9,9,1,10,1,10,1,10,1,10,1,10,1,10,
  	3,10,233,8,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,243,8,11,1,
  	11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,5,11,256,8,11,10,
  	11,12,11,259,9,11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,5,12,269,8,
  	12,10,12,12,12,272,9,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,3,13,344,8,13,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,3,14,356,8,14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,
  	1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,3,15,373,8,15,1,16,1,16,1,16,
  	1,16,1,16,1,16,1,16,1,16,3,16,383,8,16,1,17,1,17,1,17,1,17,1,17,1,17,
  	1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,
  	1,17,1,17,1,17,1,17,3,17,409,8,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,
  	1,18,3,18,419,8,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,429,8,
  	19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,5,20,440,8,20,10,20,12,
  	20,443,9,20,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,5,21,454,8,21,
  	10,21,12,21,457,9,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,
  	1,22,3,22,470,8,22,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,
  	1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,
  	1,23,1,23,3,23,498,8,23,1,24,1,24,1,24,1,24,3,24,504,8,24,1,25,1,25,1,
  	25,1,25,1,25,1,25,1,25,1,25,1,25,5,25,515,8,25,10,25,12,25,518,9,25,1,
  	25,0,9,2,10,12,18,22,24,40,42,50,26,0,2,4,6,8,10,12,14,16,18,20,22,24,
  	26,28,30,32,34,36,38,40,42,44,46,48,50,0,0,551,0,52,1,0,0,0,2,55,1,0,
  	0,0,4,77,1,0,0,0,6,94,1,0,0,0,8,121,1,0,0,0,10,138,1,0,0,0,12,159,1,0,
  	0,0,14,186,1,0,0,0,16,198,1,0,0,0,18,215,1,0,0,0,20,232,1,0,0,0,22,242,
  	1,0,0,0,24,260,1,0,0,0,26,343,1,0,0,0,28,355,1,0,0,0,30,372,1,0,0,0,32,
  	382,1,0,0,0,34,408,1,0,0,0,36,418,1,0,0,0,38,428,1,0,0,0,40,430,1,0,0,
  	0,42,444,1,0,0,0,44,469,1,0,0,0,46,497,1,0,0,0,48,503,1,0,0,0,50,505,
  	1,0,0,0,52,53,3,2,1,0,53,54,6,0,-1,0,54,1,1,0,0,0,55,56,6,1,-1,0,56,57,
  	3,4,2,0,57,58,6,1,-1,0,58,65,1,0,0,0,59,60,10,2,0,0,60,61,3,4,2,0,61,
  	62,6,1,-1,0,62,64,1,0,0,0,63,59,1,0,0,0,64,67,1,0,0,0,65,63,1,0,0,0,65,
  	66,1,0,0,0,66,3,1,0,0,0,67,65,1,0,0,0,68,69,3,16,8,0,69,70,6,2,-1,0,70,
  	78,1,0,0,0,71,72,3,6,3,0,72,73,6,2,-1,0,73,78,1,0,0,0,74,75,3,8,4,0,75,
  	76,6,2,-1,0,76,78,1,0,0,0,77,68,1,0,0,0,77,71,1,0,0,0,77,74,1,0,0,0,78,
  	5,1,0,0,0,79,80,3,20,10,0,80,81,5,34,0,0,81,82,5,17,0,0,82,83,3,12,6,
  	0,83,84,5,18,0,0,84,85,5,23,0,0,85,86,6,3,-1,0,86,95,1,0,0,0,87,88,3,
  	20,10,0,88,89,5,34,0,0,89,90,5,17,0,0,90,91,5,18,0,0,91,92,5,23,0,0,92,
  	93,6,3,-1,0,93,95,1,0,0,0,94,79,1,0,0,0,94,87,1,0,0,0,95,7,1,0,0,0,96,
  	97,3,20,10,0,97,98,5,34,0,0,98,99,5,17,0,0,99,100,3,12,6,0,100,101,5,
  	18,0,0,101,102,6,4,-1,0,102,103,3,14,7,0,103,104,6,4,-1,0,104,122,1,0,
  	0,0,105,106,3,20,10,0,106,107,5,34,0,0,107,108,5,17,0,0,108,109,5,18,
  	0,0,109,110,6,4,-1,0,110,111,3,14,7,0,111,112,6,4,-1,0,112,122,1,0,0,
  	0,113,114,3,20,10,0,114,115,5,34,0,0,115,116,5,17,0,0,116,117,3,10,5,
  	0,117,118,5,18,0,0,118,119,3,14,7,0,119,120,6,4,-1,0,120,122,1,0,0,0,
  	121,96,1,0,0,0,121,105,1,0,0,0,121,113,1,0,0,0,122,9,1,0,0,0,123,124,
  	6,5,-1,0,124,125,3,20,10,0,125,126,5,34,0,0,126,127,5,25,0,0,127,128,
  	6,5,-1,0,128,139,1,0,0,0,129,130,3,20,10,0,130,131,5,34,0,0,131,132,5,
  	27,0,0,132,133,6,5,-1,0,133,139,1,0,0,0,134,135,3,20,10,0,135,136,5,25,
  	0,0,136,137,6,5,-1,0,137,139,1,0,0,0,138,123,1,0,0,0,138,129,1,0,0,0,
  	138,134,1,0,0,0,139,148,1,0,0,0,140,141,10,4,0,0,141,142,5,24,0,0,142,
  	143,3,20,10,0,143,144,5,34,0,0,144,145,6,5,-1,0,145,147,1,0,0,0,146,140,
  	1,0,0,0,147,150,1,0,0,0,148,146,1,0,0,0,148,149,1,0,0,0,149,11,1,0,0,
  	0,150,148,1,0,0,0,151,152,6,6,-1,0,152,153,3,20,10,0,153,154,5,34,0,0,
  	154,155,6,6,-1,0,155,160,1,0,0,0,156,157,3,20,10,0,157,158,6,6,-1,0,158,
  	160,1,0,0,0,159,151,1,0,0,0,159,156,1,0,0,0,160,174,1,0,0,0,161,162,10,
  	4,0,0,162,163,5,24,0,0,163,164,3,20,10,0,164,165,5,34,0,0,165,166,6,6,
  	-1,0,166,173,1,0,0,0,167,168,10,3,0,0,168,169,5,24,0,0,169,170,3,20,10,
  	0,170,171,6,6,-1,0,171,173,1,0,0,0,172,161,1,0,0,0,172,167,1,0,0,0,173,
  	176,1,0,0,0,174,172,1,0,0,0,174,175,1,0,0,0,175,13,1,0,0,0,176,174,1,
  	0,0,0,177,178,5,19,0,0,178,179,6,7,-1,0,179,180,3,24,12,0,180,181,5,20,
  	0,0,181,182,6,7,-1,0,182,187,1,0,0,0,183,184,5,19,0,0,184,185,5,20,0,
  	0,185,187,6,7,-1,0,186,177,1,0,0,0,186,183,1,0,0,0,187,15,1,0,0,0,188,
  	189,3,20,10,0,189,190,3,22,11,0,190,191,5,23,0,0,191,192,6,8,-1,0,192,
  	199,1,0,0,0,193,194,3,20,10,0,194,195,3,18,9,0,195,196,5,23,0,0,196,197,
  	6,8,-1,0,197,199,1,0,0,0,198,188,1,0,0,0,198,193,1,0,0,0,199,17,1,0,0,
  	0,200,201,6,9,-1,0,201,202,5,34,0,0,202,203,5,25,0,0,203,204,5,34,0,0,
  	204,216,6,9,-1,0,205,206,5,34,0,0,206,207,5,25,0,0,207,216,6,9,-1,0,208,
  	209,5,34,0,0,209,210,5,27,0,0,210,211,5,34,0,0,211,216,6,9,-1,0,212,213,
  	5,34,0,0,213,214,5,27,0,0,214,216,6,9,-1,0,215,200,1,0,0,0,215,205,1,
  	0,0,0,215,208,1,0,0,0,215,212,1,0,0,0,216,223,1,0,0,0,217,218,10,1,0,
  	0,218,219,5,24,0,0,219,220,5,34,0,0,220,222,6,9,-1,0,221,217,1,0,0,0,
  	222,225,1,0,0,0,223,221,1,0,0,0,223,224,1,0,0,0,224,19,1,0,0,0,225,223,
  	1,0,0,0,226,227,5,11,0,0,227,233,6,10,-1,0,228,229,5,12,0,0,229,233,6,
  	10,-1,0,230,231,5,13,0,0,231,233,6,10,-1,0,232,226,1,0,0,0,232,228,1,
  	0,0,0,232,230,1,0,0,0,233,21,1,0,0,0,234,235,6,11,-1,0,235,236,5,34,0,
  	0,236,243,6,11,-1,0,237,238,5,34,0,0,238,239,5,21,0,0,239,240,5,35,0,
  	0,240,241,5,22,0,0,241,243,6,11,-1,0,242,234,1,0,0,0,242,237,1,0,0,0,
  	243,257,1,0,0,0,244,245,10,4,0,0,245,246,5,24,0,0,246,247,5,34,0,0,247,
  	256,6,11,-1,0,248,249,10,3,0,0,249,250,5,24,0,0,250,251,5,34,0,0,251,
  	252,5,21,0,0,252,253,5,35,0,0,253,254,5,22,0,0,254,256,6,11,-1,0,255,
  	244,1,0,0,0,255,248,1,0,0,0,256,259,1,0,0,0,257,255,1,0,0,0,257,258,1,
  	0,0,0,258,23,1,0,0,0,259,257,1,0,0,0,260,261,6,12,-1,0,261,262,3,26,13,
  	0,262,263,6,12,-1,0,263,270,1,0,0,0,264,265,10,1,0,0,265,266,3,26,13,
  	0,266,267,6,12,-1,0,267,269,1,0,0,0,268,264,1,0,0,0,269,272,1,0,0,0,270,
  	268,1,0,0,0,270,271,1,0,0,0,271,25,1,0,0,0,272,270,1,0,0,0,273,274,3,
  	16,8,0,274,275,6,13,-1,0,275,344,1,0,0,0,276,277,3,28,14,0,277,278,6,
  	13,-1,0,278,344,1,0,0,0,279,280,3,14,7,0,280,281,6,13,-1,0,281,344,1,
  	0,0,0,282,283,5,7,0,0,283,284,5,17,0,0,284,285,3,28,14,0,285,286,3,28,
  	14,0,286,287,3,32,16,0,287,288,5,18,0,0,288,289,6,13,-1,0,289,290,3,26,
  	13,0,290,291,6,13,-1,0,291,344,1,0,0,0,292,293,5,5,0,0,293,294,5,17,0,
  	0,294,295,3,32,16,0,295,296,5,18,0,0,296,297,3,26,13,0,297,298,6,13,-1,
  	0,298,344,1,0,0,0,299,300,5,5,0,0,300,301,5,17,0,0,301,302,3,32,16,0,
  	302,303,5,18,0,0,303,304,3,26,13,0,304,305,5,6,0,0,305,306,3,26,13,0,
  	306,307,6,13,-1,0,307,344,1,0,0,0,308,309,5,8,0,0,309,310,5,17,0,0,310,
  	311,3,32,16,0,311,312,5,18,0,0,312,313,6,13,-1,0,313,314,3,26,13,0,314,
  	315,6,13,-1,0,315,344,1,0,0,0,316,317,5,16,0,0,317,318,6,13,-1,0,318,
  	319,3,14,7,0,319,320,5,8,0,0,320,321,5,17,0,0,321,322,3,32,16,0,322,323,
  	5,18,0,0,323,324,5,23,0,0,324,325,6,13,-1,0,325,344,1,0,0,0,326,327,5,
  	9,0,0,327,328,5,17,0,0,328,329,5,34,0,0,329,330,5,18,0,0,330,331,5,23,
  	0,0,331,344,6,13,-1,0,332,333,5,10,0,0,333,334,3,32,16,0,334,335,5,23,
  	0,0,335,336,6,13,-1,0,336,344,1,0,0,0,337,338,5,15,0,0,338,339,5,23,0,
  	0,339,344,6,13,-1,0,340,341,5,14,0,0,341,342,5,23,0,0,342,344,6,13,-1,
  	0,343,273,1,0,0,0,343,276,1,0,0,0,343,279,1,0,0,0,343,282,1,0,0,0,343,
  	292,1,0,0,0,343,299,1,0,0,0,343,308,1,0,0,0,343,316,1,0,0,0,343,326,1,
  	0,0,0,343,332,1,0,0,0,343,337,1,0,0,0,343,340,1,0,0,0,344,27,1,0,0,0,
  	345,346,5,23,0,0,346,356,6,14,-1,0,347,348,3,32,16,0,348,349,5,23,0,0,
  	349,350,6,14,-1,0,350,356,1,0,0,0,351,352,3,34,17,0,352,353,5,23,0,0,
  	353,354,6,14,-1,0,354,356,1,0,0,0,355,345,1,0,0,0,355,347,1,0,0,0,355,
  	351,1,0,0,0,356,29,1,0,0,0,357,358,5,34,0,0,358,373,6,15,-1,0,359,360,
  	5,34,0,0,360,361,5,21,0,0,361,362,3,32,16,0,362,363,5,22,0,0,363,364,
  	6,15,-1,0,364,373,1,0,0,0,365,366,5,34,0,0,366,367,5,21,0,0,367,368,3,
  	34,17,0,368,369,5,22,0,0,369,370,6,15,-1,0,370,373,1,0,0,0,371,373,1,
  	0,0,0,372,357,1,0,0,0,372,359,1,0,0,0,372,365,1,0,0,0,372,371,1,0,0,0,
  	373,31,1,0,0,0,374,375,3,36,18,0,375,376,6,16,-1,0,376,383,1,0,0,0,377,
  	378,3,30,15,0,378,379,5,33,0,0,379,380,3,36,18,0,380,381,6,16,-1,0,381,
  	383,1,0,0,0,382,374,1,0,0,0,382,377,1,0,0,0,383,33,1,0,0,0,384,385,3,
  	30,15,0,385,386,5,25,0,0,386,387,5,33,0,0,387,388,3,36,18,0,388,389,6,
  	17,-1,0,389,409,1,0,0,0,390,391,3,30,15,0,391,392,5,33,0,0,392,393,5,
  	25,0,0,393,394,3,36,18,0,394,395,6,17,-1,0,395,409,1,0,0,0,396,397,3,
  	30,15,0,397,398,5,27,0,0,398,399,5,33,0,0,399,400,3,36,18,0,400,401,6,
  	17,-1,0,401,409,1,0,0,0,402,403,3,30,15,0,403,404,5,33,0,0,404,405,5,
  	27,0,0,405,406,3,36,18,0,406,407,6,17,-1,0,407,409,1,0,0,0,408,384,1,
  	0,0,0,408,390,1,0,0,0,408,396,1,0,0,0,408,402,1,0,0,0,409,35,1,0,0,0,
  	410,411,3,38,19,0,411,412,6,18,-1,0,412,419,1,0,0,0,413,414,3,38,19,0,
  	414,415,5,32,0,0,415,416,3,38,19,0,416,417,6,18,-1,0,417,419,1,0,0,0,
  	418,410,1,0,0,0,418,413,1,0,0,0,419,37,1,0,0,0,420,421,3,40,20,0,421,
  	422,6,19,-1,0,422,429,1,0,0,0,423,424,3,40,20,0,424,425,5,31,0,0,425,
  	426,3,40,20,0,426,427,6,19,-1,0,427,429,1,0,0,0,428,420,1,0,0,0,428,423,
  	1,0,0,0,429,39,1,0,0,0,430,431,6,20,-1,0,431,432,3,42,21,0,432,433,6,
  	20,-1,0,433,441,1,0,0,0,434,435,10,1,0,0,435,436,5,25,0,0,436,437,3,42,
  	21,0,437,438,6,20,-1,0,438,440,1,0,0,0,439,434,1,0,0,0,440,443,1,0,0,
  	0,441,439,1,0,0,0,441,442,1,0,0,0,442,41,1,0,0,0,443,441,1,0,0,0,444,
  	445,6,21,-1,0,445,446,3,44,22,0,446,447,6,21,-1,0,447,455,1,0,0,0,448,
  	449,10,1,0,0,449,450,5,27,0,0,450,451,3,44,22,0,451,452,6,21,-1,0,452,
  	454,1,0,0,0,453,448,1,0,0,0,454,457,1,0,0,0,455,453,1,0,0,0,455,456,1,
  	0,0,0,456,43,1,0,0,0,457,455,1,0,0,0,458,459,5,25,0,0,459,460,3,44,22,
  	0,460,461,6,22,-1,0,461,470,1,0,0,0,462,463,5,30,0,0,463,464,3,44,22,
  	0,464,465,6,22,-1,0,465,470,1,0,0,0,466,467,3,46,23,0,467,468,6,22,-1,
  	0,468,470,1,0,0,0,469,458,1,0,0,0,469,462,1,0,0,0,469,466,1,0,0,0,470,
  	45,1,0,0,0,471,472,3,30,15,0,472,473,6,23,-1,0,473,498,1,0,0,0,474,475,
  	5,34,0,0,475,476,5,17,0,0,476,477,3,48,24,0,477,478,5,18,0,0,478,479,
  	6,23,-1,0,479,498,1,0,0,0,480,481,5,17,0,0,481,482,3,32,16,0,482,483,
  	5,18,0,0,483,484,6,23,-1,0,484,498,1,0,0,0,485,486,5,35,0,0,486,498,6,
  	23,-1,0,487,488,5,36,0,0,488,498,6,23,-1,0,489,490,3,30,15,0,490,491,
  	5,28,0,0,491,492,6,23,-1,0,492,498,1,0,0,0,493,494,3,30,15,0,494,495,
  	5,29,0,0,495,496,6,23,-1,0,496,498,1,0,0,0,497,471,1,0,0,0,497,474,1,
  	0,0,0,497,480,1,0,0,0,497,485,1,0,0,0,497,487,1,0,0,0,497,489,1,0,0,0,
  	497,493,1,0,0,0,498,47,1,0,0,0,499,500,3,50,25,0,500,501,6,24,-1,0,501,
  	504,1,0,0,0,502,504,1,0,0,0,503,499,1,0,0,0,503,502,1,0,0,0,504,49,1,
  	0,0,0,505,506,6,25,-1,0,506,507,3,36,18,0,507,508,6,25,-1,0,508,516,1,
  	0,0,0,509,510,10,2,0,0,510,511,5,24,0,0,511,512,3,36,18,0,512,513,6,25,
  	-1,0,513,515,1,0,0,0,514,509,1,0,0,0,515,518,1,0,0,0,516,514,1,0,0,0,
  	516,517,1,0,0,0,517,51,1,0,0,0,518,516,1,0,0,0,31,65,77,94,121,138,148,
  	159,172,174,186,198,215,223,232,242,255,257,270,343,355,372,382,408,418,
  	428,441,455,469,497,503,516
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  c8086parserParserStaticData = std::move(staticData);
}

}

C8086Parser::C8086Parser(TokenStream *input) : C8086Parser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

C8086Parser::C8086Parser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  C8086Parser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *c8086parserParserStaticData->atn, c8086parserParserStaticData->decisionToDFA, c8086parserParserStaticData->sharedContextCache, options);
}

C8086Parser::~C8086Parser() {
  delete _interpreter;
}

const atn::ATN& C8086Parser::getATN() const {
  return *c8086parserParserStaticData->atn;
}

std::string C8086Parser::getGrammarFileName() const {
  return "C8086Parser.g4";
}

const std::vector<std::string>& C8086Parser::getRuleNames() const {
  return c8086parserParserStaticData->ruleNames;
}

const dfa::Vocabulary& C8086Parser::getVocabulary() const {
  return c8086parserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView C8086Parser::getSerializedATN() const {
  return c8086parserParserStaticData->serializedATN;
}


//----------------- StartContext ------------------------------------------------------------------

C8086Parser::StartContext::StartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C8086Parser::ProgramContext* C8086Parser::StartContext::program() {
  return getRuleContext<C8086Parser::ProgramContext>(0);
}


size_t C8086Parser::StartContext::getRuleIndex() const {
  return C8086Parser::RuleStart;
}

void C8086Parser::StartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStart(this);
}

void C8086Parser::StartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStart(this);
}

C8086Parser::StartContext* C8086Parser::start() {
  StartContext *_localctx = _tracker.createInstance<StartContext>(_ctx, getState());
  enterRule(_localctx, 0, C8086Parser::RuleStart);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(52);
    antlrcpp::downCast<StartContext *>(_localctx)->programContext = program(0);

    		writeIntoparserLogFile("Line " + std::to_string(antlrcpp::downCast<StartContext *>(_localctx)->programContext->info.line_no)
    			+ ": start : program\n");
    		symbolTable.Print_All();
    		writeIntoparserLogFile("Total lines: " + std::to_string(antlrcpp::downCast<StartContext *>(_localctx)->programContext->info.line_no));
    		writeIntoparserLogFile("Total number of errors: " + std::to_string(syntaxErrorCount + SemanticErrorCount));
    	
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProgramContext ------------------------------------------------------------------

C8086Parser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C8086Parser::UnitContext* C8086Parser::ProgramContext::unit() {
  return getRuleContext<C8086Parser::UnitContext>(0);
}

C8086Parser::ProgramContext* C8086Parser::ProgramContext::program() {
  return getRuleContext<C8086Parser::ProgramContext>(0);
}


size_t C8086Parser::ProgramContext::getRuleIndex() const {
  return C8086Parser::RuleProgram;
}

void C8086Parser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void C8086Parser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


C8086Parser::ProgramContext* C8086Parser::program() {
   return program(0);
}

C8086Parser::ProgramContext* C8086Parser::program(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C8086Parser::ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, parentState);
  C8086Parser::ProgramContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 2;
  enterRecursionRule(_localctx, 2, C8086Parser::RuleProgram, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(56);
    antlrcpp::downCast<ProgramContext *>(_localctx)->unitContext = unit();

    		_localctx->info.set_line(antlrcpp::downCast<ProgramContext *>(_localctx)->unitContext->info);
    		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
    			+ ": program : unit\n\n"
    			+ _localctx->info.line + "\n");
    	
    _ctx->stop = _input->LT(-1);
    setState(65);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ProgramContext>(parentContext, parentState);
        _localctx->p = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleProgram);
        setState(59);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(60);
        antlrcpp::downCast<ProgramContext *>(_localctx)->unitContext = unit();

                  		_localctx->info.set_line(antlrcpp::downCast<ProgramContext *>(_localctx)->p->info)
                  			->set_line(antlrcpp::downCast<ProgramContext *>(_localctx)->unitContext->info);
                  		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
                  			+ ": program : program unit\n\n"
                  			+ _localctx->info.line + "\n");
                  	 
      }
      setState(67);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- UnitContext ------------------------------------------------------------------

C8086Parser::UnitContext::UnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C8086Parser::Var_declarationContext* C8086Parser::UnitContext::var_declaration() {
  return getRuleContext<C8086Parser::Var_declarationContext>(0);
}

C8086Parser::Func_declarationContext* C8086Parser::UnitContext::func_declaration() {
  return getRuleContext<C8086Parser::Func_declarationContext>(0);
}

C8086Parser::Func_definitionContext* C8086Parser::UnitContext::func_definition() {
  return getRuleContext<C8086Parser::Func_definitionContext>(0);
}


size_t C8086Parser::UnitContext::getRuleIndex() const {
  return C8086Parser::RuleUnit;
}

void C8086Parser::UnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnit(this);
}

void C8086Parser::UnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnit(this);
}

C8086Parser::UnitContext* C8086Parser::unit() {
  UnitContext *_localctx = _tracker.createInstance<UnitContext>(_ctx, getState());
  enterRule(_localctx, 4, C8086Parser::RuleUnit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(77);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(68);
      antlrcpp::downCast<UnitContext *>(_localctx)->vd = var_declaration();

      		_localctx->info.set_line(antlrcpp::downCast<UnitContext *>(_localctx)->vd->info);
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": unit : var_declaration\n\n"
      			+ _localctx->info.line + "\n");
      	 
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(71);
      antlrcpp::downCast<UnitContext *>(_localctx)->fd = func_declaration();

      		_localctx->info.set_line(antlrcpp::downCast<UnitContext *>(_localctx)->fd->info);
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": unit : func_declaration\n\n"
      			+ _localctx->info.line + "\n");
      	 
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(74);
      antlrcpp::downCast<UnitContext *>(_localctx)->fdn = func_definition();

      		_localctx->info.set_line(antlrcpp::downCast<UnitContext *>(_localctx)->fdn->info);
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": unit : func_definition\n\n"
      			+ _localctx->info.line + "\n");
      	 
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_declarationContext ------------------------------------------------------------------

C8086Parser::Func_declarationContext::Func_declarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C8086Parser::Func_declarationContext::ID() {
  return getToken(C8086Parser::ID, 0);
}

tree::TerminalNode* C8086Parser::Func_declarationContext::LPAREN() {
  return getToken(C8086Parser::LPAREN, 0);
}

tree::TerminalNode* C8086Parser::Func_declarationContext::RPAREN() {
  return getToken(C8086Parser::RPAREN, 0);
}

tree::TerminalNode* C8086Parser::Func_declarationContext::SEMICOLON() {
  return getToken(C8086Parser::SEMICOLON, 0);
}

C8086Parser::Type_specifierContext* C8086Parser::Func_declarationContext::type_specifier() {
  return getRuleContext<C8086Parser::Type_specifierContext>(0);
}

C8086Parser::Parameter_listContext* C8086Parser::Func_declarationContext::parameter_list() {
  return getRuleContext<C8086Parser::Parameter_listContext>(0);
}


size_t C8086Parser::Func_declarationContext::getRuleIndex() const {
  return C8086Parser::RuleFunc_declaration;
}

void C8086Parser::Func_declarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunc_declaration(this);
}

void C8086Parser::Func_declarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunc_declaration(this);
}

C8086Parser::Func_declarationContext* C8086Parser::func_declaration() {
  Func_declarationContext *_localctx = _tracker.createInstance<Func_declarationContext>(_ctx, getState());
  enterRule(_localctx, 6, C8086Parser::RuleFunc_declaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(94);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(79);
      antlrcpp::downCast<Func_declarationContext *>(_localctx)->t = type_specifier();
      setState(80);
      antlrcpp::downCast<Func_declarationContext *>(_localctx)->idToken = match(C8086Parser::ID);
      setState(81);
      antlrcpp::downCast<Func_declarationContext *>(_localctx)->lparenToken = match(C8086Parser::LPAREN);
      setState(82);
      antlrcpp::downCast<Func_declarationContext *>(_localctx)->pl = parameter_list(0);
      setState(83);
      antlrcpp::downCast<Func_declarationContext *>(_localctx)->rparenToken = match(C8086Parser::RPAREN);
      setState(84);
      antlrcpp::downCast<Func_declarationContext *>(_localctx)->semicolonToken = match(C8086Parser::SEMICOLON);

      			SymbolInfo *temp = new SymbolInfo(antlrcpp::downCast<Func_declarationContext *>(_localctx)->idToken->getText(), "ID", antlrcpp::downCast<Func_declarationContext *>(_localctx)->t->info.line, false, true);
      			for(int i = 0; i<antlrcpp::downCast<Func_declarationContext *>(_localctx)->pl->params.size(); i++){
      				temp->set_extra_info(antlrcpp::downCast<Func_declarationContext *>(_localctx)->pl->params[i].name, "ID", antlrcpp::downCast<Func_declarationContext *>(_localctx)->pl->params[i].type, false, false);
      			}
      			symbolTable.Insert(temp);
      			_localctx->info.set_line(antlrcpp::downCast<Func_declarationContext *>(_localctx)->t->info, 1)
      				->set_line(antlrcpp::downCast<Func_declarationContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<Func_declarationContext *>(_localctx)->idToken->getLine())
      				->set_line("(", antlrcpp::downCast<Func_declarationContext *>(_localctx)->lparenToken->getLine())
      				->set_line(antlrcpp::downCast<Func_declarationContext *>(_localctx)->pl->info)
      				->set_line(")", antlrcpp::downCast<Func_declarationContext *>(_localctx)->rparenToken->getLine())
      				->set_line(";", antlrcpp::downCast<Func_declarationContext *>(_localctx)->semicolonToken->getLine(), 0, 1);
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n"
      				+ _localctx->info.line + "\n");
      	 	
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(87);
      antlrcpp::downCast<Func_declarationContext *>(_localctx)->t = type_specifier();
      setState(88);
      antlrcpp::downCast<Func_declarationContext *>(_localctx)->idToken = match(C8086Parser::ID);
      setState(89);
      antlrcpp::downCast<Func_declarationContext *>(_localctx)->lparenToken = match(C8086Parser::LPAREN);
      setState(90);
      antlrcpp::downCast<Func_declarationContext *>(_localctx)->rparenToken = match(C8086Parser::RPAREN);
      setState(91);
      antlrcpp::downCast<Func_declarationContext *>(_localctx)->semicolonToken = match(C8086Parser::SEMICOLON);

      			symbolTable.Insert(antlrcpp::downCast<Func_declarationContext *>(_localctx)->idToken->getText(), "ID", antlrcpp::downCast<Func_declarationContext *>(_localctx)->t->info.line, false, true);
      			_localctx->info.set_line(antlrcpp::downCast<Func_declarationContext *>(_localctx)->t->info, 1)
      				->set_line(antlrcpp::downCast<Func_declarationContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<Func_declarationContext *>(_localctx)->idToken->getLine())
      				->set_line("(", antlrcpp::downCast<Func_declarationContext *>(_localctx)->lparenToken->getLine())
      				->set_line(")", antlrcpp::downCast<Func_declarationContext *>(_localctx)->rparenToken->getLine())
      				->set_line(";", antlrcpp::downCast<Func_declarationContext *>(_localctx)->semicolonToken->getLine(), 0, 1);
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n\n"
      				+ _localctx->info.line + "\n");
      	 	
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_definitionContext ------------------------------------------------------------------

C8086Parser::Func_definitionContext::Func_definitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C8086Parser::Func_definitionContext::ID() {
  return getToken(C8086Parser::ID, 0);
}

tree::TerminalNode* C8086Parser::Func_definitionContext::LPAREN() {
  return getToken(C8086Parser::LPAREN, 0);
}

tree::TerminalNode* C8086Parser::Func_definitionContext::RPAREN() {
  return getToken(C8086Parser::RPAREN, 0);
}

C8086Parser::Type_specifierContext* C8086Parser::Func_definitionContext::type_specifier() {
  return getRuleContext<C8086Parser::Type_specifierContext>(0);
}

C8086Parser::Parameter_listContext* C8086Parser::Func_definitionContext::parameter_list() {
  return getRuleContext<C8086Parser::Parameter_listContext>(0);
}

C8086Parser::Compound_statementContext* C8086Parser::Func_definitionContext::compound_statement() {
  return getRuleContext<C8086Parser::Compound_statementContext>(0);
}

C8086Parser::Parameter_list_errContext* C8086Parser::Func_definitionContext::parameter_list_err() {
  return getRuleContext<C8086Parser::Parameter_list_errContext>(0);
}


size_t C8086Parser::Func_definitionContext::getRuleIndex() const {
  return C8086Parser::RuleFunc_definition;
}

void C8086Parser::Func_definitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunc_definition(this);
}

void C8086Parser::Func_definitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunc_definition(this);
}

C8086Parser::Func_definitionContext* C8086Parser::func_definition() {
  Func_definitionContext *_localctx = _tracker.createInstance<Func_definitionContext>(_ctx, getState());
  enterRule(_localctx, 8, C8086Parser::RuleFunc_definition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(121);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(96);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->t = type_specifier();
      setState(97);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken = match(C8086Parser::ID);
      setState(98);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->lparenToken = match(C8086Parser::LPAREN);
      setState(99);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->pl = parameter_list(0);
      setState(100);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->rparenToken = match(C8086Parser::RPAREN);

      			SymbolInfo *temp = symbolTable.Look_Up(antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getText());
      			if(temp != NULL){
      				if(!temp->get_is_func()){
      					writeIntoparserLogFile("Error at line" + std::to_string(antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getLine()) 
      						+ ": Multiple declaration of " + antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getText() + "\n");
      					writeIntoErrorFile("Error at line" + std::to_string(antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getLine()) 
      						+ ": Multiple declaration of " + antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getText() + "\n");
      				}else{
      					bool same = temp->get_type_specifier() == antlrcpp::downCast<Func_definitionContext *>(_localctx)->t->info.line;
      					int i = 0;
      					SymbolInfo *temp1 = temp;
      					while(temp1->get_extra_info()){
      						if(i >= antlrcpp::downCast<Func_definitionContext *>(_localctx)->pl->params.size()){
      							same = false;
      							break;
      						}
      						same &= temp1->get_extra_info()->get_variable_name() == antlrcpp::downCast<Func_definitionContext *>(_localctx)->pl->params[i].name;
      						same &= temp1->get_extra_info()->get_type_specifier() == antlrcpp::downCast<Func_definitionContext *>(_localctx)->pl->params[i].type;

      						temp1 = temp1->get_extra_info();
      						i++;
      					}
      					if(i<antlrcpp::downCast<Func_definitionContext *>(_localctx)->pl->params.size()){
      						same = false;
      					}
      					if(same && temp->get_is_defined()){
      						writeIntoparserLogFile("Error at Line " + std::to_string(antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getLine())
      							+ ": Multiple definition of function " + antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getText() + "\n");
      						writeIntoErrorFile("Error at Line " + std::to_string(antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getLine())
      							+ ": Multiple definition of function " + antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getText() + "\n");
      					}else if(same && !temp->get_is_defined()){
      						temp->set_is_defined(true);
      						symbolTable.Enter_Scope();
      						in_func_check = 1;

      						for(int i = 0; i<antlrcpp::downCast<Func_definitionContext *>(_localctx)->pl->params.size(); i++){
      						std::cout<<i<<" 1.1 "<<antlrcpp::downCast<Func_definitionContext *>(_localctx)->pl->params[i].name<<endl;
      						symbolTable.Insert(antlrcpp::downCast<Func_definitionContext *>(_localctx)->pl->params[i].name, "ID", antlrcpp::downCast<Func_definitionContext *>(_localctx)->t->info.line);
      				}
      					}else{
      						writeIntoparserLogFile("Error at Line " + std::to_string(antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getLine())
      							+ ": Multiple declaration of function " + antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getText() + "\n");
      						writeIntoErrorFile("Error at Line " + std::to_string(antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getLine())
      							+ ": Multiple declaration of function " + antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getText() + "\n");
      					}
      				}
      			}else{
      				symbolTable.Insert(antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getText(), "ID", antlrcpp::downCast<Func_definitionContext *>(_localctx)->t->info.line, false, true, true);
      				symbolTable.Enter_Scope();
      				in_func_check = 1;
      			
      				for(int i = 0; i<antlrcpp::downCast<Func_definitionContext *>(_localctx)->pl->params.size(); i++){
      					std::cout<<i<<" 1.1 "<<antlrcpp::downCast<Func_definitionContext *>(_localctx)->pl->params[i].name<<endl;
      					symbolTable.Insert(antlrcpp::downCast<Func_definitionContext *>(_localctx)->pl->params[i].name, "ID", antlrcpp::downCast<Func_definitionContext *>(_localctx)->t->info.line);
      				}
      			}
      			
      			
      		
      setState(102);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->cs = compound_statement();

      			if(in_func_check == 1){
      				symbolTable.Exit_Scope();
      				in_func_check = 0;
      			}
      			
      			_localctx->info.set_line(antlrcpp::downCast<Func_definitionContext *>(_localctx)->t->info, 1)
      				->set_line(antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getLine())
      				->set_line("(", antlrcpp::downCast<Func_definitionContext *>(_localctx)->lparenToken->getLine())
      				->set_line(antlrcpp::downCast<Func_definitionContext *>(_localctx)->pl->info)
      				->set_line(")", antlrcpp::downCast<Func_definitionContext *>(_localctx)->rparenToken->getLine())
      				->set_line(antlrcpp::downCast<Func_definitionContext *>(_localctx)->cs->info, 0, 1);
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n"
      				+ _localctx->info.line + "\n");
      	 	
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(105);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->t = type_specifier();
      setState(106);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken = match(C8086Parser::ID);
      setState(107);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->lparenToken = match(C8086Parser::LPAREN);
      setState(108);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->rparenToken = match(C8086Parser::RPAREN);

      			symbolTable.Insert(antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getText(), "ID", antlrcpp::downCast<Func_definitionContext *>(_localctx)->t->info.line, false, true);
                  symbolTable.Enter_Scope();
      			in_func_check = 1;
      		
      setState(110);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->cs = compound_statement();

      			if(in_func_check == 1){
      				symbolTable.Exit_Scope();
      				in_func_check = 0;
      			}

      			_localctx->info.set_line(antlrcpp::downCast<Func_definitionContext *>(_localctx)->t->info, 1)
      				->set_line(antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getLine())
      				->set_line("(", antlrcpp::downCast<Func_definitionContext *>(_localctx)->lparenToken->getLine())
      				->set_line(")", antlrcpp::downCast<Func_definitionContext *>(_localctx)->rparenToken->getLine())
      				->set_line(antlrcpp::downCast<Func_definitionContext *>(_localctx)->cs->info, 0, 1);
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n"
      				+ _localctx->info.line + "\n");
      	 	
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(113);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->t = type_specifier();
      setState(114);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken = match(C8086Parser::ID);
      setState(115);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->lparenToken = match(C8086Parser::LPAREN);
      setState(116);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->plr = parameter_list_err(0);
      setState(117);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->rparenToken = match(C8086Parser::RPAREN);
      setState(118);
      antlrcpp::downCast<Func_definitionContext *>(_localctx)->cs = compound_statement();

      			_localctx->info.set_line(antlrcpp::downCast<Func_definitionContext *>(_localctx)->t->info, 1)
      				->set_line(antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getLine())
      				->set_line("(", antlrcpp::downCast<Func_definitionContext *>(_localctx)->lparenToken->getLine())
      				->set_line(antlrcpp::downCast<Func_definitionContext *>(_localctx)->plr->info)
      				->set_line(")", antlrcpp::downCast<Func_definitionContext *>(_localctx)->rparenToken->getLine())
      				->set_line(antlrcpp::downCast<Func_definitionContext *>(_localctx)->cs->info, 0, 1);
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": func_definition : type_specifier ID LPAREN parameter_list_err RPAREN compound_statement\n\n"
      				+ _localctx->info.line + "\n");
      			writeIntoErrorFile("Error at line " + std::to_string(antlrcpp::downCast<Func_definitionContext *>(_localctx)->idToken->getLine()) 
      				+ ": syntax error, unexpected ADDOP, expecting RPAREN or COMMA\n");
      		
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Parameter_list_errContext ------------------------------------------------------------------

C8086Parser::Parameter_list_errContext::Parameter_list_errContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C8086Parser::Parameter_list_errContext::ID() {
  return getToken(C8086Parser::ID, 0);
}

tree::TerminalNode* C8086Parser::Parameter_list_errContext::ADDOP() {
  return getToken(C8086Parser::ADDOP, 0);
}

C8086Parser::Type_specifierContext* C8086Parser::Parameter_list_errContext::type_specifier() {
  return getRuleContext<C8086Parser::Type_specifierContext>(0);
}

tree::TerminalNode* C8086Parser::Parameter_list_errContext::MULOP() {
  return getToken(C8086Parser::MULOP, 0);
}

tree::TerminalNode* C8086Parser::Parameter_list_errContext::COMMA() {
  return getToken(C8086Parser::COMMA, 0);
}

C8086Parser::Parameter_list_errContext* C8086Parser::Parameter_list_errContext::parameter_list_err() {
  return getRuleContext<C8086Parser::Parameter_list_errContext>(0);
}


size_t C8086Parser::Parameter_list_errContext::getRuleIndex() const {
  return C8086Parser::RuleParameter_list_err;
}

void C8086Parser::Parameter_list_errContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameter_list_err(this);
}

void C8086Parser::Parameter_list_errContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameter_list_err(this);
}


C8086Parser::Parameter_list_errContext* C8086Parser::parameter_list_err() {
   return parameter_list_err(0);
}

C8086Parser::Parameter_list_errContext* C8086Parser::parameter_list_err(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C8086Parser::Parameter_list_errContext *_localctx = _tracker.createInstance<Parameter_list_errContext>(_ctx, parentState);
  C8086Parser::Parameter_list_errContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 10;
  enterRecursionRule(_localctx, 10, C8086Parser::RuleParameter_list_err, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(138);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      setState(124);
      antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->t = type_specifier();
      setState(125);
      antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->idToken = match(C8086Parser::ID);
      setState(126);
      antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->addopToken = match(C8086Parser::ADDOP);

      			_localctx->info.set_line(antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->t->info, 1)
      				->set_line(antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->idToken->getLine())
      				->set_line(antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->addopToken->getText(), antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->addopToken->getLine());
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": parameter_list_err : type_specifier ID ADDOP\n\n"
      				+ _localctx->info.line + "\n");
      		
      break;
    }

    case 2: {
      setState(129);
      antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->t = type_specifier();
      setState(130);
      antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->idToken = match(C8086Parser::ID);
      setState(131);
      antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->mulopToken = match(C8086Parser::MULOP);

      			_localctx->info.set_line(antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->t->info, 1)
      				->set_line(antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->idToken->getLine())
      				->set_line(antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->mulopToken->getText(), antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->mulopToken->getLine());
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": parameter_list_err : type_specifier ID MULOP\n\n"
      				+ _localctx->info.line + "\n");
      		
      break;
    }

    case 3: {
      setState(134);
      antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->t = type_specifier();
      setState(135);
      antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->addopToken = match(C8086Parser::ADDOP);

      			_localctx->info.set_line(antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->t->info, 1)
      				->set_line(antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->addopToken->getText(), antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->addopToken->getLine());
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": parameter_list_err : type_specifier ID MULOP\n\n"
      				+ _localctx->info.line + "\n");
      		
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(148);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Parameter_list_errContext>(parentContext, parentState);
        _localctx->plr = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleParameter_list_err);
        setState(140);

        if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
        setState(141);
        antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->commaToken = match(C8086Parser::COMMA);
        setState(142);
        antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->t = type_specifier();
        setState(143);
        antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->idToken = match(C8086Parser::ID);

                  			_localctx->info.set_line(antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->plr->info)
                  				->set_line(",", antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->commaToken->getLine())
                  				->set_line(antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->t->info)
                  				->set_line(antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<Parameter_list_errContext *>(_localctx)->idToken->getLine());
                  			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
                  				+ ": parameter_list_err : parameter_list_err COMMA type_specifier_err\n\n"
                  				+ _localctx->info.line + "\n"); 
                  		 
      }
      setState(150);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Parameter_listContext ------------------------------------------------------------------

C8086Parser::Parameter_listContext::Parameter_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C8086Parser::Parameter_listContext::ID() {
  return getToken(C8086Parser::ID, 0);
}

C8086Parser::Type_specifierContext* C8086Parser::Parameter_listContext::type_specifier() {
  return getRuleContext<C8086Parser::Type_specifierContext>(0);
}

tree::TerminalNode* C8086Parser::Parameter_listContext::COMMA() {
  return getToken(C8086Parser::COMMA, 0);
}

C8086Parser::Parameter_listContext* C8086Parser::Parameter_listContext::parameter_list() {
  return getRuleContext<C8086Parser::Parameter_listContext>(0);
}


size_t C8086Parser::Parameter_listContext::getRuleIndex() const {
  return C8086Parser::RuleParameter_list;
}

void C8086Parser::Parameter_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameter_list(this);
}

void C8086Parser::Parameter_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameter_list(this);
}


C8086Parser::Parameter_listContext* C8086Parser::parameter_list() {
   return parameter_list(0);
}

C8086Parser::Parameter_listContext* C8086Parser::parameter_list(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C8086Parser::Parameter_listContext *_localctx = _tracker.createInstance<Parameter_listContext>(_ctx, parentState);
  C8086Parser::Parameter_listContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 12;
  enterRecursionRule(_localctx, 12, C8086Parser::RuleParameter_list, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(159);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(152);
      antlrcpp::downCast<Parameter_listContext *>(_localctx)->t = type_specifier();
      setState(153);
      antlrcpp::downCast<Parameter_listContext *>(_localctx)->idToken = match(C8086Parser::ID);

      			Param p;
      			p.type = antlrcpp::downCast<Parameter_listContext *>(_localctx)->t->info.line;
      			p.name = antlrcpp::downCast<Parameter_listContext *>(_localctx)->idToken->getText();
      			_localctx->params.push_back(p);
      			std::cout<<p.type<<" "<<p.name<<endl;
      			_localctx->info.set_line(antlrcpp::downCast<Parameter_listContext *>(_localctx)->t->info, 1)
      				->set_line(antlrcpp::downCast<Parameter_listContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<Parameter_listContext *>(_localctx)->idToken->getLine());
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": parameter_list : type_specifier ID\n\n"
      				+ _localctx->info.line + "\n");
      	 	
      break;
    }

    case 2: {
      setState(156);
      antlrcpp::downCast<Parameter_listContext *>(_localctx)->t = type_specifier();

      			_localctx->info.set_line(antlrcpp::downCast<Parameter_listContext *>(_localctx)->t->info);
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": parameter_list : type_specifier\n\n"
      				+ _localctx->info.line + "\n");
      	 	
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(174);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(172);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Parameter_listContext>(parentContext, parentState);
          _localctx->pl = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleParameter_list);
          setState(161);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(162);
          antlrcpp::downCast<Parameter_listContext *>(_localctx)->commaToken = match(C8086Parser::COMMA);
          setState(163);
          antlrcpp::downCast<Parameter_listContext *>(_localctx)->t = type_specifier();
          setState(164);
          antlrcpp::downCast<Parameter_listContext *>(_localctx)->idToken = match(C8086Parser::ID);

                    			antlrcpp::downCast<Parameter_listContext *>(_localctx)->params =  antlrcpp::downCast<Parameter_listContext *>(_localctx)->pl->params;
                    			Param p;
                    			p.type = antlrcpp::downCast<Parameter_listContext *>(_localctx)->t->info.line;
                    			p.name = antlrcpp::downCast<Parameter_listContext *>(_localctx)->idToken->getText();
                    			_localctx->params.push_back(p);
                    			_localctx->info.set_line(antlrcpp::downCast<Parameter_listContext *>(_localctx)->pl->info)
                    				->set_line(",", antlrcpp::downCast<Parameter_listContext *>(_localctx)->commaToken->getLine())
                    				->set_line(antlrcpp::downCast<Parameter_listContext *>(_localctx)->t->info, 1)
                    				->set_line(antlrcpp::downCast<Parameter_listContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<Parameter_listContext *>(_localctx)->idToken->getLine());
                    			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
                    				+ ": parameter_list : parameter_list COMMA type_specifier ID\n\n"
                    				+ _localctx->info.line + "\n");
                    	    
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Parameter_listContext>(parentContext, parentState);
          _localctx->pl = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleParameter_list);
          setState(167);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(168);
          antlrcpp::downCast<Parameter_listContext *>(_localctx)->commaToken = match(C8086Parser::COMMA);
          setState(169);
          antlrcpp::downCast<Parameter_listContext *>(_localctx)->t = type_specifier();

                    			_localctx->info.set_line(antlrcpp::downCast<Parameter_listContext *>(_localctx)->pl->info)
                    				->set_line(",", antlrcpp::downCast<Parameter_listContext *>(_localctx)->commaToken->getLine())
                    				->set_line(antlrcpp::downCast<Parameter_listContext *>(_localctx)->t->info);
                    			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
                    				+ ": parameter_list : parameter_list COMMA type_specifier\n\n"
                    				+ _localctx->info.line + "\n");
                    	 	
          break;
        }

        default:
          break;
        } 
      }
      setState(176);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Compound_statementContext ------------------------------------------------------------------

C8086Parser::Compound_statementContext::Compound_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C8086Parser::Compound_statementContext::LCURL() {
  return getToken(C8086Parser::LCURL, 0);
}

tree::TerminalNode* C8086Parser::Compound_statementContext::RCURL() {
  return getToken(C8086Parser::RCURL, 0);
}

C8086Parser::StatementsContext* C8086Parser::Compound_statementContext::statements() {
  return getRuleContext<C8086Parser::StatementsContext>(0);
}


size_t C8086Parser::Compound_statementContext::getRuleIndex() const {
  return C8086Parser::RuleCompound_statement;
}

void C8086Parser::Compound_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompound_statement(this);
}

void C8086Parser::Compound_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompound_statement(this);
}

C8086Parser::Compound_statementContext* C8086Parser::compound_statement() {
  Compound_statementContext *_localctx = _tracker.createInstance<Compound_statementContext>(_ctx, getState());
  enterRule(_localctx, 14, C8086Parser::RuleCompound_statement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(186);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(177);
      antlrcpp::downCast<Compound_statementContext *>(_localctx)->lcurlToken = match(C8086Parser::LCURL);

      				if(in_func_check == 0)
      					symbolTable.Enter_Scope();
      				in_func_check = 0;
      			
      setState(179);
      antlrcpp::downCast<Compound_statementContext *>(_localctx)->ss = statements(0);
      setState(180);
      antlrcpp::downCast<Compound_statementContext *>(_localctx)->rcurlToken = match(C8086Parser::RCURL);

      				_localctx->info.set_line(antlrcpp::downCast<Compound_statementContext *>(_localctx)->lcurlToken->getText(), antlrcpp::downCast<Compound_statementContext *>(_localctx)->lcurlToken->getLine(), 0, 1)
      					->set_line(antlrcpp::downCast<Compound_statementContext *>(_localctx)->ss->info)
      					->set_line(antlrcpp::downCast<Compound_statementContext *>(_localctx)->rcurlToken->getText(), antlrcpp::downCast<Compound_statementContext *>(_localctx)->rcurlToken->getLine());
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": compound_statement : LCURL statements RCURL\n\n"
      					+ _localctx->info.line + "\n");
      					symbolTable.Print_All();
      					symbolTable.Exit_Scope();
      			
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(183);
      antlrcpp::downCast<Compound_statementContext *>(_localctx)->lcurlToken = match(C8086Parser::LCURL);
      setState(184);
      antlrcpp::downCast<Compound_statementContext *>(_localctx)->rcurlToken = match(C8086Parser::RCURL);

      				_localctx->info.set_line(antlrcpp::downCast<Compound_statementContext *>(_localctx)->lcurlToken->getText(), antlrcpp::downCast<Compound_statementContext *>(_localctx)->lcurlToken->getLine())
      					->set_line(antlrcpp::downCast<Compound_statementContext *>(_localctx)->rcurlToken->getText(), antlrcpp::downCast<Compound_statementContext *>(_localctx)->rcurlToken->getLine());
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": compound_statement : LCURL RCURL\n\n"
      					+ _localctx->info.line + "\n");
      				
      			
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Var_declarationContext ------------------------------------------------------------------

C8086Parser::Var_declarationContext::Var_declarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C8086Parser::Type_specifierContext* C8086Parser::Var_declarationContext::type_specifier() {
  return getRuleContext<C8086Parser::Type_specifierContext>(0);
}

C8086Parser::Declaration_listContext* C8086Parser::Var_declarationContext::declaration_list() {
  return getRuleContext<C8086Parser::Declaration_listContext>(0);
}

tree::TerminalNode* C8086Parser::Var_declarationContext::SEMICOLON() {
  return getToken(C8086Parser::SEMICOLON, 0);
}

C8086Parser::Declaration_list_errContext* C8086Parser::Var_declarationContext::declaration_list_err() {
  return getRuleContext<C8086Parser::Declaration_list_errContext>(0);
}


size_t C8086Parser::Var_declarationContext::getRuleIndex() const {
  return C8086Parser::RuleVar_declaration;
}

void C8086Parser::Var_declarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVar_declaration(this);
}

void C8086Parser::Var_declarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVar_declaration(this);
}

C8086Parser::Var_declarationContext* C8086Parser::var_declaration() {
  Var_declarationContext *_localctx = _tracker.createInstance<Var_declarationContext>(_ctx, getState());
  enterRule(_localctx, 16, C8086Parser::RuleVar_declaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(198);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(188);
      antlrcpp::downCast<Var_declarationContext *>(_localctx)->t = type_specifier();
      setState(189);
      antlrcpp::downCast<Var_declarationContext *>(_localctx)->dl = declaration_list(0);
      setState(190);
      antlrcpp::downCast<Var_declarationContext *>(_localctx)->sm = match(C8086Parser::SEMICOLON);

      		for(int i = 0; i<antlrcpp::downCast<Var_declarationContext *>(_localctx)->dl->IDs.size(); i++){
      			cout<<i<<" 1.2 "<<antlrcpp::downCast<Var_declarationContext *>(_localctx)->dl->IDs[i].name<<endl;
      			bool inserted = symbolTable.Insert(antlrcpp::downCast<Var_declarationContext *>(_localctx)->dl->IDs[i].name, "ID", antlrcpp::downCast<Var_declarationContext *>(_localctx)->t->info.line, antlrcpp::downCast<Var_declarationContext *>(_localctx)->dl->IDs[i].is_array);
      			if(!inserted){
      				writeIntoparserLogFile("Error at line " + std::to_string(antlrcpp::downCast<Var_declarationContext *>(_localctx)->sm->getLine()) 
      					+ ": Multiple declaration of " + antlrcpp::downCast<Var_declarationContext *>(_localctx)->dl->IDs[i].name + "\n");
      				writeIntoErrorFile("Error at line " + std::to_string(antlrcpp::downCast<Var_declarationContext *>(_localctx)->sm->getLine()) 
      					+ ": Multiple declaration of " + antlrcpp::downCast<Var_declarationContext *>(_localctx)->dl->IDs[i].name + "\n");
      				syntaxErrorCount++;
      			}
      		}
      		_localctx->info.set_line(antlrcpp::downCast<Var_declarationContext *>(_localctx)->t->info, 1)
      			->set_line(antlrcpp::downCast<Var_declarationContext *>(_localctx)->dl->info)
      			->set_line(";", antlrcpp::downCast<Var_declarationContext *>(_localctx)->sm->getLine(), 0, 1);
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": var_declaration : type_specifier declaration_list SEMICOLON\n\n"
      			+ _localctx->info.line + "\n");
      	 
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(193);
      antlrcpp::downCast<Var_declarationContext *>(_localctx)->t = type_specifier();
      setState(194);
      antlrcpp::downCast<Var_declarationContext *>(_localctx)->dlr = declaration_list_err(0);
      setState(195);
      antlrcpp::downCast<Var_declarationContext *>(_localctx)->sm = match(C8086Parser::SEMICOLON);

              _localctx->info.set_line(antlrcpp::downCast<Var_declarationContext *>(_localctx)->t->info)
      	   		->set_line(antlrcpp::downCast<Var_declarationContext *>(_localctx)->dlr->info)
      			->set_line(antlrcpp::downCast<Var_declarationContext *>(_localctx)->sm->getText(), antlrcpp::downCast<Var_declarationContext *>(_localctx)->sm->getLine());

      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": var_declaration : type_specifier declaration_list_err SEMICOLON\n\n"
      			+ _localctx->info.line + "\n");
      		writeIntoErrorFile("Error at line " + std::to_string(_localctx->info.line_no) 
      			+ ": syntax error, unexpected ADDOP, expecting COMMA or SEMICOLON\n");
              syntaxErrorCount++;
            
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Declaration_list_errContext ------------------------------------------------------------------

C8086Parser::Declaration_list_errContext::Declaration_list_errContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C8086Parser::Declaration_list_errContext::ADDOP() {
  return getToken(C8086Parser::ADDOP, 0);
}

std::vector<tree::TerminalNode *> C8086Parser::Declaration_list_errContext::ID() {
  return getTokens(C8086Parser::ID);
}

tree::TerminalNode* C8086Parser::Declaration_list_errContext::ID(size_t i) {
  return getToken(C8086Parser::ID, i);
}

tree::TerminalNode* C8086Parser::Declaration_list_errContext::MULOP() {
  return getToken(C8086Parser::MULOP, 0);
}

tree::TerminalNode* C8086Parser::Declaration_list_errContext::COMMA() {
  return getToken(C8086Parser::COMMA, 0);
}

C8086Parser::Declaration_list_errContext* C8086Parser::Declaration_list_errContext::declaration_list_err() {
  return getRuleContext<C8086Parser::Declaration_list_errContext>(0);
}


size_t C8086Parser::Declaration_list_errContext::getRuleIndex() const {
  return C8086Parser::RuleDeclaration_list_err;
}

void C8086Parser::Declaration_list_errContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration_list_err(this);
}

void C8086Parser::Declaration_list_errContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration_list_err(this);
}


C8086Parser::Declaration_list_errContext* C8086Parser::declaration_list_err() {
   return declaration_list_err(0);
}

C8086Parser::Declaration_list_errContext* C8086Parser::declaration_list_err(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C8086Parser::Declaration_list_errContext *_localctx = _tracker.createInstance<Declaration_list_errContext>(_ctx, parentState);
  C8086Parser::Declaration_list_errContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, C8086Parser::RuleDeclaration_list_err, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(215);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(201);
      antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id1 = match(C8086Parser::ID);
      setState(202);
      antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->addopToken = match(C8086Parser::ADDOP);
      setState(203);
      antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id2 = match(C8086Parser::ID);

      		_localctx->info.set_line(antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id1->getText(), antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id1->getLine())
      			->set_line(antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->addopToken->getText(), antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->addopToken->getLine())
      			->set_line(antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id2->getText(), antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id2->getLine());
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": declaration_list_err : ID ADDOP ID\n\n"
      			+ _localctx->info.line + "\n");
          
      break;
    }

    case 2: {
      setState(205);
      antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id1 = match(C8086Parser::ID);
      setState(206);
      antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->addopToken = match(C8086Parser::ADDOP);

      		_localctx->info.set_line(antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id1->getText(), antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id1->getLine())
      			->set_line(antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->addopToken->getText(), antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->addopToken->getLine());
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": declaration_list_err : ID ADDOP\n\n"
      			+ _localctx->info.line + "\n");
      	
      break;
    }

    case 3: {
      setState(208);
      antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id1 = match(C8086Parser::ID);
      setState(209);
      antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->mulopToken = match(C8086Parser::MULOP);
      setState(210);
      antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id2 = match(C8086Parser::ID);

      		_localctx->info.set_line(antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id1->getText(), antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id1->getLine())
      			->set_line(antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->mulopToken->getText(), antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->mulopToken->getLine())
      			->set_line(antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id2->getText(), antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id2->getLine());
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": declaration_list_err : ID MULOP ID\n\n"
      			+ _localctx->info.line + "\n");
      	
      break;
    }

    case 4: {
      setState(212);
      antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id1 = match(C8086Parser::ID);
      setState(213);
      antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->mulopToken = match(C8086Parser::MULOP);

      		_localctx->info.set_line(antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id1->getText(), antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->id1->getLine())
      			->set_line(antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->mulopToken->getText(), antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->mulopToken->getLine());
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": declaration_list_err : ID MULOP\n\n"
      			+ _localctx->info.line + "\n");
      	
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(223);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Declaration_list_errContext>(parentContext, parentState);
        _localctx->dlr = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleDeclaration_list_err);
        setState(217);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(218);
        antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->commaToken = match(C8086Parser::COMMA);
        setState(219);
        antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->idToken = match(C8086Parser::ID);

                  		_localctx->info.set_line(antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->dlr->info)
                  			->set_line(antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->commaToken->getText(), antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->commaToken->getLine())
                  			->set_line(antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<Declaration_list_errContext *>(_localctx)->idToken->getLine());
                  		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
                  			+ ": declaration_list_err : declaration_list_err COMMA ID\n\n"
                  			+ _localctx->info.line + "\n");
                  	 
      }
      setState(225);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Type_specifierContext ------------------------------------------------------------------

C8086Parser::Type_specifierContext::Type_specifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C8086Parser::Type_specifierContext::INT() {
  return getToken(C8086Parser::INT, 0);
}

tree::TerminalNode* C8086Parser::Type_specifierContext::FLOAT() {
  return getToken(C8086Parser::FLOAT, 0);
}

tree::TerminalNode* C8086Parser::Type_specifierContext::VOID() {
  return getToken(C8086Parser::VOID, 0);
}


size_t C8086Parser::Type_specifierContext::getRuleIndex() const {
  return C8086Parser::RuleType_specifier;
}

void C8086Parser::Type_specifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType_specifier(this);
}

void C8086Parser::Type_specifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType_specifier(this);
}

C8086Parser::Type_specifierContext* C8086Parser::type_specifier() {
  Type_specifierContext *_localctx = _tracker.createInstance<Type_specifierContext>(_ctx, getState());
  enterRule(_localctx, 20, C8086Parser::RuleType_specifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(232);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C8086Parser::INT: {
        enterOuterAlt(_localctx, 1);
        setState(226);
        antlrcpp::downCast<Type_specifierContext *>(_localctx)->intToken = match(C8086Parser::INT);

                    _localctx->info.line = antlrcpp::downCast<Type_specifierContext *>(_localctx)->intToken->getText();
        			_localctx->info.line_no = antlrcpp::downCast<Type_specifierContext *>(_localctx)->intToken->getLine();
        			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
        				+ ": type_specifier : INT\n\n" + _localctx->info.line + "\n");
                
        break;
      }

      case C8086Parser::FLOAT: {
        enterOuterAlt(_localctx, 2);
        setState(228);
        antlrcpp::downCast<Type_specifierContext *>(_localctx)->floatToken = match(C8086Parser::FLOAT);

        			_localctx->info.line = antlrcpp::downCast<Type_specifierContext *>(_localctx)->floatToken->getText();
        			_localctx->info.line_no = antlrcpp::downCast<Type_specifierContext *>(_localctx)->floatToken->getLine();
        			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
        				+ ": type_specifier : FLOAT\n\n" + _localctx->info.line + "\n");
                
        break;
      }

      case C8086Parser::VOID: {
        enterOuterAlt(_localctx, 3);
        setState(230);
        antlrcpp::downCast<Type_specifierContext *>(_localctx)->voidToken = match(C8086Parser::VOID);

                    _localctx->info.line = antlrcpp::downCast<Type_specifierContext *>(_localctx)->voidToken->getText();
        			_localctx->info.line_no = antlrcpp::downCast<Type_specifierContext *>(_localctx)->voidToken->getLine();
        			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
        				+ ": type_specifier : VOID\n\n" + _localctx->info.line + "\n");
                
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Declaration_listContext ------------------------------------------------------------------

C8086Parser::Declaration_listContext::Declaration_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C8086Parser::Declaration_listContext::ID() {
  return getToken(C8086Parser::ID, 0);
}

tree::TerminalNode* C8086Parser::Declaration_listContext::LTHIRD() {
  return getToken(C8086Parser::LTHIRD, 0);
}

tree::TerminalNode* C8086Parser::Declaration_listContext::CONST_INT() {
  return getToken(C8086Parser::CONST_INT, 0);
}

tree::TerminalNode* C8086Parser::Declaration_listContext::RTHIRD() {
  return getToken(C8086Parser::RTHIRD, 0);
}

tree::TerminalNode* C8086Parser::Declaration_listContext::COMMA() {
  return getToken(C8086Parser::COMMA, 0);
}

C8086Parser::Declaration_listContext* C8086Parser::Declaration_listContext::declaration_list() {
  return getRuleContext<C8086Parser::Declaration_listContext>(0);
}


size_t C8086Parser::Declaration_listContext::getRuleIndex() const {
  return C8086Parser::RuleDeclaration_list;
}

void C8086Parser::Declaration_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration_list(this);
}

void C8086Parser::Declaration_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration_list(this);
}


C8086Parser::Declaration_listContext* C8086Parser::declaration_list() {
   return declaration_list(0);
}

C8086Parser::Declaration_listContext* C8086Parser::declaration_list(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C8086Parser::Declaration_listContext *_localctx = _tracker.createInstance<Declaration_listContext>(_ctx, parentState);
  C8086Parser::Declaration_listContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 22;
  enterRecursionRule(_localctx, 22, C8086Parser::RuleDeclaration_list, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(242);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      setState(235);
      antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken = match(C8086Parser::ID);

      				_localctx->IDs.push_back(Param(antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken->getText()));
      				_localctx->info.set_line(antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken->getLine());
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": declaration_list : ID\n\n"
      					+ _localctx->info.line + "\n");
      		  
      break;
    }

    case 2: {
      setState(237);
      antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken = match(C8086Parser::ID);
      setState(238);
      antlrcpp::downCast<Declaration_listContext *>(_localctx)->lthirdToken = match(C8086Parser::LTHIRD);
      setState(239);
      antlrcpp::downCast<Declaration_listContext *>(_localctx)->const_intToken = match(C8086Parser::CONST_INT);
      setState(240);
      antlrcpp::downCast<Declaration_listContext *>(_localctx)->rthirdToken = match(C8086Parser::RTHIRD);

      				_localctx->IDs.push_back(Param(antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken->getText(), true));
      				_localctx->info.set_line(antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken->getLine())
      					->set_line("[", antlrcpp::downCast<Declaration_listContext *>(_localctx)->lthirdToken->getLine())
      					->set_line(antlrcpp::downCast<Declaration_listContext *>(_localctx)->const_intToken->getText(), antlrcpp::downCast<Declaration_listContext *>(_localctx)->const_intToken->getLine())
      					->set_line("]", antlrcpp::downCast<Declaration_listContext *>(_localctx)->rthirdToken->getLine());
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": declaration_list : ID LTHIRD CONST_INT RTHIRD\n\n"
      					+ _localctx->info.line + "\n");
      		  
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(257);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(255);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Declaration_listContext>(parentContext, parentState);
          _localctx->dl = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleDeclaration_list);
          setState(244);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(245);
          antlrcpp::downCast<Declaration_listContext *>(_localctx)->commaToken = match(C8086Parser::COMMA);
          setState(246);
          antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken = match(C8086Parser::ID);

                    				antlrcpp::downCast<Declaration_listContext *>(_localctx)->IDs =  antlrcpp::downCast<Declaration_listContext *>(_localctx)->dl->IDs;
                    				_localctx->IDs.push_back(Param(antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken->getText()));
                    				_localctx->info.set_line(antlrcpp::downCast<Declaration_listContext *>(_localctx)->dl->info)
                    					->set_line(",", antlrcpp::downCast<Declaration_listContext *>(_localctx)->commaToken->getLine())
                    					->set_line(antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken->getLine());
                    				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
                    					+ ": declaration_list : declaration_list COMMA ID\n\n"
                    					+ _localctx->info.line + "\n");
                    	      
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Declaration_listContext>(parentContext, parentState);
          _localctx->dl = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleDeclaration_list);
          setState(248);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(249);
          antlrcpp::downCast<Declaration_listContext *>(_localctx)->commaToken = match(C8086Parser::COMMA);
          setState(250);
          antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken = match(C8086Parser::ID);
          setState(251);
          antlrcpp::downCast<Declaration_listContext *>(_localctx)->lthirdToken = match(C8086Parser::LTHIRD);
          setState(252);
          antlrcpp::downCast<Declaration_listContext *>(_localctx)->const_intToken = match(C8086Parser::CONST_INT);
          setState(253);
          antlrcpp::downCast<Declaration_listContext *>(_localctx)->rthirdToken = match(C8086Parser::RTHIRD);

                    				antlrcpp::downCast<Declaration_listContext *>(_localctx)->IDs =  antlrcpp::downCast<Declaration_listContext *>(_localctx)->dl->IDs;
                    				_localctx->IDs.push_back(Param(antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken->getText(), true));
                    				_localctx->info.set_line(antlrcpp::downCast<Declaration_listContext *>(_localctx)->dl->info)
                    					->set_line(",", antlrcpp::downCast<Declaration_listContext *>(_localctx)->commaToken->getLine())
                    					->set_line(antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<Declaration_listContext *>(_localctx)->idToken->getLine())
                    					->set_line("[", antlrcpp::downCast<Declaration_listContext *>(_localctx)->lthirdToken->getLine())
                    					->set_line(antlrcpp::downCast<Declaration_listContext *>(_localctx)->const_intToken->getText(), antlrcpp::downCast<Declaration_listContext *>(_localctx)->const_intToken->getLine())
                    					->set_line("]", antlrcpp::downCast<Declaration_listContext *>(_localctx)->rthirdToken->getLine());
                    				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
                    					+ ": declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n"
                    					+ _localctx->info.line + "\n");
                    		  
          break;
        }

        default:
          break;
        } 
      }
      setState(259);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- StatementsContext ------------------------------------------------------------------

C8086Parser::StatementsContext::StatementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C8086Parser::StatementContext* C8086Parser::StatementsContext::statement() {
  return getRuleContext<C8086Parser::StatementContext>(0);
}

C8086Parser::StatementsContext* C8086Parser::StatementsContext::statements() {
  return getRuleContext<C8086Parser::StatementsContext>(0);
}


size_t C8086Parser::StatementsContext::getRuleIndex() const {
  return C8086Parser::RuleStatements;
}

void C8086Parser::StatementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatements(this);
}

void C8086Parser::StatementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatements(this);
}


C8086Parser::StatementsContext* C8086Parser::statements() {
   return statements(0);
}

C8086Parser::StatementsContext* C8086Parser::statements(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C8086Parser::StatementsContext *_localctx = _tracker.createInstance<StatementsContext>(_ctx, parentState);
  C8086Parser::StatementsContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 24;
  enterRecursionRule(_localctx, 24, C8086Parser::RuleStatements, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(261);
    antlrcpp::downCast<StatementsContext *>(_localctx)->s = statement();

    			_localctx->info.set_line(antlrcpp::downCast<StatementsContext *>(_localctx)->s->info);
    			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
    				+ ": statements : statement\n\n"
    				+ _localctx->info.line + "\n");
    		
    _ctx->stop = _input->LT(-1);
    setState(270);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<StatementsContext>(parentContext, parentState);
        _localctx->ss = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleStatements);
        setState(264);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(265);
        antlrcpp::downCast<StatementsContext *>(_localctx)->s = statement();

                  			_localctx->info.set_line(antlrcpp::downCast<StatementsContext *>(_localctx)->ss->info)
                  				->set_line(antlrcpp::downCast<StatementsContext *>(_localctx)->s->info);
                  			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
                  				+ ": statements : statements statement\n\n"
                  				+ _localctx->info.line + "\n");
                  	    
      }
      setState(272);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

C8086Parser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C8086Parser::Var_declarationContext* C8086Parser::StatementContext::var_declaration() {
  return getRuleContext<C8086Parser::Var_declarationContext>(0);
}

std::vector<C8086Parser::Expression_statementContext *> C8086Parser::StatementContext::expression_statement() {
  return getRuleContexts<C8086Parser::Expression_statementContext>();
}

C8086Parser::Expression_statementContext* C8086Parser::StatementContext::expression_statement(size_t i) {
  return getRuleContext<C8086Parser::Expression_statementContext>(i);
}

C8086Parser::Compound_statementContext* C8086Parser::StatementContext::compound_statement() {
  return getRuleContext<C8086Parser::Compound_statementContext>(0);
}

tree::TerminalNode* C8086Parser::StatementContext::FOR() {
  return getToken(C8086Parser::FOR, 0);
}

tree::TerminalNode* C8086Parser::StatementContext::LPAREN() {
  return getToken(C8086Parser::LPAREN, 0);
}

tree::TerminalNode* C8086Parser::StatementContext::RPAREN() {
  return getToken(C8086Parser::RPAREN, 0);
}

C8086Parser::ExpressionContext* C8086Parser::StatementContext::expression() {
  return getRuleContext<C8086Parser::ExpressionContext>(0);
}

std::vector<C8086Parser::StatementContext *> C8086Parser::StatementContext::statement() {
  return getRuleContexts<C8086Parser::StatementContext>();
}

C8086Parser::StatementContext* C8086Parser::StatementContext::statement(size_t i) {
  return getRuleContext<C8086Parser::StatementContext>(i);
}

tree::TerminalNode* C8086Parser::StatementContext::IF() {
  return getToken(C8086Parser::IF, 0);
}

tree::TerminalNode* C8086Parser::StatementContext::ELSE() {
  return getToken(C8086Parser::ELSE, 0);
}

tree::TerminalNode* C8086Parser::StatementContext::WHILE() {
  return getToken(C8086Parser::WHILE, 0);
}

tree::TerminalNode* C8086Parser::StatementContext::DO() {
  return getToken(C8086Parser::DO, 0);
}

tree::TerminalNode* C8086Parser::StatementContext::SEMICOLON() {
  return getToken(C8086Parser::SEMICOLON, 0);
}

tree::TerminalNode* C8086Parser::StatementContext::PRINTLN() {
  return getToken(C8086Parser::PRINTLN, 0);
}

tree::TerminalNode* C8086Parser::StatementContext::ID() {
  return getToken(C8086Parser::ID, 0);
}

tree::TerminalNode* C8086Parser::StatementContext::RETURN() {
  return getToken(C8086Parser::RETURN, 0);
}

tree::TerminalNode* C8086Parser::StatementContext::CONTINUE() {
  return getToken(C8086Parser::CONTINUE, 0);
}

tree::TerminalNode* C8086Parser::StatementContext::BREAK() {
  return getToken(C8086Parser::BREAK, 0);
}


size_t C8086Parser::StatementContext::getRuleIndex() const {
  return C8086Parser::RuleStatement;
}

void C8086Parser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void C8086Parser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

C8086Parser::StatementContext* C8086Parser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 26, C8086Parser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(343);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(273);
      antlrcpp::downCast<StatementContext *>(_localctx)->vd = var_declaration();

      			_localctx->info.set_line(antlrcpp::downCast<StatementContext *>(_localctx)->vd->info);
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": statement : var_declaration\n\n"
      				+ _localctx->info.line + "\n");
      	  
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(276);
      antlrcpp::downCast<StatementContext *>(_localctx)->es = expression_statement();

      			_localctx->info.set_line(antlrcpp::downCast<StatementContext *>(_localctx)->es->info);
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": statement : expression_statement\n\n"
      				+ _localctx->info.line + "\n");
      	  
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(279);
      antlrcpp::downCast<StatementContext *>(_localctx)->c = compound_statement();

      			_localctx->info.set_line(antlrcpp::downCast<StatementContext *>(_localctx)->c->info);
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": statement : compound_statement\n\n"
      				+ _localctx->info.line + "\n");
      	  
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(282);
      antlrcpp::downCast<StatementContext *>(_localctx)->forToken = match(C8086Parser::FOR);
      setState(283);
      antlrcpp::downCast<StatementContext *>(_localctx)->lparenToken = match(C8086Parser::LPAREN);
      setState(284);
      antlrcpp::downCast<StatementContext *>(_localctx)->es1 = expression_statement();
      setState(285);
      antlrcpp::downCast<StatementContext *>(_localctx)->es2 = expression_statement();
      setState(286);
      antlrcpp::downCast<StatementContext *>(_localctx)->e = expression();
      setState(287);
      antlrcpp::downCast<StatementContext *>(_localctx)->rparenToken = match(C8086Parser::RPAREN);

      			in_loop_check ++;
      	  
      setState(289);
      antlrcpp::downCast<StatementContext *>(_localctx)->s = statement();

      				if(in_loop_check > 0)
      					in_loop_check--;
      				antlrcpp::downCast<StatementContext *>(_localctx)->es1->info.line.pop_back();
      				antlrcpp::downCast<StatementContext *>(_localctx)->es2->info.line.pop_back();
      				_localctx->info.set_line("for", antlrcpp::downCast<StatementContext *>(_localctx)->forToken->getLine());
      				_localctx->info.set_line("(", antlrcpp::downCast<StatementContext *>(_localctx)->lparenToken->getLine());
      				_localctx->info.set_line(antlrcpp::downCast<StatementContext *>(_localctx)->es1->info);
      				_localctx->info.set_line(antlrcpp::downCast<StatementContext *>(_localctx)->es2->info);
      				_localctx->info.set_line(antlrcpp::downCast<StatementContext *>(_localctx)->e->info);
      				_localctx->info.set_line(")", antlrcpp::downCast<StatementContext *>(_localctx)->rparenToken->getLine());
      				_localctx->info.set_line(antlrcpp::downCast<StatementContext *>(_localctx)->s->info);
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n"
      					+ _localctx->info.line + "\n");
      	   
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(292);
      antlrcpp::downCast<StatementContext *>(_localctx)->ifToken = match(C8086Parser::IF);
      setState(293);
      antlrcpp::downCast<StatementContext *>(_localctx)->lparenToken = match(C8086Parser::LPAREN);
      setState(294);
      antlrcpp::downCast<StatementContext *>(_localctx)->e = expression();
      setState(295);
      antlrcpp::downCast<StatementContext *>(_localctx)->rparenToken = match(C8086Parser::RPAREN);
      setState(296);
      antlrcpp::downCast<StatementContext *>(_localctx)->s = statement();

      				_localctx->info.set_line("if", antlrcpp::downCast<StatementContext *>(_localctx)->ifToken->getLine());
      				_localctx->info.set_line("(", antlrcpp::downCast<StatementContext *>(_localctx)->lparenToken->getLine());
      				_localctx->info.set_line(antlrcpp::downCast<StatementContext *>(_localctx)->e->info);
      				_localctx->info.set_line(")", antlrcpp::downCast<StatementContext *>(_localctx)->rparenToken->getLine());
      				_localctx->info.set_line(antlrcpp::downCast<StatementContext *>(_localctx)->s->info);
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": statement : IF LPAREN expression RPAREN statement\n\n"
      					+ _localctx->info.line + "\n");
      	   
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(299);
      antlrcpp::downCast<StatementContext *>(_localctx)->ifToken = match(C8086Parser::IF);
      setState(300);
      antlrcpp::downCast<StatementContext *>(_localctx)->lparenToken = match(C8086Parser::LPAREN);
      setState(301);
      antlrcpp::downCast<StatementContext *>(_localctx)->e = expression();
      setState(302);
      antlrcpp::downCast<StatementContext *>(_localctx)->rparenToken = match(C8086Parser::RPAREN);
      setState(303);
      antlrcpp::downCast<StatementContext *>(_localctx)->s1 = statement();
      setState(304);
      antlrcpp::downCast<StatementContext *>(_localctx)->elseToken = match(C8086Parser::ELSE);
      setState(305);
      antlrcpp::downCast<StatementContext *>(_localctx)->s2 = statement();

      				_localctx->info.set_line("if", antlrcpp::downCast<StatementContext *>(_localctx)->ifToken->getLine())
      					->set_line("(", antlrcpp::downCast<StatementContext *>(_localctx)->lparenToken->getLine())
      					->set_line(antlrcpp::downCast<StatementContext *>(_localctx)->e->info)
      					->set_line(")", antlrcpp::downCast<StatementContext *>(_localctx)->rparenToken->getLine())
      					->set_line(antlrcpp::downCast<StatementContext *>(_localctx)->s1->info)
      					->set_line("else ", antlrcpp::downCast<StatementContext *>(_localctx)->elseToken->getLine())
      					->set_line(antlrcpp::downCast<StatementContext *>(_localctx)->s2->info);
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": statement : IF LPAREN expression RPAREN statement ELSE statement\n\n"
      					+ _localctx->info.line + "\n");
      	   
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(308);
      antlrcpp::downCast<StatementContext *>(_localctx)->whileToken = match(C8086Parser::WHILE);
      setState(309);
      antlrcpp::downCast<StatementContext *>(_localctx)->lparenToken = match(C8086Parser::LPAREN);
      setState(310);
      antlrcpp::downCast<StatementContext *>(_localctx)->e = expression();
      setState(311);
      antlrcpp::downCast<StatementContext *>(_localctx)->rparenToken = match(C8086Parser::RPAREN);

      			in_loop_check++;
      	  
      setState(313);
      antlrcpp::downCast<StatementContext *>(_localctx)->s = statement();

      				if(in_loop_check>0){
      					in_loop_check--;
      				}
      				_localctx->info.set_line("while", antlrcpp::downCast<StatementContext *>(_localctx)->whileToken->getLine())
      					->set_line("(", antlrcpp::downCast<StatementContext *>(_localctx)->lparenToken->getLine())
      					->set_line(antlrcpp::downCast<StatementContext *>(_localctx)->e->info)
      					->set_line(")", antlrcpp::downCast<StatementContext *>(_localctx)->rparenToken->getLine())
      					->set_line(antlrcpp::downCast<StatementContext *>(_localctx)->s->info);
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": statement : WHILE LPAREN expression RPAREN statement\n\n"
      					+ _localctx->info.line + "\n");
      	   
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(316);
      match(C8086Parser::DO);

      			in_loop_check++;
      		
      setState(318);
      compound_statement();
      setState(319);
      match(C8086Parser::WHILE);
      setState(320);
      match(C8086Parser::LPAREN);
      setState(321);
      expression();
      setState(322);
      match(C8086Parser::RPAREN);
      setState(323);
      match(C8086Parser::SEMICOLON);

      			if(in_loop_check>0){
      					in_loop_check--;
      				}
      		
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(326);
      antlrcpp::downCast<StatementContext *>(_localctx)->printlnToken = match(C8086Parser::PRINTLN);
      setState(327);
      antlrcpp::downCast<StatementContext *>(_localctx)->lparenToken = match(C8086Parser::LPAREN);
      setState(328);
      antlrcpp::downCast<StatementContext *>(_localctx)->idToken = match(C8086Parser::ID);
      setState(329);
      antlrcpp::downCast<StatementContext *>(_localctx)->rparenToken = match(C8086Parser::RPAREN);
      setState(330);
      antlrcpp::downCast<StatementContext *>(_localctx)->semicolonToken = match(C8086Parser::SEMICOLON);

      				cout<<"5.5 PRINTLN "<<antlrcpp::downCast<StatementContext *>(_localctx)->printlnToken->getText()<<endl;
      				SymbolInfo *temp = symbolTable.Look_Up(antlrcpp::downCast<StatementContext *>(_localctx)->idToken->getText());
      				if(temp == NULL){
      					writeIntoparserLogFile("Error at line " + std::to_string(antlrcpp::downCast<StatementContext *>(_localctx)->idToken->getLine()) 
      						+ ": Undeclared variable " + antlrcpp::downCast<StatementContext *>(_localctx)->idToken->getText() + "\n");
      					writeIntoErrorFile("Error at line " + std::to_string(antlrcpp::downCast<StatementContext *>(_localctx)->idToken->getLine()) 
      						+ ": Undeclared variable " + antlrcpp::downCast<StatementContext *>(_localctx)->idToken->getText() + "\n");
      					syntaxErrorCount++;
      				}
      				_localctx->info.set_line(antlrcpp::downCast<StatementContext *>(_localctx)->printlnToken->getText(), antlrcpp::downCast<StatementContext *>(_localctx)->printlnToken->getLine())
      					->set_line("(", antlrcpp::downCast<StatementContext *>(_localctx)->lparenToken->getLine())
      					->set_line(antlrcpp::downCast<StatementContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<StatementContext *>(_localctx)->idToken->getLine())
      					->set_line(")", antlrcpp::downCast<StatementContext *>(_localctx)->rparenToken->getLine())
      					->set_line(";", antlrcpp::downCast<StatementContext *>(_localctx)->semicolonToken->getLine(), 0, 1);
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n"
      					+ _localctx->info.line + "\n");
      	   
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(332);
      antlrcpp::downCast<StatementContext *>(_localctx)->returnToken = match(C8086Parser::RETURN);
      setState(333);
      antlrcpp::downCast<StatementContext *>(_localctx)->e = expression();
      setState(334);
      antlrcpp::downCast<StatementContext *>(_localctx)->semicolonToken = match(C8086Parser::SEMICOLON);

      				_localctx->info.set_line("return", antlrcpp::downCast<StatementContext *>(_localctx)->returnToken->getLine(), 1, 0)
      					->set_line(antlrcpp::downCast<StatementContext *>(_localctx)->e->info)
      					->set_line(";", antlrcpp::downCast<StatementContext *>(_localctx)->semicolonToken->getLine(), 0, 1);
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": statement : RETURN expression SEMICOLON\n\n"
      					+ _localctx->info.line + "\n");
      	   
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(337);
      antlrcpp::downCast<StatementContext *>(_localctx)->continueToken = match(C8086Parser::CONTINUE);
      setState(338);
      antlrcpp::downCast<StatementContext *>(_localctx)->semicolonToken = match(C8086Parser::SEMICOLON);

      			if(in_loop_check == 0){
      				writeIntoErrorFile("Line No. " + std::to_string(antlrcpp::downCast<StatementContext *>(_localctx)->continueToken->getLine()) 
      					+ ": Continue outside loop\n");
      			}
      			_localctx->info.set_line("continue", antlrcpp::downCast<StatementContext *>(_localctx)->continueToken->getLine())
      				->set_line(";", antlrcpp::downCast<StatementContext *>(_localctx)->semicolonToken->getLine());
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": statement : CONTINUE SEMICOLON SEMICOLON\n\n"
      				+ _localctx->info.line + "\n");
      		
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(340);
      antlrcpp::downCast<StatementContext *>(_localctx)->breakToken = match(C8086Parser::BREAK);
      setState(341);
      antlrcpp::downCast<StatementContext *>(_localctx)->semicolonToken = match(C8086Parser::SEMICOLON);

      			if(in_loop_check == 0){
      				writeIntoErrorFile("Line No. " + std::to_string(antlrcpp::downCast<StatementContext *>(_localctx)->breakToken->getLine()) 
      					+ ": break outside loop\n");
      			}
      			_localctx->info.set_line("break", antlrcpp::downCast<StatementContext *>(_localctx)->breakToken->getLine())
      				->set_line(";", antlrcpp::downCast<StatementContext *>(_localctx)->semicolonToken->getLine());
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": statement : BREAK SEMICOLON SEMICOLON\n\n"
      				+ _localctx->info.line + "\n");
      		
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Expression_statementContext ------------------------------------------------------------------

C8086Parser::Expression_statementContext::Expression_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C8086Parser::Expression_statementContext::SEMICOLON() {
  return getToken(C8086Parser::SEMICOLON, 0);
}

C8086Parser::ExpressionContext* C8086Parser::Expression_statementContext::expression() {
  return getRuleContext<C8086Parser::ExpressionContext>(0);
}

C8086Parser::Expression_errContext* C8086Parser::Expression_statementContext::expression_err() {
  return getRuleContext<C8086Parser::Expression_errContext>(0);
}


size_t C8086Parser::Expression_statementContext::getRuleIndex() const {
  return C8086Parser::RuleExpression_statement;
}

void C8086Parser::Expression_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression_statement(this);
}

void C8086Parser::Expression_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression_statement(this);
}

C8086Parser::Expression_statementContext* C8086Parser::expression_statement() {
  Expression_statementContext *_localctx = _tracker.createInstance<Expression_statementContext>(_ctx, getState());
  enterRule(_localctx, 28, C8086Parser::RuleExpression_statement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(355);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(345);
      antlrcpp::downCast<Expression_statementContext *>(_localctx)->semicolonToken = match(C8086Parser::SEMICOLON);

      				_localctx->info.set_line(";", antlrcpp::downCast<Expression_statementContext *>(_localctx)->semicolonToken->getLine());
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": expression_statement : SEMICOLON\n\n"
      					+ _localctx->info.line + "\n");
      			
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(347);
      antlrcpp::downCast<Expression_statementContext *>(_localctx)->e = expression();
      setState(348);
      antlrcpp::downCast<Expression_statementContext *>(_localctx)->semicolonToken = match(C8086Parser::SEMICOLON);

      				_localctx->info.set_line(antlrcpp::downCast<Expression_statementContext *>(_localctx)->e->info)
      					->set_line(";", antlrcpp::downCast<Expression_statementContext *>(_localctx)->semicolonToken->getLine(), 0, 1);
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": expression_statement : expression SEMICOLON\n\n"
      					+ _localctx->info.line + "\n");
      	   		
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(351);
      antlrcpp::downCast<Expression_statementContext *>(_localctx)->er = expression_err();
      setState(352);
      antlrcpp::downCast<Expression_statementContext *>(_localctx)->semicolonToken = match(C8086Parser::SEMICOLON);

      				_localctx->info.set_line(antlrcpp::downCast<Expression_statementContext *>(_localctx)->er->info)
      					->set_line(";", antlrcpp::downCast<Expression_statementContext *>(_localctx)->semicolonToken->getLine(), 0, 1);
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": expression_statement : expression_err SEMICOLON\n\n"
      					+ _localctx->info.line + "\n");
      				writeIntoErrorFile("Error at line " + std::to_string(_localctx->info.line_no) 
      					+ ": syntax error, unexpected ASSIGNOP");
      					syntaxErrorCount++;
      			
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableContext ------------------------------------------------------------------

C8086Parser::VariableContext::VariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C8086Parser::VariableContext::ID() {
  return getToken(C8086Parser::ID, 0);
}

tree::TerminalNode* C8086Parser::VariableContext::LTHIRD() {
  return getToken(C8086Parser::LTHIRD, 0);
}

tree::TerminalNode* C8086Parser::VariableContext::RTHIRD() {
  return getToken(C8086Parser::RTHIRD, 0);
}

C8086Parser::ExpressionContext* C8086Parser::VariableContext::expression() {
  return getRuleContext<C8086Parser::ExpressionContext>(0);
}

C8086Parser::Expression_errContext* C8086Parser::VariableContext::expression_err() {
  return getRuleContext<C8086Parser::Expression_errContext>(0);
}


size_t C8086Parser::VariableContext::getRuleIndex() const {
  return C8086Parser::RuleVariable;
}

void C8086Parser::VariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable(this);
}

void C8086Parser::VariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable(this);
}

C8086Parser::VariableContext* C8086Parser::variable() {
  VariableContext *_localctx = _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 30, C8086Parser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(372);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(357);
      antlrcpp::downCast<VariableContext *>(_localctx)->idToken = match(C8086Parser::ID);

      		SymbolInfo *temp = symbolTable.Look_Up(antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getText());

      		if(temp == NULL){
      			Param t(antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getText());
      			antlrcpp::downCast<VariableContext *>(_localctx)->param =  t;
      		}else if(temp->get_is_array()){
      			writeIntoparserLogFile("Error at line " + std::to_string(antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getLine()) 
      				+ ": Type mismatch, " + antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getText() + " is an array\n");
      			writeIntoErrorFile("Error at line " + std::to_string(antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getLine()) 
      				+ ": Type mismatch, " + antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getText() + " is an array\n");
      			syntaxErrorCount++;
      		}else{
      			Param t(temp->get_type_specifier(), temp->get_variable_name(), temp->get_is_array(), temp->get_is_func());
      			antlrcpp::downCast<VariableContext *>(_localctx)->param =  t;
      		}

      		_localctx->info.set_line(antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getLine());
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": variable : ID\n\n"
      			+ _localctx->info.line + "\n");
      	 
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(359);
      antlrcpp::downCast<VariableContext *>(_localctx)->idToken = match(C8086Parser::ID);
      setState(360);
      antlrcpp::downCast<VariableContext *>(_localctx)->lthirdToken = match(C8086Parser::LTHIRD);
      setState(361);
      antlrcpp::downCast<VariableContext *>(_localctx)->e = expression();
      setState(362);
      antlrcpp::downCast<VariableContext *>(_localctx)->rthirdToken = match(C8086Parser::RTHIRD);

      		SymbolInfo *temp = symbolTable.Look_Up(antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getText());

      		if(temp == NULL){
      			Param t("error", antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getText(), false, false);
      			antlrcpp::downCast<VariableContext *>(_localctx)->param =  t;
      			writeIntoErrorFile("Error at line " + std::to_string(antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getLine()) 
      				+ ": Undeclared variable " + antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getText() + "\n");
      			syntaxErrorCount++;
      		}else{
      			Param t(temp->get_type_specifier(), temp->get_variable_name(), temp->get_is_array(), temp->get_is_func());
      			antlrcpp::downCast<VariableContext *>(_localctx)->param =  t;
      			if(!temp->get_is_array()){
      				writeIntoparserLogFile("Error at line " + std::to_string(antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getLine()) 
      					+ ": Type mismatch," + antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getText() + " is not an array\n");
      				writeIntoErrorFile("Error at line " + std::to_string(antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getLine()) 
      					+ ": Type mismatch," + antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getText() + " is not an array\n");
      				syntaxErrorCount++;
      			}
      		}

      		if(checkFloat(antlrcpp::downCast<VariableContext *>(_localctx)->e->info.line)){
      			Param t("error", antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getText(), false, false);
      			antlrcpp::downCast<VariableContext *>(_localctx)->param =  t;
      			writeIntoErrorFile("Error at line " + std::to_string(antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getLine()) 
      				+ ": Expression inside third brackets not an integer\n");
      			SemanticErrorCount++;
      		}

      		_localctx->info.set_line(antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getLine())
      			->set_line("[", antlrcpp::downCast<VariableContext *>(_localctx)->lthirdToken->getLine())
      			->set_line(antlrcpp::downCast<VariableContext *>(_localctx)->e->info)
      			->set_line("]", antlrcpp::downCast<VariableContext *>(_localctx)->rthirdToken->getLine());
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": variable : ID LTHIRD expression RTHIRD\n\n");
      		if(checkFloat(antlrcpp::downCast<VariableContext *>(_localctx)->e->info.line)){
      			writeIntoparserLogFile("Error at line " + std::to_string(antlrcpp::downCast<VariableContext *>(_localctx)->e->info.line_no) 
      				+ ": Expression inside third brackets not an integer\n\n"
      				+ _localctx->info.line +"\n");
      		}else{
      			writeIntoparserLogFile(_localctx->info.line + "\n");
      		}
      	
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(365);
      antlrcpp::downCast<VariableContext *>(_localctx)->idToken = match(C8086Parser::ID);
      setState(366);
      antlrcpp::downCast<VariableContext *>(_localctx)->lthirdToken = match(C8086Parser::LTHIRD);
      setState(367);
      antlrcpp::downCast<VariableContext *>(_localctx)->er = expression_err();
      setState(368);
      antlrcpp::downCast<VariableContext *>(_localctx)->rthirdToken = match(C8086Parser::RTHIRD);

      		_localctx->info.set_line(antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<VariableContext *>(_localctx)->idToken->getLine())
      			->set_line("[", antlrcpp::downCast<VariableContext *>(_localctx)->lthirdToken->getLine())
      			->set_line(antlrcpp::downCast<VariableContext *>(_localctx)->er->info)
      			->set_line("]", antlrcpp::downCast<VariableContext *>(_localctx)->rthirdToken->getLine());
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": variable : ID LTHIRD expression_err RTHIRD\n\n");
      		writeIntoErrorFile("Error at line " + std::to_string(_localctx->info.line_no) 
      			+ ": syntax error, unexpected ASSIGNOP\n");
      			syntaxErrorCount++;
      	
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);

      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

C8086Parser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C8086Parser::Logic_expressionContext* C8086Parser::ExpressionContext::logic_expression() {
  return getRuleContext<C8086Parser::Logic_expressionContext>(0);
}

tree::TerminalNode* C8086Parser::ExpressionContext::ASSIGNOP() {
  return getToken(C8086Parser::ASSIGNOP, 0);
}

C8086Parser::VariableContext* C8086Parser::ExpressionContext::variable() {
  return getRuleContext<C8086Parser::VariableContext>(0);
}


size_t C8086Parser::ExpressionContext::getRuleIndex() const {
  return C8086Parser::RuleExpression;
}

void C8086Parser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void C8086Parser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}

C8086Parser::ExpressionContext* C8086Parser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 32, C8086Parser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(382);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(374);
      antlrcpp::downCast<ExpressionContext *>(_localctx)->le = logic_expression();

      			antlrcpp::downCast<ExpressionContext *>(_localctx)->param =  antlrcpp::downCast<ExpressionContext *>(_localctx)->le->param;
      			_localctx->info.set_line(antlrcpp::downCast<ExpressionContext *>(_localctx)->le->info);
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": expression : logic_expression\n\n"
      				+ _localctx->info.line + "\n");
      	   
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(377);
      antlrcpp::downCast<ExpressionContext *>(_localctx)->var = antlrcpp::downCast<ExpressionContext *>(_localctx)->variableContext = variable();
      setState(378);
      antlrcpp::downCast<ExpressionContext *>(_localctx)->assignopToken = match(C8086Parser::ASSIGNOP);
      setState(379);
      antlrcpp::downCast<ExpressionContext *>(_localctx)->le = logic_expression();

      			cout<<"ASSIGNOP "<<_localctx->param.type<<" "<<endl;
      			cout<<"ASSIGNOP "<<antlrcpp::downCast<ExpressionContext *>(_localctx)->le->param.type<<" "<<endl;

      			SymbolInfo *temp = symbolTable.Look_Up(antlrcpp::downCast<ExpressionContext *>(_localctx)->var->param.name);

      			if(temp == NULL){
      				Param t("error", antlrcpp::downCast<ExpressionContext *>(_localctx)->var->param.name, false, false);
      				antlrcpp::downCast<ExpressionContext *>(_localctx)->param =  t;
      				writeIntoparserLogFile("Error at line " + std::to_string(antlrcpp::downCast<ExpressionContext *>(_localctx)->assignopToken->getLine()) 
      					+ ": Undeclared variable " + antlrcpp::downCast<ExpressionContext *>(_localctx)->var->param.name + "\n");
      				writeIntoErrorFile("Error at line " + std::to_string(antlrcpp::downCast<ExpressionContext *>(_localctx)->assignopToken->getLine()) 
      					+ ": Undeclared variable " + antlrcpp::downCast<ExpressionContext *>(_localctx)->var->param.name + "\n");
      				syntaxErrorCount++;
      			}else{
      				Param t(temp->get_type_specifier(), temp->get_variable_name(), temp->get_is_array(), temp->get_is_func());
      				antlrcpp::downCast<ExpressionContext *>(_localctx)->param =  t;
      			}

      			if(antlrcpp::downCast<ExpressionContext *>(_localctx)->variableContext->param.type != antlrcpp::downCast<ExpressionContext *>(_localctx)->le->param.type 
      				&& antlrcpp::downCast<ExpressionContext *>(_localctx)->var->param.type != "error"
      				&& antlrcpp::downCast<ExpressionContext *>(_localctx)->le->param.type != "error"
      				&& !(antlrcpp::downCast<ExpressionContext *>(_localctx)->var->param.type == "bool" && antlrcpp::downCast<ExpressionContext *>(_localctx)->le->param.type == "int")
      				&& !(antlrcpp::downCast<ExpressionContext *>(_localctx)->var->param.type == "int" && antlrcpp::downCast<ExpressionContext *>(_localctx)->le->param.type == "bool")){

      				cout<<"ASSIGNOP1 "<<antlrcpp::downCast<ExpressionContext *>(_localctx)->var->param.type<<" "<<antlrcpp::downCast<ExpressionContext *>(_localctx)->var->info.line<<endl;
      				cout<<"ASSIGNOP1 "<<antlrcpp::downCast<ExpressionContext *>(_localctx)->le->param.type<<" "<<antlrcpp::downCast<ExpressionContext *>(_localctx)->le->info.line<<endl;
      				writeIntoErrorFile("Error at line " + std::to_string(antlrcpp::downCast<ExpressionContext *>(_localctx)->assignopToken->getLine()) 
      					+ ": Type Mismatch\n");
      				SemanticErrorCount++;
      			}
      			_localctx->info.set_line(antlrcpp::downCast<ExpressionContext *>(_localctx)->variableContext->info)
      				->set_line(antlrcpp::downCast<ExpressionContext *>(_localctx)->assignopToken->getText(), antlrcpp::downCast<ExpressionContext *>(_localctx)->assignopToken->getLine())
      				->set_line(antlrcpp::downCast<ExpressionContext *>(_localctx)->le->info);
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": expression : variable ASSIGNOP logic_expression\n\n"
      				+ _localctx->info.line + "\n");
      	   
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Expression_errContext ------------------------------------------------------------------

C8086Parser::Expression_errContext::Expression_errContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C8086Parser::VariableContext* C8086Parser::Expression_errContext::variable() {
  return getRuleContext<C8086Parser::VariableContext>(0);
}

tree::TerminalNode* C8086Parser::Expression_errContext::ADDOP() {
  return getToken(C8086Parser::ADDOP, 0);
}

tree::TerminalNode* C8086Parser::Expression_errContext::ASSIGNOP() {
  return getToken(C8086Parser::ASSIGNOP, 0);
}

C8086Parser::Logic_expressionContext* C8086Parser::Expression_errContext::logic_expression() {
  return getRuleContext<C8086Parser::Logic_expressionContext>(0);
}

tree::TerminalNode* C8086Parser::Expression_errContext::MULOP() {
  return getToken(C8086Parser::MULOP, 0);
}


size_t C8086Parser::Expression_errContext::getRuleIndex() const {
  return C8086Parser::RuleExpression_err;
}

void C8086Parser::Expression_errContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression_err(this);
}

void C8086Parser::Expression_errContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression_err(this);
}

C8086Parser::Expression_errContext* C8086Parser::expression_err() {
  Expression_errContext *_localctx = _tracker.createInstance<Expression_errContext>(_ctx, getState());
  enterRule(_localctx, 34, C8086Parser::RuleExpression_err);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(408);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(384);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->variableContext = variable();
      setState(385);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->addopToken = match(C8086Parser::ADDOP);
      setState(386);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->assignopToken = match(C8086Parser::ASSIGNOP);
      setState(387);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->le = logic_expression();

      		_localctx->info.set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->variableContext->info)
      				->set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->addopToken->getText(), antlrcpp::downCast<Expression_errContext *>(_localctx)->addopToken->getLine())
      				->set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->assignopToken->getText(), antlrcpp::downCast<Expression_errContext *>(_localctx)->assignopToken->getLine())
      				->set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->le->info);
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": expression_err : variable ADDOP ASSIGNOP logic_expression\n\n"
      			+ _localctx->info.line + "\n");
      	
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(390);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->variableContext = variable();
      setState(391);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->assignopToken = match(C8086Parser::ASSIGNOP);
      setState(392);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->addopToken = match(C8086Parser::ADDOP);
      setState(393);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->le = logic_expression();

      		_localctx->info.set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->variableContext->info)
      				->set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->assignopToken->getText(), antlrcpp::downCast<Expression_errContext *>(_localctx)->assignopToken->getLine())
      				->set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->addopToken->getText(), antlrcpp::downCast<Expression_errContext *>(_localctx)->addopToken->getLine())
      				->set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->le->info);
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": expression_err : variable ASSIGNOP ADDOP logic_expression\n\n"
      			+ _localctx->info.line + "\n");
      	
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(396);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->variableContext = variable();
      setState(397);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->mulopToken = match(C8086Parser::MULOP);
      setState(398);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->assignopToken = match(C8086Parser::ASSIGNOP);
      setState(399);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->le = logic_expression();

      		_localctx->info.set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->variableContext->info)
      				->set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->mulopToken->getText(), antlrcpp::downCast<Expression_errContext *>(_localctx)->mulopToken->getLine())
      				->set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->assignopToken->getText(), antlrcpp::downCast<Expression_errContext *>(_localctx)->assignopToken->getLine())
      				->set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->le->info);
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": expression : variable ASSIGNOP logic_expression\n\n"
      			+ _localctx->info.line + "\n");
      	
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(402);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->variableContext = variable();
      setState(403);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->assignopToken = match(C8086Parser::ASSIGNOP);
      setState(404);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->mulopToken = match(C8086Parser::MULOP);
      setState(405);
      antlrcpp::downCast<Expression_errContext *>(_localctx)->le = logic_expression();

      		_localctx->info.set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->variableContext->info)
      				->set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->assignopToken->getText(), antlrcpp::downCast<Expression_errContext *>(_localctx)->assignopToken->getLine())
      				->set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->mulopToken->getText(), antlrcpp::downCast<Expression_errContext *>(_localctx)->mulopToken->getLine())
      				->set_line(antlrcpp::downCast<Expression_errContext *>(_localctx)->le->info);
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": expression : variable ASSIGNOP logic_expression\n\n"
      			+ _localctx->info.line + "\n");
      	
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Logic_expressionContext ------------------------------------------------------------------

C8086Parser::Logic_expressionContext::Logic_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C8086Parser::Rel_expressionContext *> C8086Parser::Logic_expressionContext::rel_expression() {
  return getRuleContexts<C8086Parser::Rel_expressionContext>();
}

C8086Parser::Rel_expressionContext* C8086Parser::Logic_expressionContext::rel_expression(size_t i) {
  return getRuleContext<C8086Parser::Rel_expressionContext>(i);
}

tree::TerminalNode* C8086Parser::Logic_expressionContext::LOGICOP() {
  return getToken(C8086Parser::LOGICOP, 0);
}


size_t C8086Parser::Logic_expressionContext::getRuleIndex() const {
  return C8086Parser::RuleLogic_expression;
}

void C8086Parser::Logic_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic_expression(this);
}

void C8086Parser::Logic_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic_expression(this);
}

C8086Parser::Logic_expressionContext* C8086Parser::logic_expression() {
  Logic_expressionContext *_localctx = _tracker.createInstance<Logic_expressionContext>(_ctx, getState());
  enterRule(_localctx, 36, C8086Parser::RuleLogic_expression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(418);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(410);
      antlrcpp::downCast<Logic_expressionContext *>(_localctx)->re = rel_expression();

      				antlrcpp::downCast<Logic_expressionContext *>(_localctx)->param =  antlrcpp::downCast<Logic_expressionContext *>(_localctx)->re->param;
      				cout<<"logic_expression "<<_localctx->param.type<<" "<<_localctx->param.value<<endl;

      				_localctx->info.set_line(antlrcpp::downCast<Logic_expressionContext *>(_localctx)->re->info);
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": logic_expression : rel_expression\n\n"
      					+ _localctx->info.line + "\n");
      		 
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(413);
      antlrcpp::downCast<Logic_expressionContext *>(_localctx)->re1 = rel_expression();
      setState(414);
      antlrcpp::downCast<Logic_expressionContext *>(_localctx)->logicopToken = match(C8086Parser::LOGICOP);
      setState(415);
      antlrcpp::downCast<Logic_expressionContext *>(_localctx)->re2 = rel_expression();

      			if(antlrcpp::downCast<Logic_expressionContext *>(_localctx)->re1->param.type == "void"){
      				Param t("error", "logic_expression", false, false);
      				antlrcpp::downCast<Logic_expressionContext *>(_localctx)->param =  t;
      				writeIntoErrorFile("Error at Line " + std::to_string(antlrcpp::downCast<Logic_expressionContext *>(_localctx)->re1->info.line_no) 
      					+ ": simple_expression " + antlrcpp::downCast<Logic_expressionContext *>(_localctx)->re1->info.line + " cannot be void\n");
      				SemanticErrorCount++;
      			}else if(antlrcpp::downCast<Logic_expressionContext *>(_localctx)->re2->param.type == "void"){
      				Param t("error", "logic_expression", false, false);
      				antlrcpp::downCast<Logic_expressionContext *>(_localctx)->param =  t;
      				writeIntoErrorFile("Error at Line " + std::to_string(antlrcpp::downCast<Logic_expressionContext *>(_localctx)->re2->info.line_no) 
      					+ ": term " + antlrcpp::downCast<Logic_expressionContext *>(_localctx)->re2->info.line + " cannot be void\n");
      				SemanticErrorCount++;
      			}else{
      				Param t("bool", "logic_expression", false, false);
      				antlrcpp::downCast<Logic_expressionContext *>(_localctx)->param =  t;
      			}

      			_localctx->info.set_line(antlrcpp::downCast<Logic_expressionContext *>(_localctx)->re1->info)
      				->set_line(antlrcpp::downCast<Logic_expressionContext *>(_localctx)->logicopToken->getText(), antlrcpp::downCast<Logic_expressionContext *>(_localctx)->logicopToken->getLine())
      				->set_line(antlrcpp::downCast<Logic_expressionContext *>(_localctx)->re2->info);
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": logic_expression : rel_expression LOGICOP rel_expression\n\n"
      				+ _localctx->info.line + "\n");
      		 
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Rel_expressionContext ------------------------------------------------------------------

C8086Parser::Rel_expressionContext::Rel_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C8086Parser::Simple_expressionContext *> C8086Parser::Rel_expressionContext::simple_expression() {
  return getRuleContexts<C8086Parser::Simple_expressionContext>();
}

C8086Parser::Simple_expressionContext* C8086Parser::Rel_expressionContext::simple_expression(size_t i) {
  return getRuleContext<C8086Parser::Simple_expressionContext>(i);
}

tree::TerminalNode* C8086Parser::Rel_expressionContext::RELOP() {
  return getToken(C8086Parser::RELOP, 0);
}


size_t C8086Parser::Rel_expressionContext::getRuleIndex() const {
  return C8086Parser::RuleRel_expression;
}

void C8086Parser::Rel_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRel_expression(this);
}

void C8086Parser::Rel_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRel_expression(this);
}

C8086Parser::Rel_expressionContext* C8086Parser::rel_expression() {
  Rel_expressionContext *_localctx = _tracker.createInstance<Rel_expressionContext>(_ctx, getState());
  enterRule(_localctx, 38, C8086Parser::RuleRel_expression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(428);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(420);
      antlrcpp::downCast<Rel_expressionContext *>(_localctx)->se = simple_expression(0);

      				antlrcpp::downCast<Rel_expressionContext *>(_localctx)->param =  antlrcpp::downCast<Rel_expressionContext *>(_localctx)->se->param;
      				cout<<"rel "<<_localctx->param.type<<" "<<_localctx->param.value<<endl;

      				_localctx->info.set_line(antlrcpp::downCast<Rel_expressionContext *>(_localctx)->se->info);
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": rel_expression : simple_expression\n\n"
      					+ _localctx->info.line + "\n");
      		
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(423);
      antlrcpp::downCast<Rel_expressionContext *>(_localctx)->se1 = simple_expression(0);
      setState(424);
      antlrcpp::downCast<Rel_expressionContext *>(_localctx)->relopToken = match(C8086Parser::RELOP);
      setState(425);
      antlrcpp::downCast<Rel_expressionContext *>(_localctx)->se2 = simple_expression(0);

      				if(antlrcpp::downCast<Rel_expressionContext *>(_localctx)->se1->param.type == "void"){
      					Param t("error", "rel_expression", false, false);
      					antlrcpp::downCast<Rel_expressionContext *>(_localctx)->param =  t;
      					writeIntoErrorFile("Error at Line " + std::to_string(antlrcpp::downCast<Rel_expressionContext *>(_localctx)->se1->info.line_no) 
      						+ ": simple_expression " + antlrcpp::downCast<Rel_expressionContext *>(_localctx)->se1->info.line + " cannot be void\n");
      					SemanticErrorCount++;
      				}else if(antlrcpp::downCast<Rel_expressionContext *>(_localctx)->se2->param.type == "void"){
      					Param t("error", "rel_expression", false, false);
      					antlrcpp::downCast<Rel_expressionContext *>(_localctx)->param =  t;
      					writeIntoErrorFile("Error at Line " + std::to_string(antlrcpp::downCast<Rel_expressionContext *>(_localctx)->se2->info.line_no) 
      						+ ": term " + antlrcpp::downCast<Rel_expressionContext *>(_localctx)->se2->info.line + " cannot be void\n");
      					SemanticErrorCount++;
      				}else{
      					Param t("bool", "rel_expression", false, false);
      					antlrcpp::downCast<Rel_expressionContext *>(_localctx)->param =  t;
      				}

      				_localctx->info.set_line(antlrcpp::downCast<Rel_expressionContext *>(_localctx)->se1->info)
      					->set_line(antlrcpp::downCast<Rel_expressionContext *>(_localctx)->relopToken->getText(), antlrcpp::downCast<Rel_expressionContext *>(_localctx)->relopToken->getLine())
      					->set_line(antlrcpp::downCast<Rel_expressionContext *>(_localctx)->se2->info);
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": rel_expression : simple_expression RELOP simple_expression\n\n"
      					+ _localctx->info.line + "\n");
      		
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Simple_expressionContext ------------------------------------------------------------------

C8086Parser::Simple_expressionContext::Simple_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C8086Parser::TermContext* C8086Parser::Simple_expressionContext::term() {
  return getRuleContext<C8086Parser::TermContext>(0);
}

tree::TerminalNode* C8086Parser::Simple_expressionContext::ADDOP() {
  return getToken(C8086Parser::ADDOP, 0);
}

C8086Parser::Simple_expressionContext* C8086Parser::Simple_expressionContext::simple_expression() {
  return getRuleContext<C8086Parser::Simple_expressionContext>(0);
}


size_t C8086Parser::Simple_expressionContext::getRuleIndex() const {
  return C8086Parser::RuleSimple_expression;
}

void C8086Parser::Simple_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSimple_expression(this);
}

void C8086Parser::Simple_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSimple_expression(this);
}


C8086Parser::Simple_expressionContext* C8086Parser::simple_expression() {
   return simple_expression(0);
}

C8086Parser::Simple_expressionContext* C8086Parser::simple_expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C8086Parser::Simple_expressionContext *_localctx = _tracker.createInstance<Simple_expressionContext>(_ctx, parentState);
  C8086Parser::Simple_expressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 40;
  enterRecursionRule(_localctx, 40, C8086Parser::RuleSimple_expression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(431);
    antlrcpp::downCast<Simple_expressionContext *>(_localctx)->termContext = term(0);

    				antlrcpp::downCast<Simple_expressionContext *>(_localctx)->param =  antlrcpp::downCast<Simple_expressionContext *>(_localctx)->termContext->param;
    				cout<<"simple_expression "<<_localctx->param.type<<" "<<antlrcpp::downCast<Simple_expressionContext *>(_localctx)->termContext->info.line<<endl;


    				_localctx->info.set_line(antlrcpp::downCast<Simple_expressionContext *>(_localctx)->termContext->info);
    				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
    					+ ": simple_expression : term\n\n"
    					+ _localctx->info.line + "\n");
    		  
    _ctx->stop = _input->LT(-1);
    setState(441);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Simple_expressionContext>(parentContext, parentState);
        _localctx->se = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleSimple_expression);
        setState(434);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(435);
        antlrcpp::downCast<Simple_expressionContext *>(_localctx)->addopToken = match(C8086Parser::ADDOP);
        setState(436);
        antlrcpp::downCast<Simple_expressionContext *>(_localctx)->termContext = term(0);

                  				if(antlrcpp::downCast<Simple_expressionContext *>(_localctx)->se->param.type == "void"){
                  					Param t("error", "simple_expression", false, false);
                  					antlrcpp::downCast<Simple_expressionContext *>(_localctx)->param =  t;
                  					writeIntoErrorFile("Error at Line " + std::to_string(antlrcpp::downCast<Simple_expressionContext *>(_localctx)->se->info.line_no) 
                  						+ ": simple_expression " + antlrcpp::downCast<Simple_expressionContext *>(_localctx)->se->info.line + " cannot be void\n");
                  					SemanticErrorCount++;
                  				}else if(antlrcpp::downCast<Simple_expressionContext *>(_localctx)->termContext->param.type == "void"){
                  					Param t("error", "simple_expression", false, false);
                  					antlrcpp::downCast<Simple_expressionContext *>(_localctx)->param =  t;
                  					writeIntoErrorFile("Error at Line " + std::to_string(antlrcpp::downCast<Simple_expressionContext *>(_localctx)->termContext->info.line_no) 
                  						+ ": term " + antlrcpp::downCast<Simple_expressionContext *>(_localctx)->termContext->info.line + " cannot be void\n");
                  					SemanticErrorCount++;
                  				}else if(antlrcpp::downCast<Simple_expressionContext *>(_localctx)->se->param.type == "float" || antlrcpp::downCast<Simple_expressionContext *>(_localctx)->termContext->param.type ==  "float"){
                  					Param t("float", "simple_expression", false, false);
                  					antlrcpp::downCast<Simple_expressionContext *>(_localctx)->param =  t;
                  				}else{
                  					Param t("int", "simple_expression", false, false);
                  					antlrcpp::downCast<Simple_expressionContext *>(_localctx)->param =  t;
                  				}

                  				_localctx->info.set_line(antlrcpp::downCast<Simple_expressionContext *>(_localctx)->se->info)
                  					->set_line(antlrcpp::downCast<Simple_expressionContext *>(_localctx)->addopToken->getText(), antlrcpp::downCast<Simple_expressionContext *>(_localctx)->addopToken->getLine())
                  					->set_line(antlrcpp::downCast<Simple_expressionContext *>(_localctx)->termContext->info);
                  				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
                  					+ ": simple_expression : simple_expression ADDOP term\n\n"
                  					+ _localctx->info.line + "\n");
                  		   
      }
      setState(443);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- TermContext ------------------------------------------------------------------

C8086Parser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C8086Parser::Unary_expressionContext* C8086Parser::TermContext::unary_expression() {
  return getRuleContext<C8086Parser::Unary_expressionContext>(0);
}

tree::TerminalNode* C8086Parser::TermContext::MULOP() {
  return getToken(C8086Parser::MULOP, 0);
}

C8086Parser::TermContext* C8086Parser::TermContext::term() {
  return getRuleContext<C8086Parser::TermContext>(0);
}


size_t C8086Parser::TermContext::getRuleIndex() const {
  return C8086Parser::RuleTerm;
}

void C8086Parser::TermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTerm(this);
}

void C8086Parser::TermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTerm(this);
}


C8086Parser::TermContext* C8086Parser::term() {
   return term(0);
}

C8086Parser::TermContext* C8086Parser::term(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C8086Parser::TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, parentState);
  C8086Parser::TermContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 42;
  enterRecursionRule(_localctx, 42, C8086Parser::RuleTerm, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(445);
    antlrcpp::downCast<TermContext *>(_localctx)->ue = unary_expression();

    				antlrcpp::downCast<TermContext *>(_localctx)->param =  antlrcpp::downCast<TermContext *>(_localctx)->ue->param;
    				cout<<"term "<<_localctx->param.type<<" "<<_localctx->param.value<<endl;

    				_localctx->info.set_line(antlrcpp::downCast<TermContext *>(_localctx)->ue->info);
    				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
    					+ ": term : unary_expression\n\n"
    					+ _localctx->info.line + "\n");
    	 
    _ctx->stop = _input->LT(-1);
    setState(455);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
        _localctx->tm = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleTerm);
        setState(448);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(449);
        antlrcpp::downCast<TermContext *>(_localctx)->mulopToken = match(C8086Parser::MULOP);
        setState(450);
        antlrcpp::downCast<TermContext *>(_localctx)->ue = unary_expression();


                  				if(antlrcpp::downCast<TermContext *>(_localctx)->tm->param.type == "error" || antlrcpp::downCast<TermContext *>(_localctx)->ue->param.type == "error"){
                  					Param t("error", "term", false, false);
                  					antlrcpp::downCast<TermContext *>(_localctx)->param =  t;
                  				}else if(antlrcpp::downCast<TermContext *>(_localctx)->tm->param.type == "void"){
                  					cout<<2.1<<endl;
                  					Param t("error", "term", false, false);
                  					antlrcpp::downCast<TermContext *>(_localctx)->param =  t;
                  					writeIntoErrorFile("Error at Line " + std::to_string(antlrcpp::downCast<TermContext *>(_localctx)->tm->info.line_no) 
                  						+ ": term " + antlrcpp::downCast<TermContext *>(_localctx)->tm->info.line + " cannot be void\n");
                  					SemanticErrorCount++;
                  					
                  				}else if(antlrcpp::downCast<TermContext *>(_localctx)->ue->param.type == "void"){
                  					cout<<2.2<<endl;
                  					Param t("error", "term", false, false);
                  					antlrcpp::downCast<TermContext *>(_localctx)->param =  t;
                  					writeIntoErrorFile("Error at Line " + std::to_string(antlrcpp::downCast<TermContext *>(_localctx)->tm->info.line_no) 
                  						+ ": term " + antlrcpp::downCast<TermContext *>(_localctx)->tm->info.line + " cannot be void\n");
                  					SemanticErrorCount++;
                  				
                  				}else if((antlrcpp::downCast<TermContext *>(_localctx)->tm->param.type == "float" || antlrcpp::downCast<TermContext *>(_localctx)->ue->param.type ==  "float")
                  							&& antlrcpp::downCast<TermContext *>(_localctx)->mulopToken->getText() == "%"){
                  					cout<<2.3<<" "<<antlrcpp::downCast<TermContext *>(_localctx)->tm->param.type<<" "<<antlrcpp::downCast<TermContext *>(_localctx)->ue->param.type<<endl;
                  					Param t("error", "term", false, false);
                  					antlrcpp::downCast<TermContext *>(_localctx)->param =  t;
                  					cout<<4.3<<" "<<_localctx->param.type<<endl;
                  					writeIntoErrorFile("Error at line " + std::to_string(antlrcpp::downCast<TermContext *>(_localctx)->mulopToken->getLine()) 
                  						+ ": Non-Integer operand on modulus operator\n");
                  					SemanticErrorCount++;

                  				}else if((antlrcpp::downCast<TermContext *>(_localctx)->tm->param.type == "float" || antlrcpp::downCast<TermContext *>(_localctx)->ue->param.type ==  "float")
                  							&& antlrcpp::downCast<TermContext *>(_localctx)->mulopToken->getText() != "%"){
                  					Param t("float", "term", false, false);
                  					antlrcpp::downCast<TermContext *>(_localctx)->param =  t;			
                  				}else {
                  					cout<<2.4<<endl;
                  					Param t("int", "term", false, false);
                  					antlrcpp::downCast<TermContext *>(_localctx)->param =  t;
                  				}
                  				_localctx->info.set_line(antlrcpp::downCast<TermContext *>(_localctx)->tm->info)
                  					->set_line(antlrcpp::downCast<TermContext *>(_localctx)->mulopToken->getText(), antlrcpp::downCast<TermContext *>(_localctx)->mulopToken->getLine())
                  					->set_line(antlrcpp::downCast<TermContext *>(_localctx)->ue->info);
                  				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
                  					+ ": term : term MULOP unary_expression\n\n"
                  					+ _localctx->info.line + "\n");
                  	  
      }
      setState(457);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Unary_expressionContext ------------------------------------------------------------------

C8086Parser::Unary_expressionContext::Unary_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C8086Parser::Unary_expressionContext::ADDOP() {
  return getToken(C8086Parser::ADDOP, 0);
}

C8086Parser::Unary_expressionContext* C8086Parser::Unary_expressionContext::unary_expression() {
  return getRuleContext<C8086Parser::Unary_expressionContext>(0);
}

tree::TerminalNode* C8086Parser::Unary_expressionContext::NOT() {
  return getToken(C8086Parser::NOT, 0);
}

C8086Parser::FactorContext* C8086Parser::Unary_expressionContext::factor() {
  return getRuleContext<C8086Parser::FactorContext>(0);
}


size_t C8086Parser::Unary_expressionContext::getRuleIndex() const {
  return C8086Parser::RuleUnary_expression;
}

void C8086Parser::Unary_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnary_expression(this);
}

void C8086Parser::Unary_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnary_expression(this);
}

C8086Parser::Unary_expressionContext* C8086Parser::unary_expression() {
  Unary_expressionContext *_localctx = _tracker.createInstance<Unary_expressionContext>(_ctx, getState());
  enterRule(_localctx, 44, C8086Parser::RuleUnary_expression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(469);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(458);
      antlrcpp::downCast<Unary_expressionContext *>(_localctx)->addopToken = match(C8086Parser::ADDOP);
      setState(459);
      antlrcpp::downCast<Unary_expressionContext *>(_localctx)->ue = unary_expression();

      				if(antlrcpp::downCast<Unary_expressionContext *>(_localctx)->ue->param.type == "error"){
      					Param t("error", "unary_expression", false, false);
      					antlrcpp::downCast<Unary_expressionContext *>(_localctx)->param =  t;
      				}else if(antlrcpp::downCast<Unary_expressionContext *>(_localctx)->ue->param.type == "void"){
      					Param t("error", "unary_expression", false, false);
      					antlrcpp::downCast<Unary_expressionContext *>(_localctx)->param =  t;
      					writeIntoErrorFile("Error at Line " + std::to_string(antlrcpp::downCast<Unary_expressionContext *>(_localctx)->addopToken->getLine())
      						+ ": unary_expression is void\n");
      					SemanticErrorCount++;
      					
      				}else
      					antlrcpp::downCast<Unary_expressionContext *>(_localctx)->param =  antlrcpp::downCast<Unary_expressionContext *>(_localctx)->ue->param;
      				_localctx->info.set_line(antlrcpp::downCast<Unary_expressionContext *>(_localctx)->addopToken->getText(), antlrcpp::downCast<Unary_expressionContext *>(_localctx)->addopToken->getLine())
      					->set_line(antlrcpp::downCast<Unary_expressionContext *>(_localctx)->ue->info);
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": unary_expression : ADDOP unary_expression\n\n"
      					+ _localctx->info.line + "\n");
      		 
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(462);
      antlrcpp::downCast<Unary_expressionContext *>(_localctx)->notToken = match(C8086Parser::NOT);
      setState(463);
      antlrcpp::downCast<Unary_expressionContext *>(_localctx)->ue = unary_expression();

      			if(antlrcpp::downCast<Unary_expressionContext *>(_localctx)->ue->param.type == "error"){
      				Param t("error", "unary_expression", false, false);
      				antlrcpp::downCast<Unary_expressionContext *>(_localctx)->param =  t;
      			}else if(antlrcpp::downCast<Unary_expressionContext *>(_localctx)->ue->param.type == "void"){
      				Param t("error", "unary_expression", false, false);
      				antlrcpp::downCast<Unary_expressionContext *>(_localctx)->param =  t;
      				writeIntoErrorFile("Error at Line " + std::to_string(antlrcpp::downCast<Unary_expressionContext *>(_localctx)->ue->info.line_no) 
      					+ ": unary_expression " + antlrcpp::downCast<Unary_expressionContext *>(_localctx)->ue->info.line + " cannot be void\n");
      				SemanticErrorCount++;
      			
      			}else
      				antlrcpp::downCast<Unary_expressionContext *>(_localctx)->param =  antlrcpp::downCast<Unary_expressionContext *>(_localctx)->ue->param;

      			_localctx->info.set_line(antlrcpp::downCast<Unary_expressionContext *>(_localctx)->notToken->getText(), antlrcpp::downCast<Unary_expressionContext *>(_localctx)->notToken->getLine())
      				->set_line(antlrcpp::downCast<Unary_expressionContext *>(_localctx)->ue->info);
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": unary_expression : NOT unary_expression\n\n"
      				+ _localctx->info.line + "\n");
      		 
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(466);
      antlrcpp::downCast<Unary_expressionContext *>(_localctx)->factorContext = factor();

      			antlrcpp::downCast<Unary_expressionContext *>(_localctx)->param =  antlrcpp::downCast<Unary_expressionContext *>(_localctx)->factorContext->param;
      			cout<<"factor "<<_localctx->param.type<<" "<<_localctx->param.value<<endl;

      			_localctx->info.set_line(antlrcpp::downCast<Unary_expressionContext *>(_localctx)->factorContext->info);
      			writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      				+ ": unary_expression : factor\n\n"
      				+ _localctx->info.line + "\n");
      	 	 
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FactorContext ------------------------------------------------------------------

C8086Parser::FactorContext::FactorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C8086Parser::VariableContext* C8086Parser::FactorContext::variable() {
  return getRuleContext<C8086Parser::VariableContext>(0);
}

tree::TerminalNode* C8086Parser::FactorContext::ID() {
  return getToken(C8086Parser::ID, 0);
}

tree::TerminalNode* C8086Parser::FactorContext::LPAREN() {
  return getToken(C8086Parser::LPAREN, 0);
}

C8086Parser::Argument_listContext* C8086Parser::FactorContext::argument_list() {
  return getRuleContext<C8086Parser::Argument_listContext>(0);
}

tree::TerminalNode* C8086Parser::FactorContext::RPAREN() {
  return getToken(C8086Parser::RPAREN, 0);
}

C8086Parser::ExpressionContext* C8086Parser::FactorContext::expression() {
  return getRuleContext<C8086Parser::ExpressionContext>(0);
}

tree::TerminalNode* C8086Parser::FactorContext::CONST_INT() {
  return getToken(C8086Parser::CONST_INT, 0);
}

tree::TerminalNode* C8086Parser::FactorContext::CONST_FLOAT() {
  return getToken(C8086Parser::CONST_FLOAT, 0);
}

tree::TerminalNode* C8086Parser::FactorContext::INCOP() {
  return getToken(C8086Parser::INCOP, 0);
}

tree::TerminalNode* C8086Parser::FactorContext::DECOP() {
  return getToken(C8086Parser::DECOP, 0);
}


size_t C8086Parser::FactorContext::getRuleIndex() const {
  return C8086Parser::RuleFactor;
}

void C8086Parser::FactorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFactor(this);
}

void C8086Parser::FactorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFactor(this);
}

C8086Parser::FactorContext* C8086Parser::factor() {
  FactorContext *_localctx = _tracker.createInstance<FactorContext>(_ctx, getState());
  enterRule(_localctx, 46, C8086Parser::RuleFactor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(497);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(471);
      antlrcpp::downCast<FactorContext *>(_localctx)->variableContext = variable();

      				antlrcpp::downCast<FactorContext *>(_localctx)->param =  antlrcpp::downCast<FactorContext *>(_localctx)->variableContext->param;

      				_localctx->info.set_line(antlrcpp::downCast<FactorContext *>(_localctx)->variableContext->info);
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": factor : variable\n\n"
      					+ _localctx->info.line + "\n");
      	
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(474);
      antlrcpp::downCast<FactorContext *>(_localctx)->idToken = match(C8086Parser::ID);
      setState(475);
      antlrcpp::downCast<FactorContext *>(_localctx)->lparenToken = match(C8086Parser::LPAREN);
      setState(476);
      antlrcpp::downCast<FactorContext *>(_localctx)->argument_listContext = argument_list();
      setState(477);
      antlrcpp::downCast<FactorContext *>(_localctx)->rparenToken = match(C8086Parser::RPAREN);

      				SymbolInfo *temp = symbolTable.Look_Up(antlrcpp::downCast<FactorContext *>(_localctx)->idToken->getText());

      				if(temp == NULL){
      					Param t("error", antlrcpp::downCast<FactorContext *>(_localctx)->idToken->getText(), false, false);
      					antlrcpp::downCast<FactorContext *>(_localctx)->param =  t;
      					writeIntoErrorFile("Error at line " + std::to_string(antlrcpp::downCast<FactorContext *>(_localctx)->idToken->getLine()) 
      						+ ": No function named " + antlrcpp::downCast<FactorContext *>(_localctx)->idToken->getText() + " found\n");
      					syntaxErrorCount++;
      				
      				}else{
      					if(!temp->get_is_func()){
      						Param t("error", antlrcpp::downCast<FactorContext *>(_localctx)->idToken->getText(), false, false);
      						antlrcpp::downCast<FactorContext *>(_localctx)->param =  t;
      						writeIntoErrorFile("Error at line " + std::to_string(antlrcpp::downCast<FactorContext *>(_localctx)->idToken->getLine()) 
      							+ ": " + antlrcpp::downCast<FactorContext *>(_localctx)->idToken->getText() + " is not a function\n");
      						SemanticErrorCount++;
      						
      					}else{
      						Param t(temp->get_type_specifier(), temp->get_variable_name(), false, true);
      						antlrcpp::downCast<FactorContext *>(_localctx)->param =  t;
      					}
      				}

      				_localctx->info.set_line(antlrcpp::downCast<FactorContext *>(_localctx)->idToken->getText(), antlrcpp::downCast<FactorContext *>(_localctx)->idToken->getLine())
      					->set_line("(", antlrcpp::downCast<FactorContext *>(_localctx)->lparenToken->getLine())
      					->set_line(antlrcpp::downCast<FactorContext *>(_localctx)->argument_listContext->info)
      					->set_line(")", antlrcpp::downCast<FactorContext *>(_localctx)->rparenToken->getLine());
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": factor : ID LPAREN argument_list RPAREN\n\n"
      					+ _localctx->info.line + "\n");
      	
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(480);
      antlrcpp::downCast<FactorContext *>(_localctx)->lparenToken = match(C8086Parser::LPAREN);
      setState(481);
      antlrcpp::downCast<FactorContext *>(_localctx)->e = expression();
      setState(482);
      antlrcpp::downCast<FactorContext *>(_localctx)->rparenToken = match(C8086Parser::RPAREN);

      				antlrcpp::downCast<FactorContext *>(_localctx)->param =  antlrcpp::downCast<FactorContext *>(_localctx)->e->param;
      				_localctx->info.set_line("(", antlrcpp::downCast<FactorContext *>(_localctx)->lparenToken->getLine())
      					->set_line(antlrcpp::downCast<FactorContext *>(_localctx)->e->info)
      					->set_line(")", antlrcpp::downCast<FactorContext *>(_localctx)->rparenToken->getLine());
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": factor : LPAREN expression RPAREN\n\n"
      					+ _localctx->info.line + "\n");
      	
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(485);
      antlrcpp::downCast<FactorContext *>(_localctx)->const_intToken = match(C8086Parser::CONST_INT);

      				_localctx->param.type = "int";
      				_localctx->param.value = antlrcpp::downCast<FactorContext *>(_localctx)->const_intToken->getText();
      				_localctx->info.set_line(antlrcpp::downCast<FactorContext *>(_localctx)->const_intToken->getText(), antlrcpp::downCast<FactorContext *>(_localctx)->const_intToken->getLine());
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": factor : CONST_INT\n\n"
      					+ _localctx->info.line + "\n");
      	
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(487);
      antlrcpp::downCast<FactorContext *>(_localctx)->const_floatToken = match(C8086Parser::CONST_FLOAT);

      				_localctx->param.type = "float";
      				_localctx->param.value = antlrcpp::downCast<FactorContext *>(_localctx)->const_floatToken->getText();
      				_localctx->info.set_line(antlrcpp::downCast<FactorContext *>(_localctx)->const_floatToken->getText(), antlrcpp::downCast<FactorContext *>(_localctx)->const_floatToken->getLine());
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": factor : CONST_FLOAT\n\n"
      					+ _localctx->info.line + "\n");
      	
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(489);
      antlrcpp::downCast<FactorContext *>(_localctx)->variableContext = variable();
      setState(490);
      antlrcpp::downCast<FactorContext *>(_localctx)->incopToken = match(C8086Parser::INCOP);

      				if(antlrcpp::downCast<FactorContext *>(_localctx)->variableContext->param.type == "error"){
      					Param t("error", "variable", false, false);
      					antlrcpp::downCast<FactorContext *>(_localctx)->param =  t;
      				}else if(antlrcpp::downCast<FactorContext *>(_localctx)->variableContext->param.type == "void"){
      					Param t("error", "variable", false, false);
      					antlrcpp::downCast<FactorContext *>(_localctx)->param =  t;
      					writeIntoErrorFile("Error at Line " 
      						+ std::to_string(antlrcpp::downCast<FactorContext *>(_localctx)->variableContext->info.line_no) + ": Can not increment void variable "
      						+ antlrcpp::downCast<FactorContext *>(_localctx)->variableContext->info.line + "\n");
      					SemanticErrorCount++;
      					
      				}else{
      					
      					antlrcpp::downCast<FactorContext *>(_localctx)->param =  antlrcpp::downCast<FactorContext *>(_localctx)->variableContext->param;
      				}
      				_localctx->info.set_line(antlrcpp::downCast<FactorContext *>(_localctx)->variableContext->info)
      					->set_line(antlrcpp::downCast<FactorContext *>(_localctx)->incopToken->getText(), antlrcpp::downCast<FactorContext *>(_localctx)->incopToken->getLine());
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": factor : variable INCOP\n\n"
      					+ _localctx->info.line + "\n");
      	
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(493);
      antlrcpp::downCast<FactorContext *>(_localctx)->variableContext = variable();
      setState(494);
      antlrcpp::downCast<FactorContext *>(_localctx)->decopToken = match(C8086Parser::DECOP);

      		if(antlrcpp::downCast<FactorContext *>(_localctx)->variableContext->param.type == "error"){
      			Param t("error", "variable", false, false);
      			antlrcpp::downCast<FactorContext *>(_localctx)->param =  t;
      		}if(antlrcpp::downCast<FactorContext *>(_localctx)->variableContext->param.type == "void"){
      			Param t("error", "variable", false, false);
      			antlrcpp::downCast<FactorContext *>(_localctx)->param =  t;
      			writeIntoErrorFile("Error at Line " 
      				+ std::to_string(antlrcpp::downCast<FactorContext *>(_localctx)->variableContext->info.line_no) + ": Can not decrement void variable "
      				+ antlrcpp::downCast<FactorContext *>(_localctx)->variableContext->info.line + "\n");
      			SemanticErrorCount++;

      		}else{
      			
      			antlrcpp::downCast<FactorContext *>(_localctx)->param =  antlrcpp::downCast<FactorContext *>(_localctx)->variableContext->param;
      		}
      		_localctx->info.set_line(antlrcpp::downCast<FactorContext *>(_localctx)->variableContext->info)
      			->set_line(antlrcpp::downCast<FactorContext *>(_localctx)->decopToken->getText(), antlrcpp::downCast<FactorContext *>(_localctx)->decopToken->getLine());
      		writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      			+ ": factor : variable DECOP\n\n"
      			+ _localctx->info.line + "\n");
      	
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Argument_listContext ------------------------------------------------------------------

C8086Parser::Argument_listContext::Argument_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C8086Parser::ArgumentsContext* C8086Parser::Argument_listContext::arguments() {
  return getRuleContext<C8086Parser::ArgumentsContext>(0);
}


size_t C8086Parser::Argument_listContext::getRuleIndex() const {
  return C8086Parser::RuleArgument_list;
}

void C8086Parser::Argument_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgument_list(this);
}

void C8086Parser::Argument_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgument_list(this);
}

C8086Parser::Argument_listContext* C8086Parser::argument_list() {
  Argument_listContext *_localctx = _tracker.createInstance<Argument_listContext>(_ctx, getState());
  enterRule(_localctx, 48, C8086Parser::RuleArgument_list);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(503);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(499);
      antlrcpp::downCast<Argument_listContext *>(_localctx)->argumentsContext = arguments(0);

      				_localctx->info.set_line(antlrcpp::downCast<Argument_listContext *>(_localctx)->argumentsContext->info);
      				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
      					+ ": argument_list : arguments\n\n"
      					+ _localctx->info.line + "\n");
      			  
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);

      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

C8086Parser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C8086Parser::Logic_expressionContext* C8086Parser::ArgumentsContext::logic_expression() {
  return getRuleContext<C8086Parser::Logic_expressionContext>(0);
}

tree::TerminalNode* C8086Parser::ArgumentsContext::COMMA() {
  return getToken(C8086Parser::COMMA, 0);
}

C8086Parser::ArgumentsContext* C8086Parser::ArgumentsContext::arguments() {
  return getRuleContext<C8086Parser::ArgumentsContext>(0);
}


size_t C8086Parser::ArgumentsContext::getRuleIndex() const {
  return C8086Parser::RuleArguments;
}

void C8086Parser::ArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArguments(this);
}

void C8086Parser::ArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C8086ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArguments(this);
}


C8086Parser::ArgumentsContext* C8086Parser::arguments() {
   return arguments(0);
}

C8086Parser::ArgumentsContext* C8086Parser::arguments(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C8086Parser::ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, parentState);
  C8086Parser::ArgumentsContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 50;
  enterRecursionRule(_localctx, 50, C8086Parser::RuleArguments, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(506);
    antlrcpp::downCast<ArgumentsContext *>(_localctx)->le = logic_expression();

    				_localctx->info.set_line(antlrcpp::downCast<ArgumentsContext *>(_localctx)->le->info);
    				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
    					+ ": arguments : logic_expression\n\n"
    					+ _localctx->info.line + "\n");
    		  
    _ctx->stop = _input->LT(-1);
    setState(516);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ArgumentsContext>(parentContext, parentState);
        _localctx->args = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleArguments);
        setState(509);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(510);
        antlrcpp::downCast<ArgumentsContext *>(_localctx)->commaToken = match(C8086Parser::COMMA);
        setState(511);
        antlrcpp::downCast<ArgumentsContext *>(_localctx)->le = logic_expression();

                  				_localctx->info.set_line(antlrcpp::downCast<ArgumentsContext *>(_localctx)->args->info)
                  					->set_line(antlrcpp::downCast<ArgumentsContext *>(_localctx)->commaToken->getText(), antlrcpp::downCast<ArgumentsContext *>(_localctx)->commaToken->getLine())
                  					->set_line(antlrcpp::downCast<ArgumentsContext *>(_localctx)->le->info);
                  				writeIntoparserLogFile("Line " + std::to_string(_localctx->info.line_no)
                  					+ ": arguments : arguments COMMA logic_expression\n\n"
                  					+ _localctx->info.line + "\n");
                  		   
      }
      setState(518);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool C8086Parser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 1: return programSempred(antlrcpp::downCast<ProgramContext *>(context), predicateIndex);
    case 5: return parameter_list_errSempred(antlrcpp::downCast<Parameter_list_errContext *>(context), predicateIndex);
    case 6: return parameter_listSempred(antlrcpp::downCast<Parameter_listContext *>(context), predicateIndex);
    case 9: return declaration_list_errSempred(antlrcpp::downCast<Declaration_list_errContext *>(context), predicateIndex);
    case 11: return declaration_listSempred(antlrcpp::downCast<Declaration_listContext *>(context), predicateIndex);
    case 12: return statementsSempred(antlrcpp::downCast<StatementsContext *>(context), predicateIndex);
    case 20: return simple_expressionSempred(antlrcpp::downCast<Simple_expressionContext *>(context), predicateIndex);
    case 21: return termSempred(antlrcpp::downCast<TermContext *>(context), predicateIndex);
    case 25: return argumentsSempred(antlrcpp::downCast<ArgumentsContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool C8086Parser::programSempred(ProgramContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool C8086Parser::parameter_list_errSempred(Parameter_list_errContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

bool C8086Parser::parameter_listSempred(Parameter_listContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 4);
    case 3: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

bool C8086Parser::declaration_list_errSempred(Declaration_list_errContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool C8086Parser::declaration_listSempred(Declaration_listContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 5: return precpred(_ctx, 4);
    case 6: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

bool C8086Parser::statementsSempred(StatementsContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 7: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool C8086Parser::simple_expressionSempred(Simple_expressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 8: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool C8086Parser::termSempred(TermContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 9: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool C8086Parser::argumentsSempred(ArgumentsContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 10: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

void C8086Parser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  c8086parserParserInitialize();
#else
  ::antlr4::internal::call_once(c8086parserParserOnceFlag, c8086parserParserInitialize);
#endif
}
