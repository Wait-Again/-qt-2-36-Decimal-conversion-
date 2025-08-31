#include<string> 
#include"jzzhq.h"
using namespace std;


void Jzzhq::splitNum(string num, string& integer, string& decimal)
{

	//获取数字字符串长度
	int len = (int)num.length();
	//索引
	int i = 0;
	//寻找小数点位置
	for (; i < len; i++)
	{
		if (num[i] == '.')
		{
			break;
		}
	}
	//截取整数部分和小数部分
	integer = num.substr(0, i);
	//当有小数部分时
	if (i != len)
	{
		decimal = num.substr(i + 1, len - i - 1);
	}
}

int Jzzhq::stn(char strnum) {
	//字符0到9
	if (strnum >= 48 && strnum <= 57)
	{
		return (int)strnum - 48;
	}
	//字符A到Z
	else if (strnum >= 65 && strnum <= 90) {
		return (int)strnum - 55;
	}
	//字符a到z
	else if (strnum >= 97 && strnum <= 122)
	{
		return (int)strnum - 87;
	}
	else
	{
		return -1;
	}
}

char Jzzhq::nts(int num) {
	if (num >= 0 && num <= 9)
	{
		return to_string(num)[0];
	}
	else if (num >= 10 && num <= 36) {
		return num + 55;
	}
	else {
		return '*';
	}
}

bool Jzzhq::check(int m, string num) {
	//进制超限
	if (m < 2 || m>36)
	{
		return false;
	}
	//检查字母
	for (int i = 0; i < (int)num.length(); i++)
	{
		//检查数字部分
		if (num[i] <= 57 && num[i] >= 48)
		{
			//数字部分大于进制
			if (num[i] - 48 > m-1)
			{
				return false;
			}
		}
		//大写字母部分
		else if (num[i] <= 90 && num[i] >= 65) {
			if (num[i] - 65 > m - 11) {
				return false;
			}
		}
		//小写字母部分
		else if (num[i] <= 122 && num[i] >= 97) {
			if (num[i] - 97 > m - 11) {
				return false;
			}
		}
		//不合规的字符
		else {
			return false;
		}
	}
	//通过检查
	return true;

}

string Jzzhq::change(int m, int n, int jd, string num) {


	bool fs = false;
	//检查是否为负数
	if (num[0] == '-')
	{
		fs = true;
		//截取整数部分
		num = num.substr(1, num.length() - 1);
	}


	//中间十进制数整数部分
	long long num10 = 0;
	//中间十进制数小数部分
	double dnum10 = 0;
	//整数部分和小数部分
	string integer = "0", decimal = "0";
	//进行拆分
	splitNum(num, integer, decimal);

	//分别进行合法性检验
		//未通过检验
	if (!check(m, integer) || !check(m, decimal))
	{
		return (string)"error";
	}

	//原进制转向十进制
	//整数部分转十进制
	for (int i = 0; i < (int)integer.length(); i++)
	{
		//该位上的数乘以权重
		num10 += (long long)(stn(integer[i]) * pow(m, integer.length() - 1 - i));
	}
	//当有小数时
	if (decimal != "0")
	{
		for (int i = 0; i < (int)decimal.length(); i++)
		{
			dnum10 += (double)(stn(decimal[i]) * pow(m, -(i + 1)));
		}
	}
	//十进制转向目标进制
	//目标进制的整数部分,目标进制的小数部分
	string tari = "", tard = "", tempTari = "";
	//整数部分
	//商与余
	long long int quotient = num10, remainder = 0;
	//当商不为零时
	while (quotient)
	{
		//取得商除以目标进制的余数
		remainder = quotient % n;
		//更新商
		quotient /= n;
		//将得到的余数拼接到结果的临时整数部分上去
		tempTari += nts(remainder);
	}
	//前后交换！(此处由于前面拼接是从最后一位开始拼接的，所以最后需要倒过来)
	for (int i = (int)tempTari.length() - 1; i >= 0; i--)
	{
		// 修改整数部分处理逻辑
		string tari = tempTari.empty() ? "0" : string(tempTari.rbegin(), tempTari.rend());
	}
	//有小数部分时
	if (dnum10 != 0) {
		//小数部分乘以目标进制得到的整数部分
		int tempTard = 0;
		//依照精度进行循环
		for (int i = 0; i < jd; i++)
		{
			//得到乘以进制后的整数部分
			tempTard = (int)(dnum10 * n);
			tard += nts(tempTard);
			//更新小数
			dnum10 = dnum10 * n - tempTard;
		}
	}

	//判断是否要加上负号
	if (fs) {
		return "-" + (tari == "" ? "0" : tari + (tard == "" ? "" : ("." + tard)));
	}
	else
	{
		return tari == "" ? "0" : tari + (tard == "" ? "" : ("." + tard));
	}


}