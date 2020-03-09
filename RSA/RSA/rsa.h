#pragma once
#include <iostream>
using namespace std;
#include <time.h>
#include <fstream>
#include <math.h>
#include <boost/multiprecision/cpp_int.hpp>
typedef long DataType;
#define NUMBER 256         //元素的个数

struct Key
{
	// (e，n)  (d,n)
	DataType _ekey;      //加密的密钥
	DataType _dkey;      //解密的密钥
	DataType _pkey;		 //公共的部分
};

/*
	1.产生素数
	2.求n
	3.求f(n)
	4.求 e   1< e < f(n) ,e 和 f(n) 构成互质，随机选择
	5.求d : e * d % f(n) = 1
	(e，n)  (d,n)
*/

class RSA
{
public:
	RSA()                                                  //构造函数
	{
		getKeys();
	}
	//加密
	void ecrept(const char* filename, const char* fileout)
	{
		ifstream fin(filename, std::ifstream::binary);
		ofstream fout(fileout, std::ifstream::binary);

		if (!fin.is_open())
		{
			perror("Input file open failed!");
			return;
		}
		char * buffer = new char[NUMBER];     //每次读数据时存放数据的缓存区
		DataType* bufferOut = new DataType[NUMBER];
		while (!fin.eof())
		{
			fin.read(buffer, NUMBER);
			int curNum = fin.gcount();          //最近一次读取的字节数   也表示元素的个数
			for (int i = 0; i < curNum; ++i)
			{
				bufferOut[i] = ecrept((DataType)buffer[i], _key._ekey, _key._pkey);    //对每个字节进行加密的操作
			}
			fout.write((char*)bufferOut, curNum * sizeof(DataType));                   //将加密后的信息输出
		}

		delete[] bufferOut;
		delete[] buffer;
		fin.close();
		fout.close();
	}

	//解密
	void dcrept(const char* filename, const char* fileout)
	{
		ifstream fin(filename, ifstream::binary); 
		ofstream fout(fileout,ifstream::binary);
		if (!fin.is_open())
		{
			perror("File open failed!");
			return;
		}
		DataType * buffer = new DataType[NUMBER];          //输入缓冲区
		char * bufferOut = new char[NUMBER];			   //输出缓冲区

		while (!fin.eof())
		{
			fin.read((char*)buffer, NUMBER * sizeof(DataType));     //NUMBER * sizeof(DataType)  读取的字节数
			int num = fin.gcount();                                 //实际读入的字节数
			num /= sizeof(DataType);                                //实际读入的元素个数

			for (int i = 0; i < num; ++i)
			{
				bufferOut[i] = decrept(buffer[i], _key._dkey, _key._pkey);
			}
			fout.write(bufferOut, num);
		}

		delete[] bufferOut;
		delete[] buffer;
		fout.close();
		fin.close();
	}


	void getKeys()                                             //初始化
	{
		DataType prime1 = getPrime();
		DataType prime2 = getPrime();

		while (prime1 == prime2)
		{
			prime2 = getPrime();
		}

		DataType orla = getOrla(prime1, prime2);
		_key._pkey = getPkey(prime1, prime2);
		_key._ekey = getEkey(orla);
		_key._dkey = getDkey(_key._ekey, orla);
	}

	Key getAllKey()
	{
		return _key;
	}

	//加密解密  a^b % n
	DataType ecrept(DataType data, DataType ekey, DataType pkey)		  //加密
	{
		//pow :运算溢出
		//return (long)pow(data, ekey) % pkey;

		//i: 0,……最后一位
		DataType Ai = data;
		DataType msgE = 1;

		while (ekey) 
		{
			if (ekey & 1)            //取出解密的密钥二进制的每一位如果该位为1则进行累乘
			{
				msgE = (msgE * Ai) % pkey;
			}

			ekey >>= 1;				//将解密的密钥的二进制位右移
			Ai = (Ai * Ai) % pkey;     
		}
		return msgE;
	}

	DataType decrept(DataType data, DataType dkey, DataType pkey)		  //解密
	{
		return ecrept(data, dkey, pkey);
	}

	DataType getPrime()                                       //获取素数
	{
		srand(time(NULL));
		DataType prime;
		while (1)
		{
			prime = rand() % 100 + 2;
			if (isPrime(prime))
			{
				break;
			}
		}
		return prime;
	}

	bool isPrime(DataType data)								 //判断是否是素数
	{
		if (data <= 0)
		{
			return false;
		}
		for (int i = 2; i <= sqrt(data); i++)
		{
			if (data % i == 0)
			{
				return false;
			}
		}
		return true;
	}

	DataType getPkey(DataType prime1, DataType prime2)       //获取公共部分
	{
		return prime1 * prime2;
	}

	DataType getOrla(DataType prime1, DataType prime2)		 //获取欧拉函数的值
	{
		return (prime1 - 1) * (prime2 - 1);
	}

	//e ：1< e < f(n)
	DataType getEkey(DataType orla)						    //获取加密密钥
	{
		srand(time(NULL));
		DataType ekey;
		while (1)
		{
			ekey = rand() % orla;
			if (ekey > 1 && getGcd(ekey, orla) == 1)
			{
				return ekey;
			}
		}
	}

	//d : e * d % f(n) = 1;
	DataType getDkey(DataType ekey, DataType orla)			 //获取解密密钥
	{
		DataType dkey = orla / ekey;
		while (1)
		{
			if ((ekey * dkey) % orla == 1)
			{
				return dkey;
			}
			++dkey;
		}
	}

	//辗转相除法
	DataType getGcd(DataType data1, DataType data2)		 //获取最大公约数
	{
		DataType tmp = 0;

		while (tmp = data1 % data2)
		{
			data1 = data2;
			data2 = tmp;
		}

		return data2;
	}
private:
	Key _key;
};