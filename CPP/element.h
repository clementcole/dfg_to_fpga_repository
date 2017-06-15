#ifndef ELEMENT_H
#define ELEMENT_H
#include "Convert_to_VHD_Config.h"
#include <map>

template<class T>
class GRAPH_NODE {

private:

    T* data;
    GRAPH_NODE<T>* parent;
    vector< GRAPH_NODE<T>* > children;

public:

    GRAPH_NODE(GRAPH_NODE<T>* parent, T data);
    ~GRAPH_NODE();

    T& getData() const;
    void setData(const T& data);
    void addChild(const T& data);
    void removeChild(const size_t& indx);
    GRAPH_NODE<T>* findChild(const T& data) const;
    GRAPH_NODE<T>* getChild(const size_t& indx) const;
    GRAPH_NODE<T>* getParent() const;
    int getNumChildren() const;

};


template <class var>
class Element
{
public:
	var elementType;
	var instance;
	vector<var> OtherTypes;
	vector<Element> Connections;
};
/*
template <>
class Element <string>{
	T element;
public:
	ELEMENT (T arg) 
	{
		element = arg;
	}
	T increase
};

unordered_map <string, string> m;
    m["hello"] = "hello";
    cout << m["hello"] << endl;*/
struct element_ALU{
    string element_name; 
    string alu_instance;
    string data_port_A;
    string data_port_B;
    string data_port_out;
    string data_port_opcode;
};

struct element_IALU{
    string element_name;
    string alu_instance;
    string data_port_A;
    string data_port_IMM;
    string data_port_out;
    string data_port_opcode;
};

struct element_DLY{
    string element_name;
    string dly_instance;
    string data_port_in;
};

struct element_LDST{
    string element_name;
    string ldst_instance;
    string data_size;
};

struct element_MEM{
    string element_name;
    string mem_instance;
    string rd_adrs;
    string rd_enable_port;
    string latency;
    string wr_adrs_port;
    string wr_data_port;
};
enum  PASS_CODE
{
    passed=0,
    passed_parsing_ALU_OBJ=1, 
                            passed_parsing_ALU_instanceKEY, 
                            passed_parsing_ALU_inA_KEY,     passed_parse_inA_VAL,  
                            passed_parsing_ALU_inB_KEY,     passed_parsing_ALU_inB_VAL, 
                            passed_parsing_ALU_out_KEY,     passed_parsing_ALU_out_VAL,
                            passed_parsing_ALU_func_KEY,    passed_parsing_ALU_func_VAL,
    passed_parsing_IALU_OBJ, passed_parsing_IALU_instanceKEY, passed_parsing_IALU_inA_KEY, passed_parsing_IALU_IMM_KEY, passed_parsing_IALU_func_CODE,
    passed_parsing_MEM_OBJ,
    passed_parsing_DLY_OBJ,
    passed_parsing_LDST_OBJ, passed_parsing_LDST_STORE_KEY,

};
map<int, string> SCREAM_SUCCESS = 
{
    {passed, "SUCCESS! CODE[0] : ELEMENT PARSED SUCESSESFULLY\n"},
    {passed_parsing_ALU_OBJ, "SUCCESS! CODE[0] : ALU OBJ PARSE SUCCESS\n"},
    {passed_parsing_ALU_instanceKEY, "SUCCESS! CODE[1] :  PARSED ALU INSTANCE KEY SUCCESSFULLY\n"},
    {passed_parsing_ALU_inA_KEY, "SUCCESS! CODE[2] :  PARSED ALU IN_0 KEY SUCCESSFULLY\n"},
    {passed_parse_inA_VAL, "SUCCESS! CODE[3] :  PARSED ALU IN_0 VALUE SUCCESSFULLY\n"},
    {passed_parsing_ALU_inB_KEY, "SUCCESS! CODE[4] :  PARSED ALU IN_1 KEY SUCCESSFULLY\n"},
    {passed_parsing_ALU_inB_VAL, "SUCCESS! CODE[5] :  PARSED ALU IN_1 VALUE SUCCESSFULLY\n"},
    {passed_parsing_LDST_STORE_KEY, "SUCCESS! CODE[6] LDST UNIT SIZE KEY PARSED SUCCESSFULLY\n"}
};
enum ERROR_CODE
{
    invalid_component,
    invalid_size_ALU,
    invalid_size_IALU,
    invalid_size_LDST,
    invalid_size_DELAY,
    invalid_size_MEMORY,

    //invalid_in_A_IALU,
    invalid_in_B_IALU,
    invalid_in_IMM_ALU,
    invalid_out_ALU,
    invalid_in_A_MEM,
    invalid_in_B_MEM,
    invalid_input_MEM,
    invalid_input_DLY,
    invalid_input_LDST,

    SUCCESS,

};
map<int, string> SCREAM_PANIC =
{
    {0, "PANIC! ERROR CODE[1] : ALU COMPONENT WITH LOAD STORE UNIT SIZE ERROR!\n"},
    {1, "PANIC! ERROR CODE[1] : ALU COMPONENT WITH LOAD STORE UNIT SIZE ERROR!\n"},
    {2, "PANIC! ERROR CODE[2] : IMMEDIATE ALU COMPONENT WITH LOAD STORE UNIT SIZE ERROR\n"},
    {3, "PANIC! ERROR CODE[3] : MEMORY UNIT WITH LOAD STORE UNIT SIZE ERROR\n"},
    {4, "PANIC! ERROR CODE[4] : DELAY ELEMENT COMPONENT WITH LOAD STORE UNIT SIZE ERROR\n"},
    {5, "PANIC! ERROR CODE[5] : DELAY ELEMENT COMPONENT WITH LOAD STORE UNIT SIZE ERROR\n"}
};

map<string, string> FUNCTION_CODES =
{
    {"clear",   "11111110\n"},        
    {"idle",    "11111110\n"},         
    {"add",     "00000000\n"},           
    {"sub",     "00000000\n"},           
    {"mult",    "00000001\n"},         
    {"div",     "00000010\n"},          
    {"or",      "00000011\n"},        
    {"nor",     "00000100\n"},     
    {"xor",     "00000101\n"},           
    {"xnor",    "00000110\n"},          
    {"and",     "00000111\n"},          
    {"not",     "00001000\n"},         
    {"sla",     "00001001\n"},           
    {"sra",     "00001010\n"},           
    {"sll",     "00001011\n"},           
    {"srl",     "00001100\n"},         
    {"ror",     "00001101\n"},           
    {"rol",     "00001110\n"},           
    {"fadd",    "00001111\n"},          
    {"fsub",    "00010000\n"}, 
    {"fmult",   "00010001\n"},         
    {"fdiv",    "00010010\n"}
};
//#define MAX(x, y) (x) < (y) ? (y) : (x)
/*
auto SCREAM_PARSER(auto code) 
void DecoratorClass::ADD(vector<string>& Instr){
    string blockNum = Instr[0];
    string lineNum = Instr[1];
    string Abs = Instr[2];
    string Rel = Instr[3];
    string Mac = Instr[4];
    string nodeLabel = Instr[5];
    string destLabel1 = Instr[6];
    string srcLabel1 = Instr[7];
    string srcLabel2 = Instr[8];
    string node = Instr[5] + "_" + Instr[0] + "_" + Instr[1];
    string dest = Instr[6] + "_" + Instr[0] + "_" + Instr[1];
    string src1 = Instr[7] + "_" + Instr[0] + "_" + Instr[1];
    string src2 = Instr[8]+ "_" + Instr[0] + "_" + Instr[1];
    graphCol.push_back(blockNum);
    graphCol.push_back(lineNum);
    graphCol.push_back(Abs);
    graphCol.push_back(Rel);
    graphCol.push_back(Mac);
    graphCol.push_back(nodeLabel);
    graphCol.push_back(destLabel1);
    graphCol.push_back(srcLabel1);
    graphCol.push_back(srcLabel2);
    graphCol.push_back(node);
    graphCol.push_back(dest);
    graphCol.push_back(src1);
    graphCol.push_back(src2);
    graphCol.push_back("0");
    graphCol.push_back("0");
    graphCol.push_back("0");
    graphRow.push_back(graphCol);
    graphCol.clear();
 audio 
} 
    -> ERROR_CODE
{
    auto msg = KNOWN_ERRORS.find(code);
    //if(msg == KNOWN_ERRORS.end() ){return ERROR_CODE::SUCCESS;}
    //else 
       cout<< msg->second;
};*/
/*
struct PANIC_ROOM
{
    int PANIC_INDEX;
    map<int, string> m;
    m[0] = ("PANIC! ERROR CODE[0] : UNABLE TO FIND COMPONENT FOR WHICH INSTANCE BELONGS TO\n");
    m[1] = "PANIC! ERROR CODE[1] : ALU COMPONENT WITH LOAD STORE UNIT SIZE ERROR!\n";
    m[2] = "PANIC! ERROR CODE[2] : IMMEDIATE ALU COMPONENT WITH LOAD STORE UNIT SIZE ERROR\n";
    m[3] = "PANIC! ERROR CODE[3] : MEMORY UNIT WITH LOAD STORE UNIT SIZE ERROR\n";
    m[4] = "PANIC! ERROR CODE[4] : DELAY ELEMENT COMPONENT WITH LOAD STORE UNIT SIZE ERROR\n";
    m[5] = "PANIC! ERROR CODE[5] : DELAY ELEMENT COMPONENT WITH LOAD STORE UNIT SIZE ERROR\n";
    //void(*SCREAM) (const struct PANIC_ROOM*);
};*/
/*
void  SCREAM_0(const struct PANIC_ROOM*) {printf("PANIC[0]: %s", PANIC_ROOM -> PANIC[0]);}
void  SCREAM_1(const struct PANIC_ROOM*) {printf("PANIC[0]: %s", PANIC_ROOM -> PANIC[1]);}
*/
/*

        bool ALU_SUB_FLAG_PROCESSING_PORT_A = false;
        bool ALU_SUB_FLAG_PROCESSING_PORT_B = false;
        bool ALU_SUB_FLAG_PROCESSING_PORT_OUT = false;
        bool ALU_SUB_FLAG_PROCESSING_PORT_OPCODE = false;

/*

        bool PROCESSING_IALU_COMPONENTS = false;
        bool IALU_SUB_FLAG_PROCESSING_INSTANCE =false;
        bool IALU_SUB_FLAG_PROCESSING_PORT_A = false;
        bool IALU_SUB_FLAG_PROCESSING_PORT_B = false;
        bool IALU_SUB_FLAG_PROCESSING_PORT_OUT = false;
        bool IALU_SUB_FLAG_PROCESSING_PORT_OPCODE = false;
      


        bool PROCESSING_MEM_COMPONENTS = false;
        bool MEM_SUB_FLAG_PROCESSING_MEM_INSTANCE = false;
        bool MEM_SUB_FLAG_PROCESSING_RD_ADRS = false;
        bool MEM_SUB_FLAG_PROCESSING_RD_EN_PORT = false;
        bool MEM_SUB_FLAG_PROCESSING_LATENCY = false;
        bool MEM_SUB_FLAG_PROCESSING_WR_ADRS_PORT = false;
        bool MEM_SUB_FLAG_PROCESSING_WR_DATA_PORT = false;

      
        bool PROCESSING_LDST_COMPONENTS = false;
        bool LDST_SUB_FLAG_PROCESSING_LDST_SIZE = false;
        bool LDST_SUB_FLAG_PROCESSING_LDST_INSTANCE = false;

        bool DLY_SUB_FLAG_PROCESSING_DLY_COMPONENTS = false;
        bool DLY_SUB_FLAG_PROCESSING_DLY_INSTANCE = false;
        bool DLY_SUB_FLAG_PROCESSING_DATA_PORT_IN = false;
*/
/*
PODCASTS
Coding Blocks Podcast
http://www.makeuseof.com/tag/15-top-notch-podcasts-programmers-software-developers/
http://www.fullstackradio.com/50
https://community.c9.io/t/writing-a-c-app/4965
http://stackoverflow.com/questions/5567529/what-makes-a-static-variable-initialize-only-once
http://stackoverflow.com/questions/5373714/generate-calling-graph-for-c-code/5373814#5373814
http://tdm-gcc.tdragon.net/download
Portable linux
http://www.porteus.org/
*/
#endif