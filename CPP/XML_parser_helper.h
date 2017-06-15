#ifndef XML_PARSER_HELPER_H
#define XML_PARSER_HELPER_H
#include "Convert_to_VHD_Config.h"

class TokenHelper
{
	public:
		
		vector<string> micro_ops;
		vector<string> macro_ops;
		vector<string> registers;
		vector<string> INSTR;


		inline bool IsNumber(const std::string& thisWord);
		inline bool StringEqualCaseIgnore( const std::string& s1, const std::string& s2 );
		inline bool Is_Same_Char(const std::string& thisWord);
		inline int  Count_Char_Occurs(const std::string& s, const char arbt_char);
		inline int GetReserve(const string& s);
		inline int GetALUFunction(const string& s);
		inline int FPGA_Element_Type(const string& s);
		//inline int GetALUInputs(const string& s);
		inline int GetToken(char this_char);
		inline void split(const string& word, char ch, vector<string>& Vec);
		inline string removesubStr(const string& Str, const string& subStr);
};
inline int  TokenHelper::Count_Char_Occurs(const std::string& s, const char arbt_char)
{
	int count = 0;
	for(int i = 0; i < s.length(); i++)
	{
		if(s[i] == arbt_char) count++;
	}
	return count;
}
/*
inline int TokenHelper::return_FPGA_Element_Type(const string& s)
{
	if(StringEqualCaseIgnore(s, "LDST"))
	{
		return ELEMENT_LOAD_STORE;
	}
	else if(StringEqualCaseIgnore(s, "IALU"))
	{
		return ELEMENT_ALU;
	}
	else if(StringEqualCaseIgnore(s, "MEM512b"))
	{
		return ELEMENT_DELAY;
	}
	else if(StringEqualCaseIgnore(s, "DLY"))
	{
		return ELEMENT_LOAD_STORE;
	}
	else return ELEMENT_UNKNOWN;
}
*/	
inline bool TokenHelper::IsNumber(const std::string& thisWord)
{
	std::string::const_iterator it = thisWord.begin();
	while (it != thisWord.end() && std::isdigit(*it))
				    	++it;
	return (!thisWord.empty() && it == thisWord.end());
}

			
inline bool TokenHelper::StringEqualCaseIgnore( const std::string& s1, const std::string& s2 ) 
{
	std::string scpy1( s1 );
	std::string scpy2( s2 );
	std::transform( scpy1.begin(), scpy1.end(), scpy1.begin(), ::tolower );
	std::transform( scpy2.begin(), scpy2.end(), scpy2.begin(), ::tolower );
	return ( scpy1 == scpy2 );
}


inline bool TokenHelper::Is_Same_Char(const std::string& thisWord)
{
	return (thisWord.empty() || thisWord.find_first_not_of(thisWord[0]) == std::string::npos);
}

inline int TokenHelper::GetReserve(const string& s)
{
				//auto wordToken = VALUES;
				
			if (StringEqualCaseIgnore( s, "<!--"))
				return XML_COMMENT_OPENING_TAGS;


			else if (StringEqualCaseIgnore( s, "-->"))
					return XML_COMMENT_CLOSING_TAGS;

			else if(StringEqualCaseIgnore(s, "IALU"))
					return IALU_TYPE_;

			else if(StringEqualCaseIgnore(s, "ALU"))
					return ALU_TYPE_;

			else if(StringEqualCaseIgnore(s, "LDST"))
			{
				return LOAD_STORE_TYPE_;
			}
			else if(StringEqualCaseIgnore(s, "size")) return SIZE;
			//else if(StringEqualCaseIgnore(s, "IALU"))
			else if(StringEqualCaseIgnore(s, "MEM512b"))
			{
				return MEMORY_TYPE_;
			}
			else if(StringEqualCaseIgnore(s, "DLY"))
			{
				return DELAY_TYPE_;
			}

			else if(StringEqualCaseIgnore( s, "instance"))return INSTANCE;

			else if(StringEqualCaseIgnore(s, "in_0"))
					return INPUT_0;

			else if (StringEqualCaseIgnore( s, "in_1"))
					return INPUT_1;


			else if(StringEqualCaseIgnore(s, "immed"))
					return IMMEDIATE;

			else if(StringEqualCaseIgnore(s, "funct")) 
					return FUNCTION;

			else if(StringEqualCaseIgnore(s, "MEM512b"))
					return MEMORY_TYPE_;

			else if(StringEqualCaseIgnore(s, "latency"))
					return LATENCY;

			else if(StringEqualCaseIgnore(s, "rd_adrs"))
					return READ_ADRS;	

			else if(StringEqualCaseIgnore(s, "rd_enable"))
					return READ_EN;			

			else if(StringEqualCaseIgnore(s, "wr_adrs"))
					return WRITE_ADRS;	

			else if(StringEqualCaseIgnore(s, "wr_data"))
					return WRITE_DATA;	

			else 
					return UNKNOWN_RESERVE;
}

inline int TokenHelper::GetToken(char this_char)
{
	char ch = this_char;
	auto char_Token = -1;
	if ((ch > AT_SYM && ch < SQR_BRAC_LT) || (ch > GRAVE_ACCENT && ch < CURLY_BRAC_LT) )
		char_Token = LETTER;

	else if ((ch > FORWARD_SLASH) && (ch < COLON))
		char_Token = DIGIT;

	else if (ch == '-')
		char_Token = HYPHEN;

	else if (ch == '#')
		char_Token = NUMBER_SYM;

	else if (ch == '$')
		char_Token = DOLLAR_SYM;

	else if (ch == '%')
		char_Token = PERCENT_SYM;

	else if (ch == '&')
		char_Token = AMPERSAND;

	else if (ch == '!')
		char_Token = EXCLAMATION;

	else if (ch == '"')
		char_Token = QUOTES;

	else if (ch == ' ')
		char_Token = WHITESPACE;

	else if (ch == ',')
		char_Token = COMMA;

	else if (ch == '*')
		char_Token = ASTERICK;

	else if (ch == ':')
		char_Token = COLON;

	else if (ch == '.')
		char_Token = FULL_STOP;

	else if (ch == '/')
		char_Token = FORWARD_SLASH;

	else if (ch == '0')
		char_Token = ZERO;

	else if (ch == '1')
		char_Token = ONE;

	else if (ch == '2')
		char_Token = TWO;

	else if (ch == '3')
		char_Token = THREE;

	else if (ch == '4')
		char_Token = FOUR;

	else if (ch == '5')
		char_Token = FIVE;

	else if (ch == '6')
		char_Token = SIX;

	else if (ch == '7')
		char_Token = SEVEN;

	else if (ch == '8')
		char_Token = EIGTH;

	else if (ch == '9')
		char_Token = NINE;

	else if (ch == ':')
		char_Token = COLON;

	else if (ch == ';')
		char_Token = SEMI_COLON;

	else if (ch == '<')
		char_Token = LESS_THAN;

	else if(ch == '=')
		char_Token = EQUAL;

	else if(ch == '>')
		char_Token = GREATER_THAN;

	else if(ch == '?')
		char_Token = QUESTION_MARK;

	else if(ch == '@')
		char_Token = AT_SYM;

	else if(ch == '[')
		char_Token = SQR_BRAC_LT;

	else if(ch == '\\')
		char_Token = BACK_SLASH;

	else if(ch == ']')
		char_Token = SQR_BRAC_RT;

	else if(ch == '^')
		char_Token = CARET;

	else if(ch == '_')
		char_Token = UNDERSCORE;

	else if(ch == '`')
		char_Token = GRAVE_ACCENT;

	else if(ch == '{')
		char_Token = CURLY_BRAC_LT;

	else if(ch == '|')
		char_Token = VERTICAL_BAR;

	else if(ch == '~')
		char_Token = TILDE;

	else if(ch == 127)
		char_Token = DELETE;

	else if(ch == '\n')
		char_Token = NEWLINE;
	else
		char_Token = UNDEFINED;

	return char_Token;
}

inline void TokenHelper::split(const string& word, char ch, vector<string>& Vec)
{
	size_t i = 0;
	size_t j = word.find(ch);
	while ( j != string::npos)
	{
		Vec.push_back(word.substr(i, j-i));
		i = ++j;
		j = word.find(ch,j);
		if (j == string::npos)	
			Vec.push_back(word.substr(i, word.length()));
		
	} 
}
//inline string TokenHelper::removesubStr(const string& Str, const string& subStr)
//{
//	string::size_type foundpos = Str.find(subStr);
//	if(foundpos != string::npos)
//		{ 
//			Str.erase(Str.begin() + foundpos, Str.begin() + foundpos + subStr.length());
//		}
//}

#endif














