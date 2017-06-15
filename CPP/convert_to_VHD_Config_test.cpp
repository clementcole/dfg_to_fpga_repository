#include "convert_to_VHD_Config.cpp"
#include "XML_parser.h"
#include "element.h"
#include <thread>



void foo() 
{
	cout << "Hello World\n";
}
void bar()
{
	cout << "Bar running\n";
}
void fbar()
{
	cout << "fbar running\n";
}

int main(){
	//unordered_map <string, string> m;
	//m["hello"] = "hello";
	//cout << m["hello"] << endl;
	//element_ALU myALU;
	//element_DLY myDLY;
	//element_LDST myLDST;
/*
	int a;
	unsigned t0 = clock();
	//vector<element_ALU> ALUS;
	//ALUS.push_back(element_ALU());
	//ALUS[0].element_name = "GREEN";
	//cout << ALUS[0].element_name << endl;
	string xml_file = "histogram_pim.xml";
	string test = "C:/Modeltech_pe_edu_10.4a/ALU/Instruction.config";
	//cout<<"Enter the XML file's name: ";
	//cin >> xml_file;
	//cout<<"Enter the CONFIG file's name: ";
	//cin >> xml_file;
	XML_Parser Charles_XML_Parser;
	Charles_XML_Parser.__main__(xml_file, test);
	//Charles_XML_Parser.TEST_INSTRUCTION_LINE();
	Charles_XML_Parser.PROCESS_COMPONENT_MATRIX();

	std::thread first (foo);
	std::thread second (bar);
	std::thread third(fbar);
	first.join();
	second.join();
	third.join();
	std::cout <<(clock() - t0)<< "\n";
	//auto func = [] () {cout << "Hello World\n";};
	//func();
*/

	for (char idx=0; idx < 250; idx++) cout << "Hello World" << endl;
	return 0;
}
