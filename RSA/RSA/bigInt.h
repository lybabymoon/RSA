#pragma once
#include <string>
#include <iostream>
#include <utility>
#include <functional>
using namespace std;
class BigInt
{
public:
	BigInt(){}
	BigInt(const string & num)
		:_number(num)
	{

	}
	BigInt(const int num);

	BigInt BigInt::operator+(BigInt& bi)
	{
		string ans = add(_number, bi._number);
		return BigInt(ans);
	}

	BigInt BigInt::operator-(BigInt& bi)
	{
		string ans = sub(_number, bi._number);
		return BigInt(ans);
	}

	BigInt BigInt::operator*(BigInt& bi)
	{
		string ans = mul(_number, bi._number);
		return BigInt(ans);
	}

	BigInt BigInt::operator/(BigInt& bi)
	{
		pair<string, string> ans = dev(_number, bi._number);
		return BigInt(ans.first);
	}

	BigInt BigInt::operator%(BigInt& bi)
	{
		pair<string, string> ans = dev(_number, bi._number);
		return BigInt(ans.second);
	}

	BigInt& BigInt::operator+=(BigInt& bi);
	BigInt& BigInt::operator-=(BigInt& bi);
	BigInt& BigInt::operator*=(BigInt& bi);
	BigInt& BigInt::operator/=(BigInt& bi);
	BigInt& BigInt::operator%=(BigInt& bi);

	BigInt& operator++()               //++i
	{

	}

	BigInt operator++(int)			  //i++
	{

	}

	BigInt& operator--()
	{

	}

	BigInt operator--(int)
	{

	}

	friend ostream& operator<<(ostream& _cout, BigInt& bi);
private:
	string _number;
	string add(string num1, string num2)                            //大数加法
	{
		string ans;
		int i = num1.size()-1;
		int j = num2.size()-1;
		int curNum = 0;
		while (i >= 0 || j >= 0 || curNum != 0)
		{
			if (i >= 0)
			{
				curNum += num1[i--] - '0';
			}

			if (j >= 0)
			{
				curNum += num2[j--] - '0';
			}

			ans += to_string(curNum % 10);
			curNum /= 10;
		}

		reverse(ans.begin(), ans.end());
		return ans;
	}

	string sub(string num1, string num2)                           //大数减法    num1 > num2
	{
		string ans;
		int i = num1.size() - 1;
		int j = num2.size() - 1;
	
		if (i >= j)
		{
			int len = i - j;
			num2.insert(num2.begin(),len, '0');
			j = i;
		}
		else
		{
			int len = j - i;
			num1.insert(num1.begin(),len, '0');
			i = j;
		}

		//while (i>=0 && j>=0)
		int curNum = 0;

		while (i >= 0 || j >= 0)
		{
			if (num1[i] >= num2[j])
			{
				curNum = (num1[i] - '0') - (num2[j] - '0');
			}
			else
			{
				--num1[i - 1];
				num1[i] += 10;
				curNum = (num1[i]-'0') - (num2[j] - '0');
			}
			--i;
			--j;
			ans += to_string(curNum);
		}
		reverse(ans.begin(), ans.end());

		while (ans.front() == '0')
		{
			ans.erase(ans.begin());
		}
		return ans;
	}

	string mul(string num1, string num2)							//大数乘法
	{
		int len1 = num1.size();
		int len2 = num2.size();
		if (len1 > len2)
		{
			swap(num1, num2);
			swap(len1, len2);
		}
		int curNum = 0;
		int carryNum = 0;
		string ans;
		
		for (int i = len1 - 1; i >= 0; --i)
		{
			string tmp;
			for (int j = len2 - 1; j >= 0 ; --j)
			{
				curNum = (num1[i] - '0') * (num2[j] - '0') + carryNum;
				carryNum = curNum / 10;
				tmp += to_string(curNum%10);
			}
			tmp.insert(tmp.begin(), len1 - 1 - i, '0');
			reverse(tmp.begin(), tmp.end());
			ans = add(ans, tmp);
		}
		return ans;
	}

	pair<string, string> dev(string num1, string num2)                 //大数除法
	{
		string ans;
		string rem = num1;        //余数
		int len = num1.size() - num2.size();
		num2.append(num1.size() - num2.size(), '0');
		for (int i = 0; i <= len; i++)
		{
			char count = '0';
			while (1)
			{
				if (less(rem, num2))
				{
					break;
				}

				rem = sub(rem , num2);
				++count;
			}
			ans += count;
			num2.pop_back();     //除数减小十倍
		}
		while (ans.size() > 1 && ans[0] == '0')
		{
			ans.erase(0, 1);
		}

		return make_pair(ans, rem);
	}

	bool less(string num1, string num2)      //小于
	{
		if (num1.size() < num2.size())
		{
			return true;
		}

		if (num1.size() > num2.size())
		{
			return false;
		}
		return num1 < num2;           //长度相同
	}
};

ostream& operator<<(ostream& _cout, BigInt& bi)
{
	_cout << bi._number << endl;
	return _cout;
}