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

void func();
void fun2();
void fun4();
void jiexiJson();

int main()
{
    //func();
    fun2();
    //pointFun();
    //jiexiJson();


    system("pause");// 暂停以显示终端窗口
}


void func()
{
    //rapidjson::Document* ptr_doc = new rapidjson::Document();
    //ptr_doc->Parse("{}");
    //rapidjson::Document::AllocatorType& allocator = ptr_doc->GetAllocator();

    //rapidjson::Value current_gameplay(rapidjson::kObjectType);
    //rapidjson::Value current_gameplay_achievements(rapidjson::kObjectType);
    //ptr_doc->AddMember("current_gameplay", current_gameplay, allocator);//对象添加
    //ptr_doc->AddMember("current_gameplay_achievements", current_gameplay_achievements, allocator);

    //rapidjson::Value user(rapidjson::kObjectType);
    //if (!(*ptr_doc)["current_gameplay"].GetObject().HasMember("user"))//判断是否user对象
    //{
    //    (*ptr_doc)["current_gameplay"].AddMember("user", user, allocator);//current_gameplay对象添加user对象
    //}

    //rapidjson::Value strObject(rapidjson::kStringType);
    //strObject.SetString("123");
    //(*ptr_doc)["current_gameplay"]["user"].AddMember("id", strObject, allocator);//current_gameplay的user对象添加 id:"123";

    //(*ptr_doc)["current_gameplay"]["user"]["id"].SetString("321");//current_gameplay的user对象修改为 id:"321";
    //(*ptr_doc)["current_gameplay"]["user"].RemoveMember("id");//current_gameplay的user对象删除id项
    //rapidjson::StringBuffer  buffer;
    //rapidjson::Writer<rapidjson::StringBuffer>  writer(buffer);
    //ptr_doc->Accept(writer);
    //auto msgToString = buffer.GetString();
    //printf("info:%s", msgToString);

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

    rapidjson::Document* ptr_doc = new rapidjson::Document();
    ptr_doc->Parse("{}");
    rapidjson::Document::AllocatorType& allocator = ptr_doc->GetAllocator();


    rapidjson::Value vType(rapidjson::kObjectType);
    rapidjson::Value vData(rapidjson::kObjectType);
    ptr_doc->AddMember("type", 11028, allocator);//对象添加
    ptr_doc->AddMember("data", vData, allocator);
    (*ptr_doc)["data"].AddMember("wxid", "wxid_xxxxxxx", allocator);//data对象添加
    (*ptr_doc)["data"].AddMember("nickname", "中文", allocator);//data对象添加
    (*ptr_doc)["data"].AddMember("avatar", "http://xxxxxxx", allocator);//data对象添加


    rapidjson::StringBuffer  buffer;
    rapidjson::Writer<rapidjson::StringBuffer>  writer(buffer);
    ptr_doc->Accept(writer);
    auto msgToString = buffer.GetString();


    if (typeid(msgToString) == typeid(const char*)) {
        cout << "str1的类型是：const char*" << endl;
    }
    if (typeid(msgToString) == typeid(wchar_t*)) {
        cout << "str2的类型是:wchar_t" << endl;
    }
    if (typeid(msgToString) == typeid(const wchar_t*)) {
        cout << "str2的类型是:wchar_t" << endl;
    }
    if (typeid(msgToString) == typeid(string)) {
        cout << "str2的类型是:string" << endl;
    }

    printf("info:%s", msgToString);


    //doc.AddMember("type", 11028, allocator);
    //doc.AddMember("data", "{}", allocator);

    //(*doc)["data"].AddMember("user", "wx_id1222", allocator);
    //doc["data"].AddMember("wxid", "wx_id1222", allocator);

    //doc["data"].AddMember("avatar", "wx_id1222", allocator);

    //Value vData(kArrayType);


    ////构建userinfo数据
    ////Value vUserInfo(kObjectType);

    ////wxid
    //char wxid[50] = { 0 };
    //sprintf(wxid, "wx_id1222");
    //Value vWxid(wxid, doc.GetAllocator());
    //vData.AddMember("wxid", vWxid, allocator);

    ////nickname
    //wchar_t nickname[100] = { 0 };
    //sprintf(wxid, "wx_id1222");
    //Value vNickName(UnicodeToUtf8(nickname), doc.GetAllocator());
    //vData.AddMember("nickname", vNickName, allocator);
    //
    ////avatar
    //char avatar[100] = { 0 };
    //sprintf(avatar, "http://124.com");
    //Value vAvatar(avatar, doc.GetAllocator());
    //vData.AddMember("avatar", vAvatar, allocator);


    ////vData.PushBack(vUserInfo, allocator);
    //doc.AddMember("data", vData, allocator);


    //StringBuffer sb;
    //PrettyWriter<StringBuffer> writer(sb);
    //doc.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
    //std::cout << sb.GetString() << std::endl;

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


wchar_t* StrToWchar(std::string str)
{
    int strSize = (int)(str.length() + 1);
    wchar_t* wStr = new wchar_t[strSize];
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wStr, strSize);
    return wStr;
    delete[] wStr;
}


void jiexiJson() {

    char buffer[100] = "{\"data\": {\"to_wxid\": \"wxid_4j4mqsuzdgie22\",\"content\": \"中文\" },\"type\": 1}";

    Document doc;
    doc.SetObject();
    Document::AllocatorType& allocator = doc.GetAllocator(); //获取分配器

    if (doc.ParseInsitu(buffer).HasParseError()) {
        printf("ParseInsitu is error...\n");
        return;
    }

    int nType = doc["type"].GetInt();

    string toWxid = doc["data"]["to_wxid"].GetString();
    // wToWxid 和 wToWxid2一样
    wchar_t* wToWxid = UTF8ToUnicode(doc["data"]["to_wxid"].GetString());
    wchar_t* wToWxid2 = StrToWchar(doc["data"]["to_wxid"].GetString());


    string content = doc["data"]["content"].GetString();
    const char* cContent = {0};
    cContent = content.c_str();

    wchar_t* wContent = StrToWchar(doc["data"]["content"].GetString());




    getchar();
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



