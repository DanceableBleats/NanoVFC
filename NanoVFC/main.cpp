// ConsoleApplication1.cpp : Defines the entry point for the console application.

//#include <vector>
//#include <iostream>
//#include <string>
//#include <stdio.h>
//#include <tchar.h>


#include "includes.h"

int main(int argc, char *argv[])
{
	//std::string newfilename = "outFile.txt";
	mstrClass *p_mstrClass = new mstrClass();

	std::string filename1;
	std::string filename2;

	int mode = 0;
	if (argc > 1)
	{
		if (std::string(argv[1]) == "/D")
		{
			//std::cout << "delete mode?" << std::endl;
			mode = DELETE;
			filename1.append(argv[2]);
		}
		else if (std::string(argv[1]) == "/M")
		{
			mode = MERGE;
			filename1.append(argv[2]);
			filename2.append(argv[3]);
		}
		else 
		{
			std::cout << "Incorrect arguments. '/D <filename>' for RXA-21 Delete Operation, '/M <outgoingfilename> <responsefilename>' to merge." << std::endl;
			//system("pause");
		}
	}
	else
	{
		std::cout << "Incorrect arguments. '/D <filename>' for RXA-21 Delete Operation, '/M <outgoingfilename> <responsefilename>' to merge." << std::endl;
		//system("pause");
	}
	
		

	if (mode == DELETE)
	{
		std::cout << "DELETE MODE." << std::endl << "====================" << std::endl << std::endl;
		std::string *p_delFileName = new std::string("deleted.txt");
		std::string *p_keepFileName = new std::string("output.txt");
		int h1 = p_mstrClass->newHLFile(&filename1);
		int h2 = p_mstrClass->newHLFile(p_keepFileName);
		int h3 = p_mstrClass->newHLFile(p_delFileName);
		p_mstrClass->openFileStream(h1, IN);
		p_mstrClass->openFileStream(h2, OUT);
		p_mstrClass->openFileStream(h3, OUT);
		p_mstrClass->parseFile(h1);
		p_mstrClass->removeRXA21Deletes(h1, h2, h3);
		p_mstrClass->writeFile(h2);
		p_mstrClass->writeFile(h3);

		system("pause");	
		return 1;
	}
	else if (mode == MERGE)
	{
		std::cout << "MERGE MODE." << std::endl << "====================" << std::endl << std::endl;
		//std::string *p_outputFileName = new std::string("merged.txt");
		int h1 = p_mstrClass->newHLFile(&filename1);
		int h2 = p_mstrClass->newHLFile(&filename2);
		p_mstrClass->openFileStream(h1, IN);
		p_mstrClass->openFileStream(h2, IN);
		p_mstrClass->parseFile(h1);
		p_mstrClass->parseFile(h2);
		int newHandle = p_mstrClass->mergeFiles(h2, h1);
		p_mstrClass->openFileStream(newHandle, OUT);
		p_mstrClass->writeFile(newHandle);

		system("pause");
		return 1;
	}


	return 0;
}

