// 05-CharacterSet.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include "string"
#include <vector>


using namespace std;

string WcharToString(WCHAR* wchar)
{
    WCHAR* wText = wchar;
    // WideCharToMultiByte的运用
    DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);
    // psText为char*的临时数组，作为赋值给std::string的中间变量
    char* psText = new char[dwNum];
    // WideCharToMultiByte的再次运用
    WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);
    // std::string赋值
    return psText;
}

// 获取转换为UTF-16 LE编码的字符串
std::u16string utf8_to_utf16le(const std::string& u8str, bool addbom, bool* ok)
{
	std::u16string u16str;
	u16str.reserve(u8str.size());
	if (addbom) {
		u16str.push_back(0xFEFF);	//bom (字节表示为 FF FE)
	}
	std::string::size_type len = u8str.length();

	const unsigned char* p = (unsigned char*)(u8str.data());
	// 判断是否具有BOM(判断长度小于3字节的情况)
	if (len > 3 && p[0] == 0xEF && p[1] == 0xBB && p[2] == 0xBF) {
		p += 3;
		len -= 3;
	}

	bool is_ok = true;
	// 开始转换
	for (std::string::size_type i = 0; i < len; ++i) {
		uint32_t ch = p[i];	// 取出UTF8序列首字节
		if ((ch & 0x80) == 0) {
			// 最高位为0，只有1字节表示UNICODE代码点
			u16str.push_back((char16_t)ch);
			continue;
		}
		switch (ch & 0xF0)
		{
		case 0xF0: // 4 字节字符, 0x10000 到 0x10FFFF
		{
			uint32_t c2 = p[++i];
			uint32_t c3 = p[++i];
			uint32_t c4 = p[++i];
			// 计算UNICODE代码点值(第一个字节取低3bit，其余取6bit)
			uint32_t codePoint = ((ch & 0x07U) << 18) | ((c2 & 0x3FU) << 12) | ((c3 & 0x3FU) << 6) | (c4 & 0x3FU);
			if (codePoint >= 0x10000)
			{
				// 在UTF-16中 U+10000 到 U+10FFFF 用两个16bit单元表示, 代理项对.
				// 1、将代码点减去0x10000(得到长度为20bit的值)
				// 2、high 代理项 是将那20bit中的高10bit加上0xD800(110110 00 00000000)
				// 3、low  代理项 是将那20bit中的低10bit加上0xDC00(110111 00 00000000)
				codePoint -= 0x10000;
				u16str.push_back((char16_t)((codePoint >> 10) | 0xD800U));
				u16str.push_back((char16_t)((codePoint & 0x03FFU) | 0xDC00U));
			}
			else
			{
				// 在UTF-16中 U+0000 到 U+D7FF 以及 U+E000 到 U+FFFF 与Unicode代码点值相同.
				// U+D800 到 U+DFFF 是无效字符, 为了简单起见，这里假设它不存在(如果有则不编码)
				u16str.push_back((char16_t)codePoint);
			}
		}
		break;
		case 0xE0: // 3 字节字符, 0x800 到 0xFFFF
		{
			uint32_t c2 = p[++i];
			uint32_t c3 = p[++i];
			// 计算UNICODE代码点值(第一个字节取低4bit，其余取6bit)
			uint32_t codePoint = ((ch & 0x0FU) << 12) | ((c2 & 0x3FU) << 6) | (c3 & 0x3FU);
			u16str.push_back((char16_t)codePoint);
		}
		break;
		case 0xD0: // 2 字节字符, 0x80 到 0x7FF
		case 0xC0:
		{
			uint32_t c2 = p[++i];
			// 计算UNICODE代码点值(第一个字节取低5bit，其余取6bit)
			uint32_t codePoint = ((ch & 0x1FU) << 12) | ((c2 & 0x3FU) << 6);
			u16str.push_back((char16_t)codePoint);
		}
		break;
		default:	// 单字节部分(前面已经处理，所以不应该进来)
			is_ok = false;
			break;
		}
	}
	if (ok != NULL) { *ok = is_ok; }

	return u16str;
}



std::wstring ConvertFromUtf8ToUtf16(const std::string& str)
{
	std::wstring convertedString;
	int requiredSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, 0, 0);
	if (requiredSize > 0)
	{
		std::vector<wchar_t> buffer(requiredSize);
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &buffer[0], requiredSize);
		convertedString.assign(buffer.begin(), buffer.end() - 1);
	}

	return convertedString;
}


int main()
{

    char src[16] = {
        0xe5,0x8a,0xa9,0xe6 ,0x89 ,0x8b ,0x7a ,0x68 ,0x75 ,0x73,0x68 ,0x6f ,0x75,0x00
    };

    printf("%s\n", src);

	wcout.imbue(locale("chs"));

    // content是utf16进制数据存储
    char content[100] = {
        0xe5,0x8a,0xa9,0xe6 ,0x89 ,0x8b ,0x7a ,0x68 ,0x75 ,0x73,0x68 ,0x6f ,0x75,0x00
    };

	string str = content;
	wstring wstr = ConvertFromUtf8ToUtf16(str);

	wcout << wstr.c_str() << endl;




}

