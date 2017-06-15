#include "Convert_to_VHD_Config.h"

/*
enum EnumType{
	FIRST_ENUM_TYPE,
	A = FIRST_ENUM_TYPE,
	B,
	C,
	LAST_ENUM_TYPE
};*/
void removeSubstrs(string& s, const string& p)
{
	int n = p.length();
	for (int i = s.find(p);  i != p.npos; i = s.find(p))  
		s.erase(i, n);
	
}
int main(){
	string wholeStr = "LDST0.data";
	string sub = ".data";
	removeSubstrs(wholeStr, sub);
	cout << wholeStr << endl;
}