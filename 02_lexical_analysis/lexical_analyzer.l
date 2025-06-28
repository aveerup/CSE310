%option noyywrap

%x initiate_single_line_comment
%x initiate_multi_line_comment
%x initiate_string
%x initiate_const_char

%{

#include<bits/stdc++.h>
#include "../01_symbol_table/SymbolTable.cpp"
using namespace std;

ofstream flog;
ofstream ftoken;

string current_lexeme;

int line_count = 0;
int current_line_count = 0;

int comment_count = 0;
int single_line_comment_count = 0;
int multi_line_comment_count = 0;

int error_count = 0;

int num_buckets = 7;
SymbolTable* symbolTable = new SymbolTable(num_buckets, &flog, "SDBM"); 

string make_all_capital_letter(string str){
    for(int i=0; i < str.length(); i++){
        if('a' <= str[i] && str[i] <= 'z'){
            str[i] = 'A' + str[i] - 'a'; 
        }
    }

    return str;
}

string make_all_small_letter(string str){
    for(int i=0; i < str.length(); i++){
        if('A' <= str[i] && str[i] <= 'Z'){
            str[i] = 'a' + str[i] - 'A'; 
        }
    }

    return str;
}

string make_keyword_token(string keyword){
    return "<" + make_all_capital_letter(keyword) + ">";
}

string get_character_literal(char const_char){
    switch(const_char){
        case 'n':
            return "\n";
            break;
        case 't':
            return "\t";
            break;
        case '\\':
            return "\\";
            break;
        case '\'':
            return "'";
            break;
        case 'a':
            return "\a";
            break;
        case 'f':
            return "\f";
            break;
        case 'r':
            return "\r";
            break;
        case 'b':
            return "\b";
            break;
        case 'v':
            return "\v";
            break;
        case '0':
            return "\0";
            break;
        case '\"':
            return "\"";
            break;
        default:
            return "no match"; 
            break;
    }
}

void handle_error(string error_msg, int current_line_count){
    error_count++;
    flog<<"Error at line no " + to_string(current_line_count) + ": ";
    flog<<error_msg<<endl<<endl;
}

void print_tokens(string token){
    ftoken<<token<<" ";

    int middle_reached = 0;
    string type = "", name = "";
    for( int i = 0; i < token.length(); i++){
        if(token[i] == ' ' && (token[i-1] == '<' || token[i+1] == ',' || token[i+1] == '>'))
            continue;

        if(token[i] == ','){
            middle_reached = 1;
        }else if(middle_reached == 0 && token[i] != '<' && token[i] != '>' ){
            type += token[i];
        }else if(middle_reached == 1 && token[i] != '>'){
            name += token[i];
        }
    }

    if(name == ""){
        name = make_all_small_letter(type);
    }

    flog<<"Line no "<<to_string(line_count + 1)<<": Token <"<<type<<"> Lexeme "<<name<<" found"<<endl<<endl;

    if(type == "ID" || type == "CONST_INT" || type == "CONST_FLOAT"){
        symbolTable->Insert(name, type);
        symbolTable->Print_All();
    }
}

string make_string_token(string str){
    return "<STRING, " + str + ">";
}

%}

ws " "|"\t"|"\f"|"\r"|"\v"
newline "\n"|"\r\n"

keyword "if"|"for"|"do"|"int"|"float"|"void"|"switch"|"default"|"else"|"while"|"break"|"char"|"double"|"return"|"case"|"continue"|"goto"|"long"|"short"|"static"|"unsigned"
addop "+"|"-"
mulop "*"|"/"|"%"
incop "++"|"--"
relop "<"|"<="|">"|">="|"=="|"!="
assignop "="
logicop "&&"|"||"
not "!"
comma ","
semicolon ";"
lparen "("
rparen ")"
lcurl "{"
rcurl "}"
lthird "["
rthird "]"
underscore "_"
digits [0-9]
letters [a-zA-Z]
single_quote "\'"
double_quote "\""
any_other_character .

const_int {digits}+
const_float {digits}*(\.{digits}+)?("E"[+-]?{digits}+)?
identifier ({letters}|{underscore})+({digits}|{letters}|{underscore})*
single_line_comment "\/\/"
multi_line_comment  "\/\*"
character_literal "\\"({letters}|"\\"|"'"|"0"|"\"")

error_more_than_one_decimal {digits}*\.{digits}(\.{digits})+
error_ill_formed_number {digits}*(\.{digits}+)*"E"[+-]?{digits}*(\.{digits}*)+
error_invalid_character_sequence {digits}+({letters}|{digits}|{underscore})*({letters}|{underscore})+

%%

{ws}+ {
                cout<<yytext;
            }

{keyword} {
                cout<<yytext;
                print_tokens(make_keyword_token(yytext));
            }

{lparen} {
                cout<<yytext;
                print_tokens("<LPAREN, (>");
            }

{rparen} {
                cout<<yytext;
                print_tokens("<RPAREN, )>");
            }

{lcurl} {
                cout<<yytext;
                print_tokens("<LCURL, {>");
                symbolTable->Enter_Scope();
            }

{rcurl} {
                cout<<yytext;
                print_tokens("<RCURL, }>");
                symbolTable->Exit_Scope();
            }

{lthird} {
                cout<<yytext;
                print_tokens("<LTHIRD, [>");
            }

{rthird} {
                cout<<yytext;
                print_tokens("<RTHIRD, ]>");
            }

{addop} {
                cout<<yytext;
                current_lexeme = yytext;
                print_tokens("<ADDOP, "+current_lexeme+">");
            }

{mulop} {
                cout<<yytext;
                current_lexeme = yytext;
                print_tokens("<MULOP, "+current_lexeme+">");
            }

{incop} {
                cout<<yytext;
                current_lexeme = yytext;
                print_tokens("<INCOP, "+current_lexeme+">");
            }

{relop} {
                cout<<yytext;
                current_lexeme = yytext;
                print_tokens("<RELOP, "+current_lexeme+">");
            }

{assignop} {
                cout<<yytext;
                current_lexeme = yytext;
                print_tokens("<ASSIGNOP, "+current_lexeme+">");
            }

{logicop} {
                cout<<yytext;
                current_lexeme = yytext;
                print_tokens("<LOGICOP, "+current_lexeme+">");
            }

{comma} {
                cout<<yytext;
                print_tokens("<COMMA, ,>");
            }

{semicolon} {
                cout<<yytext;
                print_tokens("<SEMICOLON, ;>");
            }

{not} {
                cout<<yytext;
                print_tokens("<NOT, !>");
            }

{const_int} {
                cout<<yytext;
                current_lexeme = yytext;
                print_tokens("<CONST_INT, "+current_lexeme+">");
            }

{const_float} {
                cout<<yytext;
                current_lexeme = yytext;
                print_tokens("<CONST_FLOAT, "+current_lexeme+">");
            }

{identifier} {
                cout<<yytext;
                current_lexeme = yytext;
                print_tokens("<ID, "+current_lexeme+">");
            }

{newline} {
                cout<<yytext;
                line_count++;
            }

{single_line_comment} {
                cout<<yytext;
                BEGIN initiate_single_line_comment;
            }

<initiate_single_line_comment>{

    "\\"{newline} {
                    cout<<yytext;
                    line_count++;
                }

    {newline} {
                    cout<<yytext;
                    comment_count++;
                    single_line_comment_count++;
                    line_count++;
                    BEGIN INITIAL;
                }

    <<EOF>> {
                    cout<<yytext;
                    comment_count++;
                    single_line_comment_count++;
                    line_count++;
                    BEGIN INITIAL;
                }

}

{multi_line_comment} {
                cout<<yytext;
                current_lexeme = yytext;
                current_line_count = line_count + 1;
                BEGIN initiate_multi_line_comment;
            }

<initiate_multi_line_comment>{

    "\*\/" {
                    cout<<yytext;
                    comment_count++;
                    multi_line_comment_count++;
                    BEGIN INITIAL;
                }

    <<EOF>> {
                    string error_msg = "Unterminated comment ";
                    error_msg += current_lexeme;
                    handle_error(error_msg, current_line_count);
                    BEGIN INITIAL;
                }

    [^\n] {
                    cout<<yytext;
                    current_lexeme += yytext;
                }

    {newline} {
                    cout<<yytext;
                    current_lexeme += yytext;
                    line_count++;
                }

}

{double_quote} {
                cout<<yytext;
                current_lexeme = "";
                current_line_count = line_count + 1;
                BEGIN initiate_string;
            }

<initiate_string>{

    {character_literal} {
        string temp = get_character_literal(yytext[1]);
        if(temp != "no match"){
            current_lexeme += temp;
        }else{
            string invalid_term = yytext;
            handle_error("invalid escape sequence " + invalid_term, current_line_count);
            BEGIN INITIAL;
        }
    }
    
    {double_quote} {
                    print_tokens(make_string_token(current_lexeme));
                    BEGIN INITIAL;
                }

    "\\"{newline} {
                    line_count++;

                }

    "\\"{ws}+{newline} {
                    cout<<yytext;
                    line_count++;
                    handle_error("backslash and newline separated by space", current_line_count);
                }

    {newline} {
                    cout<<yytext;
                    line_count++;
                    string error_msg = "Unterminated string ";
                    error_msg += "\"";
                    error_msg += current_lexeme;
                    handle_error(error_msg, current_line_count);
                    BEGIN INITIAL;
                }

    [^\n\"\\] {
        cout<<yytext;
        current_lexeme += yytext;
                }

}

{single_quote} {
    cout<<yytext;
    current_lexeme = "";
    current_line_count = line_count + 1;
    BEGIN initiate_const_char;
}

<initiate_const_char>{

    ({letters}|{digits})"'" {
        cout<<yytext;
        current_lexeme = "";
        current_lexeme += yytext[0];
        print_tokens("<CONST_CHAR, " + current_lexeme + ">");
        BEGIN INITIAL;
    }

    "'" {
        cout<<yytext;
        current_lexeme = "";
        print_tokens("<CONST_CHAR, " + current_lexeme + ">");
        BEGIN INITIAL;
    }

    {character_literal}"'" {
        cout<<yytext;
        current_lexeme = get_character_literal(yytext[1]);
        if( current_lexeme == "no match"){
            string error_msg = "Invalid character literal ";
            error_msg += "'";
            error_msg += yytext;
            handle_error(error_msg, current_line_count);
            BEGIN INITIAL;
        }else{
            print_tokens("<CONST_CHAR, " + current_lexeme + ">");
            BEGIN INITIAL;
        }  
    }

    ([^\n\\\']*{character_literal}*)+{newline} {
        cout<<yytext;
        string error_msg = "Unterminated character ";
        error_msg += "\'";
        error_msg += yytext;
        handle_error(error_msg, current_line_count);
        line_count++;
        BEGIN INITIAL;  
    }

    ([^\n\\\']|{character_literal})([^\n\\\']|{character_literal})+"'" {
        cout<<yytext;
        string error_msg = "Multi character constant error ";
        error_msg += "'";
        error_msg += yytext;
        handle_error(error_msg, current_line_count);
        BEGIN INITIAL;
    }

}

{single_quote}{single_quote} {
                cout<<yytext;
                string error_msg = "Empty character constant error ";
                error_msg += yytext;
                handle_error(error_msg, line_count + 1);
            }

{error_more_than_one_decimal} {
                cout<<yytext;
                string error_msg = "Too many decimal points ";
                error_msg += yytext;
                handle_error(error_msg, line_count + 1);
            }

{error_ill_formed_number} {
                cout<<yytext;
                string error_msg = "Ill formed number ";
                error_msg += yytext;
                handle_error(error_msg, line_count + 1);
            }

{error_invalid_character_sequence} {
                cout<<yytext;
                string error_msg = "Invalid prefix on ID or invalid suffix on Number ";
                error_msg += yytext;
                handle_error(error_msg, line_count + 1);
            }

<<EOF>> {
                cout<<endl;
                line_count++;
                symbolTable->Print_All();
                return 0;
            }

{any_other_character} {
                cout<<yytext;
                string error_msg = "Unrecognized character ";
                error_msg += yytext;
                handle_error(error_msg, line_count + 1);
            }

%%

int main(int argc,char *argv[]){

	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}

	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}

	flog.open("2105112_log.txt");
	ftoken.open("2105112_token.txt");
	
    yyin= fin;
	yylex();
	fclose(yyin);
	
    cout<<"Total lines : "<<line_count<<endl;
    flog<<"Total lines: "<<line_count<<endl;
    cout<<"total comment count: "<<comment_count<<endl;
    cout<<"single line comment count: "<<single_line_comment_count<<endl;
    cout<<"multi line comment count: "<<multi_line_comment_count<<endl;
    cout<<"Total errors : "<<error_count<<endl;
    flog<<"Total errors: "<<error_count<<endl;

    flog.close();
    ftoken.close();

    return 0;
}