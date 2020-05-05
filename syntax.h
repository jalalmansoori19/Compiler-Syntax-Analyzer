#ifndef  SYNTAX_H
#define	 SYNTAX_H	
#include <string>
using namespace std;

class SyntaxAnalyzer{
	
	private:
	
	string s;	
	bool isChar(char c);
    bool isSymbol(char c);
	bool isString(char c);		
	bool checkKeyword(string word);
	void generateToken(string word, char c);
	bool checkIdentifier(string word);
	
	//Assignment # 3
	
	bool start(string returnType);
	bool DataType(string returnType);
	
	public:
	
	void setSourceCode(string code);
	void display();
	void separateWords();
	
	//Assignment# 3
	
	//for Functions Declaration and calling
	int getSize();
	int funcDeclaration(string array[]);
	int funcCalling(string array[]);
	string getError();
	void check();
	
	//for Conditional Statements
	int ifConditional(string array[], int pos);
	bool isOperand(string word);		
	bool isOperator(string word);
	
	//For Switch Case
	int switchCaseCalling(string array[]);
	
	//For Loop
	int whileLoopCalling(string array[], int pos);
	int whileLoopDefinition(string array[]);
	bool checkString(string word);
	string getStringToken();
	void setCountZero();
	int getValue();
	
};

#endif
