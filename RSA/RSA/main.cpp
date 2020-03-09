#include "rsa.h"
#include "bigInt.h"

void test()
{
	RSA rsa;
	rsa.getKeys();
	Key key = rsa.getAllKey();
	cout << "keys : " << endl;
	cout << key._ekey<< " " << key._dkey << " " << key._pkey <<endl;
	DataType original = 2;

	DataType decout = rsa.ecrept(original, key._ekey, key._pkey);
	cout << "original: " << original << endl;
	cout << "ecrept: " << decout << endl;
	cout << "decrpet: " << rsa.decrept(decout, key._dkey, key._pkey) << endl;
}

void testRSA()
{
	RSA rsa;
	Key key = rsa.getAllKey();
	cout << "(e,n)" << key._ekey << "," << key._pkey << endl;
	cout << "(n,d)" << key._pkey << "," << key._dkey << endl;
	rsa.ecrept("test.txt", "test.ecrpet.txt");
	rsa.dcrept("test.ecrpet.txt", "test.decrpet.txt");

	cout << "success" << endl;
}

void testBigInt()
{
	BigInt bi;
	int a = 123;
	int b = 321534;

	/*cout << a - b << endl;
	cout << bi.sub("1001", "999") <<endl;
	cout << a + b << endl;
	cout << bi.add("123452121", "541215");*/

	//cout << a * b << endl;
	//cout << bi.mul("12365461651651", "651651561654665");

	/*cout << bi.dev("123", "47").first << " " << bi.dev("123", "47").second << endl;*/
	cout << a * b << endl;
	BigInt aa = "123";
	BigInt bb = "321534";
	cout << aa * bb << endl;
	cout << aa << endl;
	cout << bb << endl;
}
int main()
{
	testRSA();
	//testBigInt();
	//test();
	return 0;
}