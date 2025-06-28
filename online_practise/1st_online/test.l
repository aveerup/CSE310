%option noyywrap

%x in_vector
%x in_param

%{

#include<bits/stdc++.h>
using namespace std;

ofstream flog;
ofstream ftoken;

string current_lexeme;

int depth = 0;

int line_count = 1;
int current_line_count = 0;

int error_count = 0;

stack<char> s;

%}

ws "\t"|" "|"\r"|"\v"|"\f"
newline "\n"|"\r\n"
lparen "("
rparen ")"
lcurl "{"
rcurl "}"
lthird "["
rthird "]"

%%

{ws}+ {}
{newline} {
    if(s.empty())
            flog<<"matched brackets"<<endl;
}

<<EOF>> {
    if(s.empty())
            flog<<"matched brackets"<<endl;
    return 0;
}

{lparen} {
    s.push('(');
}

{lcurl} {
    s.push('{');
}

{lthird} {
    s.push('[');
}

{rparen} {
    if(s.top() == '('){
        s.pop();
        
    }else
        flog<<"unmatched brackets"<<endl;
}

{rcurl} {
    if(s.top() == '{'){
        s.pop();
        // if(s.empty())
        //     flog<<"matched brackets"<<endl;
    }else
        flog<<"unmatched brackets"<<endl;
}

{rthird} {
    if(s.top() == '['){
        s.pop();
     
    }else
        flog<<"unmatched brackets"<<endl;
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

    flog.close();
    ftoken.close();

    return 0;
}