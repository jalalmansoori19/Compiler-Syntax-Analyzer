#include <iostream>
#include <string>
#include <fstream>
#include "syntax.h"
#define SIZE 10
using namespace std;

int id=0;
int keyW=0;
int sym=0;
int str=0;
int lit=0; 

int openP=0;
int closeP=0;
int semicolon=0;
int openB=0;
int closeB=0;

ofstream myFile;
int count=0;
string nameOfError="";
string tokenString="";
			
string keyword[SIZE]={"numbers", "decimals", "words", 	"if", 
                  "else", "check", "expr"	"stop", "repeatTill","send"
				 };

//Functions Definitions
void SyntaxAnalyzer::setSourceCode(string code)
{
	s=code;

}
//Display Source Code
void SyntaxAnalyzer::display()
{
	cout<<s<<endl;
	
}
void SyntaxAnalyzer::separateWords()
{
	int index=0;
	char c;
	string word="";
	
	myFile.open("generatedTokens.txt");
	
	
	while(index < s.length() ) // In String length there is extra increase of length by 2
	{
		c=s.at(index);
	
		if(isChar(c))
		{
			word=word+c;
			
		}
		
		if(isString(c))
		{
			word=word+c;
			while(true)
			{	
				index++;
				c=s.at(index);
				word=word+c;
				if(c== 34)
				{
					//Generates String "Hello World !"
					//cout<<word<<endl;
					generateToken(word, 'S');
					
					
					
					word="";
					break;
				}
				
			}
		}
		
		if(isSymbol(c) || c == 32  ) 
		{
			
			if(word != "")
			{//Generates Keyword or Identifier
			//cout<<word<<endl;	
			
				if(checkKeyword(word) == true)
				{
					generateToken(word, 'K');
					
					
				}
				//Checking Identifier repective to Regular Expression
				else if(checkIdentifier(word)  == true)
				{
					generateToken(word, 'I');
					
					
				}
				else
				{
					//For Constants
					generateToken(word, 'L');
					
				
				}
				word="";	
			}
				
			
			if(c!=32)
			{
				//For Logical Operator e.g == , !=, >=, <=
				if((c== '='|| c=='>' || c=='<' || c=='!') && '='==s.at(index+1) || c=='|' || c=='&')
				{	
				string logical_O="";
				logical_O +=c;
				logical_O +=s.at(index+1);
				generateToken(logical_O, 'O');
				
				//cout<<logical_O<<endl;
				index++;
				}
				else if(c!=10)
				{
					//Generates Symbols like *,-,/...etc
					//cout<<c<<endl;
					string s(1, c); // Casting char into string
					generateToken(s, 'O');
					
					
				}
				
			}
				
		}
		
		index++;
				
	} 
	

	myFile.close();
}

bool SyntaxAnalyzer::isChar(char c)
{
	if((c>=65 && c<=90) ||  (c>=97 && c<=122) ||  (c>=48 && c<=57) )
	{
		return true;
	}
	return false;
}

bool SyntaxAnalyzer::isSymbol(char c)
{
	//c==10 for printing last character
	if((c>=35 && c<=47) || c==33 || c == 10 || (c>=58 && c<=64) || (c>=91 && c<=96) || (c>=123 && c<=125))
	{
		return true;
	}
	return false;
}

bool SyntaxAnalyzer::isString(char c)
{
	if(c == 34)
	{
		return true;
	}
	return false;
}

bool SyntaxAnalyzer::checkKeyword(string word)
{
	for(int i=0; i<SIZE; i++)
	{
		if(keyword[i] == word)
		{
			return true;
		}
	}
	return false;
}

void SyntaxAnalyzer::generateToken(string word, char c)
{
	if(word=="(")
	{
		openP++;
	}
	else if(word==")")
	{
		closeP++;
	}
	else if(word==";")
	{
		semicolon++;
	}
	else if(word== "{")
	{
		openB++;
	}
	else if(word=="}")
	{
		closeB++;
	}
	
	
	
	myFile<<word<<"\n";
	
	if(word.at(0) == 34)
	{
		tokenString=word;
	}
	
	count++;
	switch(c)
	{
		case'K':
		keyW++;
		//cout<<"< Keyword#"<<keyW<<", "<<word<<" >\n"<<endl;
		
		break;
		
		case'I':
		id++;
		//cout<<"< Idenfier#"<<id<<", "<<word<<" >\n"<<endl;
		
		break;
		
		case'O':
		sym++;
		//cout<<"< Symbol#"<<sym<<", "<<word<<" >\n"<<endl;
		
		break;
		
		case'S':
		str++;
		//cout<<"< String#"<<str<<", "<<word<<" >\n"<<endl;
		
		break;
		
		case'L':
		lit++;
		//cout<<"< Literals#"<<lit<<", "<<word<<" >\n"<<endl;
		
		break;
		
	}
	
	
}

bool SyntaxAnalyzer::checkIdentifier(string word)
{
	//If string starts from letters a, b,c..z or A, B, ..z
	if((word.at(0)>=65 && word.at(0)<=90) || (word.at(0)>=97 && word.at(0)<=122) )
	{
		//Checking for string such assasd!# which is not accepted
		for(int i=1; i<word.length(); i++)
		{
			
			if(word.at(i) >= 48 && word.at(i) <= 57 || word.at(i) >= 65 && word.at(i) <= 90 || word.at(i) >= 97 && word.at(i) <= 122 )
			{
					
			}
			else
			{
				return false;
			}
		}
		return true;	
	}
	
	return false;
}


int SyntaxAnalyzer::getSize()
{
	return count;
}

bool SyntaxAnalyzer::start(string returnType)
{
	if(DataType(returnType) ==  true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int SyntaxAnalyzer::funcDeclaration(string array[])
{
	int flag=0;
	
	//Checking keyword for return type
	if(start(array[0]) == true)
	{
		
		//Next Phase to check Function Name
		if(checkIdentifier( array[1]) == true)
		{
			
			if(array[2] =="(" && openP == 1)
			{
				
				
				for(int i=3; i<count-2; i=i+3)
				{
					if(DataType(array[i]) == true)
					{
						 if(checkIdentifier( array[i+1]) == true)
						{
							if(array[i+2] == "," || i + 2 == count-2)
							{
								flag=1;
							}
							else 
							{
								nameOfError="Error : There is Error on/before/After of , ";
								flag=0;
								break;
							}	
						}
						else 
						{
							nameOfError="Error : There is Error on/before/After of Parameter Variable name ";
							flag=0;
							break;
						}
							
					}
					else 
					{
						nameOfError="Error : There is Error  on/before/After of Parameter Data Type ";
						flag=0;
						break;
					}
					
				}
				
				if( flag == 1 )
				{
					
					if( array[count-2] ==")" && closeP == 1 )
					{
						if( array[count-1] ==";" && semicolon == 1 )
						{
							return 1;
						}
						else
						{
							//Error
							nameOfError="Error : There is Error on/before/After of semicolon ; ";
							return 0;
						}
						
					}
					else
					{
						//Error
						nameOfError="Error : There is Error on/before/After of closing parenthesis ";
						return 0;
					}	
				}
				else
				{
					//Error
					nameOfError="Error : There is Error  before ) closing paranthesis ";
					return 0;
				}	
			}
			else
			{		
			//Error
			nameOfError="Error : There is Error on/before/After of Open Parenthesis ( ";
			return 0;
			}		
		}
		else
		{	
		//Error
			nameOfError="Error : There is Error on/before/After of Function Name ";
			return 0;
		}
			
	}
	else
	{
		//Error
		nameOfError="Error : There is Error on/before/After of Return Type ";
		return 0;
	}
	
 		
}

bool SyntaxAnalyzer::DataType(string returnType)
{
	if(returnType == "numbers" || returnType == "decimals" || returnType == "words")
	{
		return true;
	}
	else
	{
		return false;
	}	
}

string SyntaxAnalyzer::getError()
{
	openP=0;
	closeP=0;
	semicolon=0;
	count=0;
	openB=0;
	closeB=0;
	return nameOfError;
}

void SyntaxAnalyzer::check()
{
	cout<<"OpenP:  "<<openP<<endl;
	cout<<"CloseP:"<<closeP<<endl;
	cout<<"Semicolon: "<<semicolon<<endl;
	cout<<"count: "<<count<<endl;
	
}

int SyntaxAnalyzer::funcCalling(string array[])
{
	int flag=0;
	

		
		//Next Phase to check Function Name
		if(checkIdentifier( array[0]) == true)
		{
			
			if(array[1] =="(" && openP == 1)
			{
				
				
				for(int i=2; i<count-2; i=i+2)
				{
				
					 if(checkIdentifier( array[i]) == true)
					{
						if(array[i+1] == "," || i + 1 == count-2)
						{
							flag=1;
						}
						else 
						{
							nameOfError="Error : There is Error on/before/After of , ";
							flag=0;
							break;
						}	
					}
					else 
					{
						nameOfError="Error : There is Error on/before/After of Parameter Variable name ";
						flag=0;
						break;
					}
							
					
					
				}
				
				if( flag == 1 )
				{
					
					if( array[count-2] ==")" && closeP == 1 )
					{
						if( array[count-1] ==";" && semicolon == 1 )
						{
							return 1;
						}
						else
						{
							//Error
							nameOfError="Error : There is Error on/before/After of semicolon ; ";
							return 0;
						}
						
					}
					else
					{
						//Error
						nameOfError="Error : There is Error on/before/After of closing parenthesis ";
						return 0;
					}	
				}
				else
				{
					//Error
					nameOfError="Error : There is Error  before ) closing paranthesis ";
					return 0;
				}	
			}
			else
			{		
			//Error
			nameOfError="Error : There is Error on/before/After of Open Parenthesis ( ";
			return 0;
			}		
		}
		else
		{	
		//Error
			nameOfError="Error : There is Error on/before/After of Function Name ";
			return 0;
		}
			
	
	
}

int SyntaxAnalyzer::ifConditional(string array[], int pos)
{
	int flag=0;
	count=pos;
	if(array[0]== "if")
	{
		if(array[1]=="(" && openP == 2)
		{
			
			for(int i=2; i<count-1; i=i+4)
			{
				//checking Operand
				if(isOperand(array[i]) == true)
				{
					if(isOperator(array[i+1]) == true)
					{
						if(isOperand(array[i+2]) == true)
						{
							if(array[i+3] == "||" || array[i+3] == "&&" || i+2==count-2)
							{
								flag=1;
							}
							else
							{
								nameOfError="Error : There is Error ON/before/After || or && or )";
								flag=0;
							}
						}
						else
						{
							nameOfError="Error : There is Error ON/before/After Operand ";
							flag=0;
						}
					}
					else
					{
						nameOfError="Error : There is Error ON/before/After Operator ";
						flag=0;	
					}
				}
				else
				{
					nameOfError="Error : There is Error ON/before/After Operand ";
					flag=0;
				}	
			}
			
			if(flag == 1)
			{
				//checking closing paranthesis
				if(array[count-1] == ")" && closeP==2)
				{
					return 1;
				}
				else
				{
					nameOfError="Error : There is Error on/before/After closing paranthesis ) ";
					return 0;
				}	
			}		
			else
			{
				nameOfError="Error : There is Error After opening paranthesis or closing paranthesis ) ";
				return 0;
			}
		}
		else
		{
			nameOfError="Error : There is Error on/before/After opening paranthesis ( ";
			return 0;
		}
	}
	else
	{
		nameOfError="Error : There is Error on/before/After if ";
		return 0;
	}
	
}

bool SyntaxAnalyzer::isOperand(string word)
{
	if(checkIdentifier(word) == true)
	{
		return true;
	}
	else
	{
		for(int i=0; i<word.length(); i++)
		{
			if( !(word.at(i) >=48 && word.at(i) <=57 ) )
			{
				return false;
			}
		}	
	}
	
	return true;
}

bool SyntaxAnalyzer::isOperator(string word)
{
	if(word == ">" || word == "<" || word == ">=" || word == "<=" || word == "==" || word == "!=" )
	{
		return true;
	}	
}

int SyntaxAnalyzer::switchCaseCalling(string array[])
{
	if(array[0] == "check")
	{
		if(array[1] == "(")
		{
			if(checkIdentifier(array[2]) == true)
			{
				if(array[3] == ")")
				{
					return 1;
				}
				else
				{
					nameOfError="Error : There is Error ON/before/After closing Paranthesis )";
					return 0;
				}
			}
			else
			{
				nameOfError="Error : There is Error ON/before/After parameter name )";
				return 0;
			}
		}
		else
		{
			nameOfError="Error : There is Error ON/before/After opening Paranthesis (";
			return 0;
		}
	}
	else
	{
		nameOfError="Error : There is Error ON/before/After Keyword";
		return 0;
	}
}

int SyntaxAnalyzer::whileLoopCalling(string array[], int pos)
{
	int flag=0;
	count=pos;
	if(array[0]== "repeatTill")
	{
		if(array[1]=="(" && openP == 2)
		{
			
			for(int i=2; i<count-1; i=i+4)
			{
				//checking Operand
				if(isOperand(array[i]) == true)
				{
					if(isOperator(array[i+1]) == true)
					{
						if(isOperand(array[i+2]) == true)
						{
							if(array[i+3] == "||" || array[i+3] == "&&" || i+2==count-2)
							{
								flag=1;
							}
							else
							{
								nameOfError="Error : There is Error ON/before/After || or && ";
								flag=0;
							}
						}
						else
						{
							nameOfError="Error : There is Error ON/before/After Operand ";
							flag=0;
						}
					}
					else
					{
						nameOfError="Error : There is Error ON/before/After Operator ";
						flag=0;	
					}
				}
				else
				{
					nameOfError="Error : There is Error ON/before/After Operand ";
					flag=0;
				}	
			}
			
			if(flag == 1)
			{
				//checking closing paranthesis
				if(array[count-1] == ")" && closeP==2)
				{
					return 1;
				}
				else
				{
					nameOfError="Error : There is Error on/before/After closing paranthesis ) ";
					return 0;
				}	
			}		
			else
			{
				//nameOfError="Error : There is Error After opening paranthesis or closing paranthesis ) ";
				return 0;
			}
		}
		else
		{
			nameOfError="Error : There is Error on/before/After opening paranthesis ( ";
			return 0;
		}
	}
	else
	{
		nameOfError="Error : There is Error on/before/After if ";
		return 0;
	}
}

int SyntaxAnalyzer::whileLoopDefinition(string array[])
{
	
if(array[0] == "{")
{
		
	if(array[1] == "show")
	{
		if(array[2] == "(" && openP==2)
		{
			if(checkString(array[3]) == true)
			{
				if(array[4] == ")" && closeP==2)
				{
					if(array[5] ==";" && semicolon == 1)
					{
						if(array[6] =="}" && closeB == 1)
						{
							return 1;
						}
						else
						{
							nameOfError="Error : There is Error on/before/After } ";
							return 0;							
						}
					}
					else
					{
						nameOfError="Error : There is Error on/before/After ; ";
						return 0;
					}
				}
				else
				{
					nameOfError="Error : There is Error on/before/After closing Paranthesis ) ";
					
					return 0;
				}
			}
			else
			{
				nameOfError="Error : There is Error between  strings  ";
				return 0;
			}
		}
		else
		{
			nameOfError="Error : There is Error on/before/After opening Paranthesis ( ";
			return 0;
		}
	}
	else
	{
		nameOfError="Error : There is Error on/before/After  show functionName ";
		return 0;
	}
}
else
{
	nameOfError="Error : There is Error on/before/After  Opening Braces { ";
	return 0;

}

}

bool SyntaxAnalyzer::checkString(string word)
{
	for(int i =0; i<word.length(); i++)
	{
		if( !(word.at(i)>=65 && word.at(i)<=90) &&  !(word.at(i)>=97 && word.at(i)<=122) &&  !(word.at(i)>=48 && word.at(i)<=57) && word.at(i)!=34 && word.at(i) != 92 && word.at(i)!= 44 && word.at(i)!= 32  ) 
		{
			return  false;
		}
	}
	return true;
	
}

string SyntaxAnalyzer::getStringToken()
{
	return tokenString;
}

void SyntaxAnalyzer::setCountZero()
{
	count=0;
}
int SyntaxAnalyzer::getValue()
{
	return openP;
}
