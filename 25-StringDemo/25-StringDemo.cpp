// 25-StringDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "io_utils.h"
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <tchar.h>

int main() {

    char str[] = "wxid_wir3w987pznk12^Gdaziran2012^Gwxid_uhdq7a2lzfft22^Gwxid_wwdaid0qockd22^Gwxid_1640216401612^Gwxid_zu2xun17g2un22^Gwxid_ltgi1v495ibm22^Gwxid_zknn0vhxjacc21^Gwxid_pxe6avbmt3v922^Gwxid_zf4m5wy6q0il22^Gwxid_5354823546114^Gwxid_tsryluo049cf22^Gli_huadong^Gwxid_3721687216112^Gwxid_zoecdrver59u22^Gwxid_mcg671o58af312^Gmu124578^Gwss199081^Gjiahe784331^Gteewsteews^Gwxid_u8x86w4jiwpp22^GJackliu2011^Gwxid_l9ie4ema9gu611^Gxiaomingagou^Gwxid_r1lr07cnq2cs22^Gwxid_sg7nxczfu5kt22^Gzhangzhongliang8008^Gwxid_l59x38zkfkmo22^Gwxid_4j4mqsuzdgie22^Gwinty2010^Glonghun0991^Gwxid_p9e216xcqfpw21^Gwxid_thatd8wsjdbf31^Gzmcmsl^Gshangjixin^Gwxid_8262k5d5h80k22^Gwxid_4sy2barbyny712^Gxiaowang360230^Gwxid_2t7fw46c94vc22^Gbeijingfang2011";
    const char s[3] = "^G";
    char* token;

    /* 获取第一个子字符串 */
    token = strtok(str, s);

    /* 继续获取其他的子字符串 */
    while (token != NULL) {
        printf("%s\n", token);

        token = strtok(NULL, s);
    }

    return 0;
}
