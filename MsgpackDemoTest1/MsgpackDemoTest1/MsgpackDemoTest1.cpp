// MsgpackDemoTest1.cpp: 控制台程序测试

#include "stdafx.h"
#include <iostream>
#include <vector>
#include<sstream>
#include <cassert>
#include "msgpack.hpp"
using namespace std;


#ifdef _DEBUG
#pragma comment(lib,"msgpackd.lib")
#else
#pragma comment(lib,"msgpack.lib")
#endif

class mypoint
{
private:
	int x;
	int y;
	int z;
public:
	mypoint() {}
	mypoint(int tx, int ty, int tz)
	{
		x = tx;
		y = ty;
		z = tz;
	}
public:
	MSGPACK_DEFINE(x, y, z);
};

class  myObject
{
private:
	vector<mypoint>  points;
	string  name;
public:
	myObject() {}
	myObject(string tname, vector<mypoint> const & tpoints)
	{
		name = tname;
		points = tpoints;
	}
	MSGPACK_DEFINE(name, points);
};

void testMyObject()
{

	// serializes my object 
	myObject  obj1("ABC", { { 0,0,0 },{ 1,1,1 },{ 2,2,2 } });
	//myObject  obj2("DEF", { {3,3,3 },{ 4,4,4 },{ 5,5,5 } });
	std::stringstream  ss;
	msgpack::pack(ss, obj1);

	// Deserialize my object
	auto oh = msgpack::unpack(ss.str().data(), ss.str().size());
	msgpack::object obj = oh.get();

	std::cout << obj << std::endl;


	myObject ob = obj.convert();  // convert to my object;

								  //assert( obj.as<decltype(obj1)>() == obj1);

}


int main()
{
	std::cout << MSGPACK_VERSION << std::endl;


	// serializes this object.
	std::vector<std::string> vec;
	vec.push_back("Hello");
	vec.push_back("MessagePack");

	// serialize it into simple buffer.
	msgpack::sbuffer sbuf;
	msgpack::pack(sbuf, vec);

	// deserialize it.
	msgpack::object_handle oh =
		msgpack::unpack(sbuf.data(), sbuf.size());

	// print the deserialized object.
	msgpack::object obj = oh.get();
	std::cout << obj << std::endl;  //=> ["Hello", "MessagePack"]

									// convert it into statically typed object.
	std::vector<std::string> rvec;
	obj.convert(rvec);

	// my object test
	testMyObject();

	return 0;
}

