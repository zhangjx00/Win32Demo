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


//rapidjson::Document document;

void func();
void fun2();
void fun4();
void jiexiJson();

int main()
{
    //func();
    //func();
    //pointFun();
    //jiexiJson();
    fun4();

    system("pause");// 暂停以显示终端窗口
}


void func()
{

    Document doc;
    doc.SetObject();
    Document::AllocatorType& allocator = doc.GetAllocator(); //获取分配器
    //1.添加字符串对象
    doc.AddMember("author", "tashaxing", allocator);
    //2.添加数组对象

    char memberList[] = "wxid_wir3w987pznk12^Gdaziran2012^Gwxid_uhdq7a2lzfft22^Gwxid_wwdaid0qockd22^Gwxid_1640216401612^Gwxid_zu2xun17g2un22^Gwxid_ltgi1v495ibm22^Gwxid_zknn0vhxjacc21^Gwxid_pxe6avbmt3v922^Gwxid_zf4m5wy6q0il22^Gwxid_5354823546114^Gwxid_tsryluo049cf22^Gli_huadong^Gwxid_3721687216112^Gwxid_zoecdrver59u22^Gwxid_mcg671o58af312^Gmu124578^Gwss199081^Gjiahe784331^Gteewsteews^Gwxid_u8x86w4jiwpp22^GJackliu2011^Gwxid_l9ie4ema9gu611^Gxiaomingagou^Gwxid_r1lr07cnq2cs22^Gwxid_sg7nxczfu5kt22^Gzhangzhongliang8008^Gwxid_l59x38zkfkmo22^Gwxid_4j4mqsuzdgie22^Gwinty2010^Glonghun0991^Gwxid_p9e216xcqfpw21^Gwxid_thatd8wsjdbf31^Gzmcmsl^Gshangjixin^Gwxid_8262k5d5h80k22^Gwxid_4sy2barbyny712^Gxiaowang360230^Gwxid_2t7fw46c94vc22^Gbeijingfang2011";
    const char flag[3] = "^G";
    char* wxidItem;

    /* 获取第一个子字符串 */
    wxidItem = strtok(memberList, flag);

    /* 继续获取其他的子字符串 */
    Value array1(kArrayType);
    while (wxidItem != NULL) {

        Value string_object(kObjectType);
        size_t nSize = strlen(wxidItem);
        string_object.SetString(wxidItem, nSize, doc.GetAllocator());
        array1.PushBack(string_object, allocator);
        wxidItem = strtok(NULL, flag);
    }


    doc.AddMember("number", array1, allocator);



    ////3.添加复合对象
    //Value object(kObjectType);
    //object.AddMember("language1", "C++", allocator);
    //object.AddMember("language2", "java", allocator);
    //doc.AddMember("language", object, allocator);
    ////4.添加对象数组和复合对象的组合
    //Value array2(kArrayType);
    //Value object1(kObjectType);
    //object1.AddMember("hobby", "drawing", allocator);
    //array2.PushBack(object1, allocator);
    //Value object2(kObjectType);
    //object2.AddMember("height", 1.71, allocator);
    //array2.PushBack(object2, allocator);
    //doc.AddMember("information", array2, allocator);


    StringBuffer buffer;
    PrettyWriter<StringBuffer> pretty_writer(buffer);  //PrettyWriter是格式化的json，如果是Writer则是换行空格压缩后的json
    doc.Accept(pretty_writer);
    //打印到屏幕
    cout << "the json output:" << endl;
    cout << buffer.GetString() << endl;

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

        rapidjson::Document doc;
        doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("type", 11028, allocator);
    doc.AddMember("data", "{}", allocator);

    doc["data"].AddMember("user", "wx_id1222", allocator);
    doc["data"].AddMember("wxid", "wx_id1222", allocator);

    doc["data"].AddMember("avatar", "wx_id1222", allocator);

    Value vData(kArrayType);


    //构建userinfo数据
    //Value vUserInfo(kObjectType);

    //wxid
    char wxid[50] = { 0 };
    sprintf(wxid, "wx_id1222");
    Value vWxid(wxid, doc.GetAllocator());
    vData.AddMember("wxid", vWxid, allocator);

    //nickname
    wchar_t nickname[100] = { 0 };
    sprintf(wxid, "wx_id1222");
    Value vNickName(UnicodeToUtf8(nickname), doc.GetAllocator());
    vData.AddMember("nickname", vNickName, allocator);
    
    //avatar
    char avatar[100] = { 0 };
    sprintf(avatar, "http://124.com");
    Value vAvatar(avatar, doc.GetAllocator());
    vData.AddMember("avatar", vAvatar, allocator);


    //vData.PushBack(vUserInfo, allocator);
    doc.AddMember("data", vData, allocator);


    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    doc.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
    std::cout << sb.GetString() << std::endl;

}



//解析数组
void fun4()
{

    char lpSendMsgText[150] = "{\"data\": {\"to_wxid\": \"wxid_4j4mqsuzdgie22\",\"content\": \"@张zhangjx 111111111\", \"at_list\": [\"wxid_4j4mqsuzdgie22\"] },\"type\": 11036}";
    
    //RapidJson
    Document doc;
    doc.SetObject();
    Document::AllocatorType& allocator = doc.GetAllocator(); //获取分配器

    if (doc.ParseInsitu(lpSendMsgText).HasParseError()) {
        OutputDebugString(TEXT("ParseInsitu is error...\n"));
    }

    //解析type
    
    Value& infoArray = doc["data"]["at_list"];
    if (infoArray.IsArray()) {
        for (int i = 0; i < infoArray.Size(); i++) {
            const Value& object = infoArray[i];
            string lots = object.GetString();

            string aa = lots;
        }
        
    }


    doc["data"]["at_list"].GetArray();

    int nType = doc["type"].GetInt();

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



