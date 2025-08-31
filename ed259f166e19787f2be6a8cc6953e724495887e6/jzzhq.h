#ifndef E46FCEB5_2520_4A00_B760_65DF2C6F80DB
#define E46FCEB5_2520_4A00_B760_65DF2C6F80DB
#include<string>
using namespace std;
class Jzzhq {
public:
	//对外接口
	//进制转换
	//原进制，目标进制，精度，待转化数字
	//转换失败发送error
	string change(int, int, int, string);


private:

	//拆分字符串数字，将其拆为整数部分和小数部分
	//原字符串数字，整数部分，小数部分
	void splitNum(string, string&, string&);

	//将字符数字转换为数字
	int stn(char);

	//数字转换字符
	char nts(int);

	//输入校验
	//进制，待检验的字符串
	bool check(int, string);


};











#endif /* E46FCEB5_2520_4A00_B760_65DF2C6F80DB */
