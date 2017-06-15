#ifndef XML_PARSER_H
#define XML_PARSER_H
#include "XML_parser_helper.h"
#include "element.h"
#include "ALU_ENUMS.h"

class XML_Parser
{
private:

		bool OPEN_CONFIG_TAG_FLAG = false;
		bool CLOSE_CONFIG_TAG_FLAG = false;
		bool READ_ALU_CONFIG_FLAG = false;
		bool READ_ELEMENT_INST_FLAG = false;
		bool READ_ELEMENT_TYPE_FLAG = false;
		bool READ_DLY_CONFIG_FLAG = false;
		bool READ_LDST_CONFIG_FLAG = false;
		bool READING_KEY_FLAG = false;
		bool READING_VALUE_FLAG = false;
		bool READING_STATEMENT_DONE = false;
		bool EQUAL_FLAG = false;
		bool INSTANCE_FLAG = false;
		bool INPUT_FLAG_0 = false;

		/*
			COMPONENTS AND SUB COMPONENTS FLAGS*****************************************************************
		*/
		/******************IALU COMPONENTS FLAGS ****************************/
		bool COMMENT_PROCESSING_TAGS = false;
		bool OPEN_COMMENT_TAG_FLAG = false;
		bool CLOSE_COMMENT_TAG_FLAG = false;

		/******************IALU COMPONENTS FLAGS ****************************/
		bool PROCESSING_ALU_COMPONENTS = false;
		bool ALU_SUB_FLAG_PROCESSING_INSTANCE =false;
		bool ALU_SUB_FLAG_PROCESSING_PORT_A = false;
		bool ALU_SUB_FLAG_PROCESSING_PORT_B = false;
		bool ALU_SUB_FLAG_PROCESSING_PORT_OUT = false;
		bool ALU_SUB_FLAG_PROCESSING_PORT_OPCODE = false;


		/******************ALU COMPONENTS FLAGS ****************************/
		bool PROCESSING_IALU_COMPONENTS = false;
		bool IALU_SUB_FLAG_PROCESSING_INSTANCE =false;
		bool IALU_SUB_FLAG_PROCESSING_PORT_A = false;
		bool IALU_SUB_FLAG_PROCESSING_PORT_IMM = false;
		bool IALU_SUB_FLAG_PROCESSING_PORT_OUT = false;
		bool IALU_SUB_FLAG_PROCESSING_PORT_OPCODE = false;


		/******************MEM COMPONENTS FLAGS ****************************/
		bool PROCESSING_MEM_COMPONENTS = false;
		bool MEM_SUB_FLAG_PROCESSING_INSTANCE = false;
		bool MEM_SUB_FLAG_PROCESSING_RD_ADRS = false;
		bool MEM_SUB_FLAG_PROCESSING_RD_EN_PORT = false;
		bool MEM_SUB_FLAG_PROCESSING_LATENCY = false;
		bool MEM_SUB_FLAG_PROCESSING_WR_ADRS_PORT = false;
		bool MEM_SUB_FLAG_PROCESSING_WR_DATA_PORT = false;

		/******************LOAD STORE COMPONENTS FLAGS ****************************/
		bool PROCESSING_LDST_COMPONENTS = false;
		bool LDST_SUB_FLAG_PROCESSING_SIZE = false;
		bool LDST_SUB_FLAG_PROCESSING_INSTANCE = false;

		/******************DELAY COMPONENTS FLAGS ****************************/
		bool PROCESSING_DLY_COMPONENTS = false;
		bool DLY_SUB_FLAG_PROCESSING_DLY_INSTANCE = false;
		bool DLY_SUB_FLAG_PROCESSING_DATA_PORT_IN = false;
		/*
			END OF  COMPONENTS AND SUB COMPONENTS FLAGS*****************************************************************
		*/
		string _space_ = " ";
		string _colons_ = " : ";
		string _semiColons_ = " ; ";
		string _quotes_	= "\"";
		string _square_brack_open_ = "[";
		string _square_brack_close_ = "]";
		string _tab_ = "\t";
		string data = ".data";

		int alu_ref_counter = 0;
		int ialu_ref_counter = 0;
		int mem_ref_counter = 0;
		int dly_ref_counter = 0;
		int ldst_ref_counter = 0;

		vector<string> InstrVec;
		vector<element_ALU> ALUS;
		vector<element_IALU> IALUS;
		vector<element_DLY> DLYS;
		vector<element_LDST> LDSTS;
		vector<element_MEM> MEMS;
		TokenHelper thisHelper;



		/*
			GRAPH UTILITIES
		*/
		vector< std::string > FPGA_COMPONENTS_PORTS;
		vector<	vector<std::string> > FPGA_COMPONENTS;
		
		vector<	std::string > ALU_CONFIG_Cnode;
		vector< vector<std::string> > ALU_CONFIG_Rnode; 
		/*
			Notes on ALU_COL_node
			ALU_CONFIG_Rnode[X][0] = IN_RDY_SIG[X]
			ALU_CONFIG_Rnode[X][1] = ALU_OP[X]

			ALU_CONFIG_Rnode[X][2] = select_linesB[X]
			ALU_CONFIG_Rnode[X][3] = select_linesA[X]

			ALU_CONFIG_Rnode[X][4] = input_A_SOURCE[X]
			ALU_CONFIG_Rnode[X][5] = input_B_SOURCE[X]
		*/

		//vector< std::string > ALU_COL_MUX;
		//vector< vector<std::string> > ALU_ROW_MUX;

		//vector<std::string> IN_RDY_SIG;
		//vector<std::string> OUT_RDY_SIG;

public:
		//inline void 	SCREAM(int error_code);
		inline void     GET_ELEMENT_TYPE(const std::string s);
		inline void 	SET_FLAGS(int lexem_type);
		inline void     RESET_COMMENT_FLAGS(const std::string s);
		inline void 	PROCESS_ELEMENT_COMPONENTS_VALUE(const string str);
		inline void     PROCESS_ELEMENT_COMPONENTS(string str);
		inline void		TEST_INSTRUCTION_LINE();
		inline void 	PROCESS_COMPONENT_MATRIX();
		inline void		CONVERT_COMPONENT_TO_ALU();

		inline void     RESET_CONFIG_FLAGS(const std::string s);
		inline void 	SET_OPEN_TAGS_FLAGS(string thisWord);
		inline void 	SET_CLOSE_TAGS_FLAGS(string thisTag);
		inline void     SET_READING_KEY_FLAG(string thisWord);
		inline void     SET_READING_VALUE_FLAG(string thisWord);
		inline void 	Is_Open_Statement(string thisTag);
		inline void     Is_Close_Statement(string thisTag);
		inline void 	Is_MEM_STATEMENT(string thisWord);
		inline void 	Is_ALU_STATEMENT(string word);
		inline void     Insert_Value_ALU(string word);
		inline void     Insert_Key_ALU(string word);



		inline void		__main__(const string& inputFile, const string& outputFile);
		inline void     __return_lexem__(const string str);
};



inline void XML_Parser::GET_ELEMENT_TYPE(const std::string s)//Called to get the element type
{
	;;
}
inline void XML_Parser::PROCESS_COMPONENT_MATRIX()
{
	string ALU_ID;
	string select_lines_A;
	string select_lines_B;
	string OPCODE;
	string INPUT_READY_SOURCE;
	string RESULT_READY_SOURCE;
	//string 
	for (int i =0; i < FPGA_COMPONENTS.size(); i++) //Previous component
	{
		for(int j = i + 1; j < FPGA_COMPONENTS[i].size(); j++) //Next Component
		{
			if(thisHelper.GetReserve(FPGA_COMPONENTS[i][0]) == LOAD_STORE_TYPE_) 
			{
				if( FPGA_COMPONENTS[i][0] == FPGA_COMPONENTS[j][4] )  //.data
				{

				}		
			}
			else if ( thisHelper.GetReserve(FPGA_COMPONENTS[i][0]) ==  DELAY_TYPE_)
			{
				//ALU_CONFIG_Cnode.push_back(FPGA_COMPONENTS[i][2]);  
				
			}
			else if ( thisHelper.GetReserve(FPGA_COMPONENTS[i][0]) ==  MEMORY_TYPE_)
			{
				//ALU_CONFIG_Cnode.push_back(FPGA_COMPONENTS[i][2]);
			}
			else if ( thisHelper.GetReserve(FPGA_COMPONENTS[i][0]) == IALU_TYPE_)
			{
				//ALU_CONFIG_Cnode.push_back(FPGA_COMPONENTS[i][2]);
			}
		}
	}
	/*

	#include <string>
	#include <iostream>

	using namespace std;

	template<typename T>
	void removeSubstrs(basic_string<T>& s,
                   const basic_string<T>& p) {
   	basic_string<T>::size_type n = p.length();

   	for (basic_string<T>::size_type i = s.find(p);
        i != basic_string<T>::npos;
        i = s.find(p))
      s.erase(i, n);
	}

	int main() {
   		string s = "One fish, two fish, red fish, blue fish";
   		string p = "fish";

   		removeSubstrs(s, p);

   		cout << s << '\n';
	}
		if( thisHelper.GetReserve(FPGA_COMPONENTS[i][0]) == LOAD_STORE_TYPE_)
		{
			for(int j = i+1; j < FPGA_COMPONENTS[i].size(); j++)
			{
				if( thisHelper.GetReserve(FPGA_COMPONENTS[j][0]) == IALU_TYPE_)
				{
					if( FPGA_COMPONENTS[j][2].find(FPGA_COMPONENTS[i][3])  !=  (string::npos))
					{
						;;
					}
					else if( FPGA_COMPONENTS[j][4].find(FPGA_COMPONENTS[i][3])  !=  (string::npos))
					{
						;
					}
					else if( FPGA_COMPONENTS[j][4].find(FPGA_COMPONENTS[i][3])  !=  (string::npos))
					{
						;
					}
				}
			}
		}
	*/
		/*
		else if ( thisHelper.GetReserve(FPGA_COMPONENTS[i][0]) ==  IALU_TYPE_)
		{
			for(int j= i + 1; j < FPGA_COMPONENTS.size(); j++)
			{
				printf("HELLO HELLO\n");
			}

		}
		if ( thisHelper.GetReserve(FPGA_COMPONENTS[i][0]) ==  DELAY_TYPE_)
		{
			cout << "WE GOT A DELAY UNIT YO!!\n";
			break;
		}
		if ( thisHelper.GetReserve(FPGA_COMPONENTS[i][0]) ==  MEMORY_TYPE_)
		{
			cout << "WE GOT A MEMORY UNIT YO!!\n";
			break;
		}
		*/


	
}//END OF FUNCTION PROCESS_COMPONENT_MATRIX()

inline void XML_Parser::SET_FLAGS(int lexem_type) //Called when whitespace encountered
{
	switch(lexem_type)
	{

		//case
		case INSTANCE:
			if(PROCESSING_ALU_COMPONENTS == true)
			{
				ALU_SUB_FLAG_PROCESSING_INSTANCE = true;
				cout <<" : line 135 : " <<SCREAM_SUCCESS[passed];
			}
			else if(PROCESSING_IALU_COMPONENTS == true)
			{
				IALU_SUB_FLAG_PROCESSING_INSTANCE = true;
				cout << " line 140 : "<<SCREAM_SUCCESS[passed];
			}
			else if(PROCESSING_MEM_COMPONENTS == true)
			{
				MEM_SUB_FLAG_PROCESSING_INSTANCE = true;
				cout<<"line 145  : " << SCREAM_SUCCESS[passed];
			}
			else if(PROCESSING_ALU_COMPONENTS == true)
			{
				ALU_SUB_FLAG_PROCESSING_INSTANCE = true;
				cout<<"line 150  : " << SCREAM_SUCCESS[passed];
			}
			else if(PROCESSING_LDST_COMPONENTS == true)
			{
				LDST_SUB_FLAG_PROCESSING_INSTANCE = true;
				cout<<"line 155  : " << SCREAM_SUCCESS[passed];
			}
			else if(PROCESSING_DLY_COMPONENTS == true)
			{
				DLY_SUB_FLAG_PROCESSING_DLY_INSTANCE = true;
				cout<<"line 160 : " << SCREAM_SUCCESS[passed];
			}

			break;

		case SIZE:
			if(PROCESSING_ALU_COMPONENTS == true) 		cout <<"line 166 : "<<SCREAM_PANIC[0];//SCREAM_PANIC[0];
			else if(PROCESSING_IALU_COMPONENTS == true) cout <<"line 167 : "<<SCREAM_PANIC[0];
			else if(PROCESSING_MEM_COMPONENTS == true)	cout <<"line 168 : "<<SCREAM_PANIC[0];
			else if(PROCESSING_ALU_COMPONENTS == true)	cout <<"line 169 : "<<SCREAM_PANIC[0];
			else if(PROCESSING_LDST_COMPONENTS == true)	cout <<"line 170 : "<<SCREAM_SUCCESS[0];//SCREAM_PANIC[0];
			else if(PROCESSING_DLY_COMPONENTS == true)	cout <<"line 171 : "<<SCREAM_PANIC[0];//SCREAM_PANIC[0];
			break;
		case INPUT_0:
			break;

		case INPUT_1:
			break;

		case IMMEDIATE:
			break;

		case FUNCTION:
			break;


		case READ_ADRS:
			break;

		case WRITE_ADRS:
			break;

		case WRITE_DATA:
			break;

		default:
			break;
	}

}

inline void XML_Parser::PROCESS_ELEMENT_COMPONENTS_VALUE(const string str)
{
	int this_lexem = thisHelper.GetReserve(str);
	if(PROCESSING_IALU_COMPONENTS == true)
	{
		if(IALU_SUB_FLAG_PROCESSING_INSTANCE == true)
		{
				IALUS[ialu_ref_counter].alu_instance = str;
				IALU_SUB_FLAG_PROCESSING_INSTANCE = false;
		}
		else if (ALU_SUB_FLAG_PROCESSING_PORT_A == true)
		{
				IALUS[ialu_ref_counter].data_port_A = str;
				IALU_SUB_FLAG_PROCESSING_PORT_A = false;
		}
		else if (IALU_SUB_FLAG_PROCESSING_PORT_IMM == true)
		{
				IALUS[ialu_ref_counter].data_port_IMM = str;
				IALU_SUB_FLAG_PROCESSING_PORT_IMM = false;
		}
		else if(ALU_SUB_FLAG_PROCESSING_PORT_OUT == true)
		{
				IALUS[ialu_ref_counter].data_port_out = str;
				IALU_SUB_FLAG_PROCESSING_PORT_OUT = false;
		}
		else if(IALU_SUB_FLAG_PROCESSING_PORT_OPCODE == true)
		{
				IALUS[ialu_ref_counter].data_port_opcode = str;
				IALU_SUB_FLAG_PROCESSING_PORT_OPCODE = false;
				PROCESSING_IALU_COMPONENTS = false;
		}

	}
	else if(PROCESSING_ALU_COMPONENTS == true)
	{
		if(ALU_SUB_FLAG_PROCESSING_INSTANCE == true)
		{
				ALUS[alu_ref_counter].alu_instance = str;
				ALU_SUB_FLAG_PROCESSING_INSTANCE = false;
		}
		else if (ALU_SUB_FLAG_PROCESSING_PORT_A == true)
		{
				ALUS[alu_ref_counter].data_port_A = str;
				ALU_SUB_FLAG_PROCESSING_PORT_A = false;
		}
		else if (ALU_SUB_FLAG_PROCESSING_PORT_B == true)
		{
				ALUS[alu_ref_counter].data_port_B = str;
				ALU_SUB_FLAG_PROCESSING_PORT_B = false;
		}
		else if(ALU_SUB_FLAG_PROCESSING_PORT_OUT == true)
		{
				ALUS[alu_ref_counter].data_port_out = str;
				ALU_SUB_FLAG_PROCESSING_PORT_OUT = false;
		}
		else if(ALU_SUB_FLAG_PROCESSING_PORT_OPCODE == true)
		{
				ALUS[alu_ref_counter].data_port_opcode = str;
				ALU_SUB_FLAG_PROCESSING_PORT_OPCODE = false;
				PROCESSING_ALU_COMPONENTS = false;
		}

	}
	else if(PROCESSING_MEM_COMPONENTS == true)
	{
		if(MEM_SUB_FLAG_PROCESSING_INSTANCE == true)
		{
				MEMS[mem_ref_counter].mem_instance = str;
				MEM_SUB_FLAG_PROCESSING_INSTANCE = false;
		}
		else if(MEM_SUB_FLAG_PROCESSING_RD_ADRS == true)
		{
				MEMS[mem_ref_counter].rd_adrs = str;
				MEM_SUB_FLAG_PROCESSING_RD_ADRS = false;
		}
		else if(MEM_SUB_FLAG_PROCESSING_RD_EN_PORT == true)
		{
				MEMS[mem_ref_counter].rd_enable_port = str;
				MEM_SUB_FLAG_PROCESSING_RD_EN_PORT = false;
		}
		else if(MEM_SUB_FLAG_PROCESSING_LATENCY == true)
		{
				MEMS[mem_ref_counter].latency = str;
				MEM_SUB_FLAG_PROCESSING_LATENCY = false;
		}
		else if(MEM_SUB_FLAG_PROCESSING_WR_ADRS_PORT == true)
		{
				MEMS[mem_ref_counter].wr_adrs_port = str;
				MEM_SUB_FLAG_PROCESSING_WR_ADRS_PORT = false;

		}
		else if(MEM_SUB_FLAG_PROCESSING_WR_DATA_PORT == true)
		{
				MEMS[mem_ref_counter].wr_data_port = str;
				MEM_SUB_FLAG_PROCESSING_WR_DATA_PORT = false;
				PROCESSING_MEM_COMPONENTS = false;

		}
	}
	else if(PROCESSING_DLY_COMPONENTS == true)
	{
		if(DLY_SUB_FLAG_PROCESSING_DLY_INSTANCE == true)
		{
				DLYS[ldst_ref_counter].dly_instance = str;
				DLY_SUB_FLAG_PROCESSING_DLY_INSTANCE = false;

		}
		else if(DLY_SUB_FLAG_PROCESSING_DATA_PORT_IN == true)
		{
				LDSTS[ldst_ref_counter].data_size = str;
				DLY_SUB_FLAG_PROCESSING_DATA_PORT_IN = false;
				PROCESSING_DLY_COMPONENTS = false;
		}
	}
	else if(PROCESSING_LDST_COMPONENTS == true)
	{
		if(LDST_SUB_FLAG_PROCESSING_SIZE == true)
		{
				LDSTS[ldst_ref_counter].data_size = str;
				LDST_SUB_FLAG_PROCESSING_SIZE = false;

		}
		else if(LDST_SUB_FLAG_PROCESSING_INSTANCE == true)
		{
				LDSTS[ldst_ref_counter].ldst_instance = str;
				LDST_SUB_FLAG_PROCESSING_INSTANCE = false;
				PROCESSING_LDST_COMPONENTS = false;
		}
	}
}
inline void XML_Parser::TEST_INSTRUCTION_LINE()
{
	//for(int i=0; i < InstrVec.size(); i++){
	//	cout <<InstrVec[i] << endl;
	//}
	for(int i=0; i < FPGA_COMPONENTS.size(); i++)
	{
		for(int j=0; j < FPGA_COMPONENTS[i].size(); j++)
		{
			cout << FPGA_COMPONENTS[i][j] <<"\t";
		}
		cout << endl;
	}
}
inline void XML_Parser::PROCESS_ELEMENT_COMPONENTS(string str)
{
	int this_lexem = thisHelper.GetReserve(str);
	if (this_lexem == ALU_TYPE_)
	{
		PROCESSING_ALU_COMPONENTS = true;
		PROCESSING_IALU_COMPONENTS = false;
		PROCESSING_MEM_COMPONENTS = false;
		PROCESSING_DLY_COMPONENTS = false;
		PROCESSING_LDST_COMPONENTS = false;
		ALUS.push_back(element_ALU());
		alu_ref_counter = ALUS.size() - 1;
		ALUS[alu_ref_counter].element_name = str;
		std::cout << "ALU_TYPE_ = true"<<endl;
	}

	else if (this_lexem == IALU_TYPE_)
	{
		PROCESSING_ALU_COMPONENTS = false;
		PROCESSING_IALU_COMPONENTS = true;
		PROCESSING_MEM_COMPONENTS = false;
		PROCESSING_DLY_COMPONENTS = false;
		PROCESSING_LDST_COMPONENTS = false;
		IALUS.push_back(element_IALU());
		ialu_ref_counter = IALUS.size() - 1;
		IALUS[ialu_ref_counter].element_name = str;
		cout << "IALU_TYPE_ = true";
	}

	else if(this_lexem == LOAD_STORE_TYPE_)
	{
		PROCESSING_ALU_COMPONENTS = false;
		PROCESSING_IALU_COMPONENTS = false;
		PROCESSING_MEM_COMPONENTS = false;
		PROCESSING_DLY_COMPONENTS = false;
		PROCESSING_LDST_COMPONENTS = true;
		LDSTS.push_back(element_LDST());
		ldst_ref_counter = LDSTS.size() - 1;
		LDSTS[ldst_ref_counter].element_name = str;
		cout << "LOAD_TYPE_ = true";
	}

	else if(this_lexem == MEMORY_TYPE_)
	{
		PROCESSING_ALU_COMPONENTS = false;
		PROCESSING_IALU_COMPONENTS = false;
		PROCESSING_MEM_COMPONENTS = true;
		PROCESSING_DLY_COMPONENTS = false;
		PROCESSING_LDST_COMPONENTS = false;
		MEMS.push_back(element_MEM());
		mem_ref_counter = MEMS.size() - 1;
		MEMS[ldst_ref_counter].element_name = str;
		cout << "MEM_TYPE_ = true";
	}

	else if(this_lexem == DELAY_TYPE_)
	{
		PROCESSING_ALU_COMPONENTS = false;
		PROCESSING_IALU_COMPONENTS = false;
		PROCESSING_MEM_COMPONENTS = false;
		PROCESSING_DLY_COMPONENTS = true;
		PROCESSING_LDST_COMPONENTS = false;
		DLYS.push_back(element_DLY());
		dly_ref_counter = DLYS.size() - 1;
		DLYS[dly_ref_counter].element_name = str;
		cout << "DELAY_TYPE_ = true";
	}
	cout << "NOTHING\n";
}

inline void XML_Parser::__main__(const string& XMLFileObjName, const string& ConfigFileObjName)
{
	string word;
	int refCounter =0;
	int local_lexem = UNDEFINED;
	char c;
	int line_num = 0;
	int block_num = 0;
	ofstream ConfigFileObj(ConfigFileObjName);
	fstream XMLFileObj(XMLFileObjName);
	vector<string> InstrLine;
	InstrLine.clear();
	int find_open_tag;
	int find_close_tag;
	//std::regex re_opening("<(.*)");
	//std::regex find_element_instance1("[a-z][A-Z]")
	while(XMLFileObj.get(c))
	{

		int thisToken = thisHelper.GetToken(c);
		switch(thisToken)
		{
			case LESS_THAN:
				word.push_back(c);
				break;

			case EXCLAMATION:
				word.push_back(c);
				COMMENT_PROCESSING_TAGS = true;
				OPEN_COMMENT_TAG_FLAG = true;

				break;

			case HYPHEN:
				word.push_back(c);
				break;

			case GREATER_THAN:
				if (COMMENT_PROCESSING_TAGS == true) word.clear();
				else InstrVec.push_back(word);
				CLOSE_COMMENT_TAG_FLAG = false;
				OPEN_COMMENT_TAG_FLAG = false;
				OPEN_CONFIG_TAG_FLAG = false;
				CLOSE_CONFIG_TAG_FLAG = false;
				EQUAL_FLAG = false;
				INSTANCE_FLAG = false;
				//cout << InstrVec.size() << " "<<endl;
				if(InstrVec.size() == 0) InstrVec.clear();
				else if(InstrVec.size() == 5)
				{
					for(int i =0; i < 5; i++)
					{
						FPGA_COMPONENTS_PORTS.push_back(InstrVec[i]);
					}	FPGA_COMPONENTS_PORTS.push_back("NO_PORT");FPGA_COMPONENTS_PORTS.push_back("NO_PORT");
					 	FPGA_COMPONENTS_PORTS.push_back("NO_PORT");FPGA_COMPONENTS_PORTS.push_back("NO_PORT");FPGA_COMPONENTS_PORTS.push_back("NO_PORT");FPGA_COMPONENTS_PORTS.push_back("NO_PORT");
					 	FPGA_COMPONENTS_PORTS.push_back("NO_PORT");FPGA_COMPONENTS_PORTS.push_back("NO_PORT");
						FPGA_COMPONENTS.push_back(FPGA_COMPONENTS_PORTS);
						FPGA_COMPONENTS_PORTS.clear();
				}
				else if(InstrVec.size() == 11)
				{
					for(int i = 0; i < 11; i++)
					{
						FPGA_COMPONENTS_PORTS.push_back(InstrVec[i]);
					}
					FPGA_COMPONENTS_PORTS.push_back("NO_PORT");FPGA_COMPONENTS_PORTS.push_back("NO_PORT");
					FPGA_COMPONENTS.push_back(FPGA_COMPONENTS_PORTS);
					FPGA_COMPONENTS_PORTS.clear();
				}
				else if(InstrVec.size() == 13)
				{
					for(int i = 0; i < 13; i++)
					{
						FPGA_COMPONENTS_PORTS.push_back(InstrVec[i]);
					}FPGA_COMPONENTS.push_back(FPGA_COMPONENTS_PORTS);
					FPGA_COMPONENTS_PORTS.clear();
				}
				//for(int i=0; i < FPGA_COMPONENTS.size(); i ++)
				//{
				//	for(int j =0; j < FPGA_COMPONENTS[i].size(); j++) cout << FPGA_COMPONENTS[i][j]<< "  ";
				//}
				break;

			case NEWLINE:
				line_num++;
				COMMENT_PROCESSING_TAGS = false;
				word.clear();

				InstrVec.clear();
				//FPGA_COMPONENTS_PORTS.clear();
				break;

			case EQUAL:
				if( (COMMENT_PROCESSING_TAGS ) == true )
				{

					word.clear();
					continue;
				}
				else
				{
					InstrVec.push_back(word);

				}
				word.clear(); //watch out
				break;

			case FULL_STOP:
				word.push_back(c);
				break;

			case UNDERSCORE:
				word.push_back(c);
				break;

			case QUOTES:
				if(COMMENT_PROCESSING_TAGS == false)
				{
					if(LDST_SUB_FLAG_PROCESSING_SIZE == true)
					{
						InstrVec.push_back(word);
						//cout << "worked" <<endl;
					}
					//cout << LDSTS[ldst_ref_counter].data_size << endl;

				}
				break;

			case COMMA:
				//if (thisHelper.Count_Char_Occurs(word, '"') == 2)
				if(COMMENT_PROCESSING_TAGS == false)
				{
					InstrVec.push_back(word);
					//SET_FLAGS(thisHelper.GetReserve(word));
				}
				word.clear();
				break;

			case WHITESPACE: //chech if
				if(COMMENT_PROCESSING_TAGS == false)
				{
					if(word.find('<') != string::npos)
					{
						word.erase(std::find(word.begin(), word.end(), '<'));
						InstrVec.push_back(word);
						//cout << word<< "  : " <<thisHelper.GetReserve(word)<<" COMPONENT_TYPE "<<line_num<<"\n";
					}
				}

				word.clear();
				break;

			case LETTER:
				if(COMMENT_PROCESSING_TAGS == false)
				{
					word.push_back(c);
				}

				break;

			case DIGIT:
				if(COMMENT_PROCESSING_TAGS == false)
				{

					word.push_back(c);


				}
				break;



			default:
				break;
		}
	}

}
/*
	THERE IS NO SUCH THING AS LINEAR ORDER IN LANGUAGE. LANGUAGE IS REFLEXIVE
	EUGINE PRINCIPLE.
*/
#endif
