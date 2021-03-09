// 04-RapidJson.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/pointer.h"
#include <cstdio>
#include "string"
#include <iostream>
#include <sstream>
#include <vector>
#include <windows.h>

using namespace rapidjson;
using namespace std;

char* UnicodeToUtf8(const wchar_t* unicode);
wchar_t* UTF8ToUnicode(const char* str);


rapidjson::Document document;

void fun2();
void fun4();

int main()
{

    fun4();
    //pointFun();


    system("pause");// 暂停以显示终端窗口
}




/*

{
   "data" : {
      "avatar" : "http://xxxxxxx",
      "nickname" : "xxxxx",
      "wxid" : "wxid_xxxxxxx"
   },
   "type" : 11028
}

*/
void fun2() {

    Document doc;
    doc.SetObject();
    Document::AllocatorType& allocator = doc.GetAllocator(); //获取分配器


    doc.AddMember("type", 11028, allocator);

    Value vData(kArrayType);


    //构建userinfo数据
    Value vUserInfo(kObjectType);

    //wxid
    char wxid[50] = { 0 };
    sprintf(wxid, "wx_id1222");
    Value vWxid(wxid, doc.GetAllocator());
    vUserInfo.AddMember("wxid", vWxid, allocator);

    //nickname
    wchar_t nickname[100] = { 0 };
    sprintf(wxid, "wx_id1222");
    Value vNickName(UnicodeToUtf8(nickname), doc.GetAllocator());
    vUserInfo.AddMember("nickname", vNickName, allocator);
    
    //avatar
    char avatar[100] = { 0 };
    sprintf(avatar, "http://124.com");
    Value vAvatar(avatar, doc.GetAllocator());
    vUserInfo.AddMember("avatar", vAvatar, allocator);


    vData.PushBack(vUserInfo, allocator);
    doc.AddMember("data", vData, allocator);


    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    doc.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
    std::cout << sb.GetString() << std::endl;

}



void fun4()
{
    //rapidjson::Document document;
    document.SetObject();
    //rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    //rapidjson::Value object1(rapidjson::kObjectType);

    //document.AddMember("StCode", "SS1211054", allocator);
    //document.AddMember("Timestamp", "2020-02-24 13:50:41", allocator);

    // 数组
    rapidjson::Value alarmArray(rapidjson::kArrayType);

    for (int i = 0; i < 3; i++)
    {
        char strParamCode[128] = { 0 };
        sprintf(strParamCode, "param%d", i + 1);

        rapidjson::Value objectTemp(rapidjson::kObjectType);
        rapidjson::Value valueParamCode(strParamCode, document.GetAllocator());
        objectTemp.AddMember("paramCode", valueParamCode, document.GetAllocator());
        objectTemp.AddMember("value", i + 10, document.GetAllocator());
        objectTemp.AddMember("mark", "N", document.GetAllocator());

        alarmArray.PushBack(objectTemp, document.GetAllocator());
    }

    document.AddMember("Alarm", alarmArray, document.GetAllocator());

    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    std::string jsonStr2 = buffer.GetString();
    // 打印生成的json字符串
    std::cout << "test2(), strJson2为: " << jsonStr2.c_str() << std::endl;
}


/*
    UnicodeToUtf8
*/
char* UnicodeToUtf8(const wchar_t* unicode)
{
    int len;
    len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
    char* szUtf8 = (char*)malloc(len + 1);
    if (szUtf8 != 0) {
        memset(szUtf8, 0, len + 1);
    }
    WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL, NULL);
    return szUtf8;
}

/*
    UTF8ToUnicode
*/
wchar_t* UTF8ToUnicode(const char* str)
{
    int    textlen = 0;
    wchar_t* result;
    textlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    result = (wchar_t*)malloc((textlen + 1) * sizeof(wchar_t));
    if (result != 0)
    {
        memset(result, 0, (textlen + 1) * sizeof(wchar_t));
    }
    MultiByteToWideChar(CP_UTF8, 0, str, -1, (LPWSTR)result, textlen);
    return    result;
}
