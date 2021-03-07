// 03-MongooseClient71.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "mongoose.h"
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32.lib")


static const char* s_listen_on = "http://localhost:8000";
static const char* s_web_directory = ".";

// This RESTful server implements the following endpoints:
//   /websocket - upgrade to Websocket, and implement websocket echo server
//   /api/rest - respond with JSON string {"result": 123}
//   any other URI serves static files from s_web_directory

static void fn(struct mg_connection* c, int ev, void* ev_data, void* fn_data) {

    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message* hm = (struct mg_http_message*)ev_data;
        if (mg_http_match_uri(hm, "/websocket")) {
            // Upgrade to websocket. From now on, a connection is a full-duplex
            // Websocket connection, which will receive MG_EV_WS_MSG events.
            mg_ws_upgrade(c, hm, NULL);
        }
        else if (mg_http_match_uri(hm, "/rest")) {
            // Serve REST response
            mg_http_reply(c, 200, "", "{\"result\": %d}\n", 123);
        }
        else {
            // Serve static files
            //struct mg_http_serve_opts opts = { .root_dir = s_web_directory };
            struct mg_http_serve_opts opts;
            opts.root_dir = s_web_directory;

            mg_http_serve_dir(c, (mg_http_message*)ev_data, &opts);
        }
    }
    else if (ev == MG_EV_WS_MSG) {
        // Got websocket frame. Received data is wm->data. Echo it back!
        struct mg_ws_message* wm = (struct mg_ws_message*)ev_data;
        mg_ws_send(c, wm->data.ptr, wm->data.len, WEBSOCKET_OP_TEXT);
        mg_iobuf_delete(&c->recv, c->recv.len);
    }
    (void)fn_data;
}

int main(void) {
    struct mg_mgr mgr;                            // Event manager
    mg_mgr_init(&mgr);                            // Initialise event manager
    //mg_http_listen(&mgr, s_listen_on, fn, NULL);  // Create HTTP listener
    //for (;;) mg_mgr_poll(&mgr, 1000);             // Infinite event loop
    //mg_mgr_free(&mgr);
    return 0;
}

//int main()
//{
//    std::cout << "Hello World!\n";
//}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
