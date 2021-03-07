// 04-RapidJson.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/pointer.h"
#include <cstdio>
#include "string"
#include <iostream>


using namespace rapidjson;
using namespace std;


int main()
{
	Document doc;
	doc.SetObject();
	Document::AllocatorType& allocator = doc.GetAllocator(); //获取分配器

	doc.AddMember("event", "event", allocator);

	Value contactArray(kArrayType);

	string str = "abc";

	for (int i = 0; i < 3; i++) {

		Value storage_photo_count(kStringType);
		std::string storage_photo_count_str(str);
		storage_photo_count.SetString(storage_photo_count_str.c_str(),storage_photo_count_str.size(), allocator);

		Value contactObj(kObjectType);
		contactObj.AddMember("hobby", "drawing", allocator);
		contactObj.AddMember("count", storage_photo_count, allocator);
		contactArray.PushBack(contactObj, allocator);
	}

	doc.AddMember("data", contactArray, allocator);

	StringBuffer sb;
	PrettyWriter<StringBuffer> writer(sb);
	doc.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
	std::cout << sb.GetString() << std::endl;
}
