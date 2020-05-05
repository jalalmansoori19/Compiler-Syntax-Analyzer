#include <iostream>
#include <fstream>
#include "syntax.cpp"
#include <string>
using namespace std;

int main()
{
	
	//Reading Source Code from file
	ifstream MYFILE("sourceCode.txt");
	string s_Code=""; 
	
	//below function used for reading file content and storing it in string variable s_Code
	s_Code.assign( istreambuf_iterator<char>(MYFILE) , istreambuf_iterator<char>());
	
	
	SyntaxAnalyzer object;
	
	cout<<"Source Code \n\n";
	
	
	object.setSourceCode(s_Code);
	
	object.display();
    
	object.separateWords();
	
	
	//Now Token Are Generated an stored on txt file
	
	ifstream FILE("generatedTokens.txt");
	string a="";
	int i=0;
	string tokenArray[object.getSize()];
	string temp="";
	
	while(FILE>>a)
	{
		if(a.at(0) == 34)
		{
			tokenArray[i]=object.getStringToken();
			while(FILE>>a)
			{
				if(a.at(a.length()-1) == 34)
				{
					break;
				}
			}
		}
		else
		{
			tokenArray[i]=a;	
		}
		
		i++;
	}
	
	int pos=0;
	int size=0;
	int pos2=0; 
	
	for(int i=0; i<object.getSize(); i++)
	{
		if(tokenArray[i] == ")")
		{
			pos=i;
			break;
		}
	}
	
	for(int i=0; i<object.getSize(); i++)
	{
		if(tokenArray[i] == "{")
		{
			pos2=i;
			break;
		}	
	}
	
	size=object.getSize() - pos2;
	
	string tokenArray2[size];

	for(int i=0; i<size; i++)
	{
		tokenArray2[i]=tokenArray[i+pos2];
	}
	

	//Below Code is For CONDITIONAL STATEMENTS
	if(  object.ifConditional(tokenArray, pos+1)== 1)
	{
		
		if(object.whileLoopDefinition(tokenArray2) == 1)
		{
			cout<<"Syntactically Correct !";	
		}
			
		else
		{
			char key='0';
		
			cout<<"Your Source Code is Syntactically InCorrect !"<<endl;
			
			cout<<object.getError()<<endl;
			
			
			cout<<"\n If you have resolve error Press c to check : ";
			cin>>key;
			
			switch(key)
			{
				case 'c':
					main();
				break;
			}
		}
		
	}
	else
	{
		char key='0';
		
		cout<<"Your Source Code is Syntactically InCorrect !"<<endl;
		
		cout<<object.getError()<<endl;
		
		
		cout<<"\n If you have resolve error Press c to check : ";
		cin>>key;
		
		switch(key)
		{
			case 'c':
				main();
			break;
		}		
	}
	
	
	//Below Code is for Function CAllING
	/*if(object.funcCalling(tokenArray) == 1)
		{
			cout<<"Syntactically Correct !";	
		}
			
		else
		{
			char key='0';
		
			cout<<"Your Source Code is Syntactically InCorrect !"<<endl;
			
			cout<<object.getError()<<endl;
			
			
			cout<<"\n If you have resolve error Press c to check : ";
			cin>>key;
			
			switch(key)
			{
				case 'c':
					main();
				break;
			}
		}
		*/
		
	// Below Code is Function DECLARATION	
/*	if(object.funcDeclaration(tokenArray) == 1)
		{
			cout<<"Syntactically Correct !";	
		}
			
		else
		{
			char key='0';
		
			cout<<"Your Source Code is Syntactically InCorrect !"<<endl;
			
			cout<<object.getError()<<endl;
			
			
			cout<<"\n If you have resolve error Press c to check : ";
			cin>>key;
			
			switch(key)
			{
				case 'c':
					main();
				break;
			}
		}
	*/
	
	
	//Below Code is For WHILE LOOP
	/*if(  object.whileLoopCalling(tokenArray, pos+1)== 1)
	{
		
		if(object.whileLoopDefinition(tokenArray2) == 1)
		{
			cout<<"Syntactically Correct !";	
		}
			
		else
		{
			char key='0';
		
			cout<<"Your Source Code is Syntactically InCorrect !"<<endl;
			
			cout<<object.getError()<<endl;
			
			
			cout<<"\n If you have resolve error Press c to check : ";
			cin>>key;
			
			switch(key)
			{
				case 'c':
					main();
				break;
			}
		}
		
	}
	else
	{
		char key='0';
		
		cout<<"Your Source Code is Syntactically InCorrect !"<<endl;
		
		cout<<object.getError()<<endl;
		
		
		cout<<"\n If you have resolve error Press c to check : ";
		cin>>key;
		
		switch(key)
		{
			case 'c':
				main();
			break;
		}		
	}
	
	*/
	return 0;
}


