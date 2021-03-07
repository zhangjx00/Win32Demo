// 03-MongooseServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include "mongoose.h"
#include "string"
#include <list>
#include<thread>

using namespace std;

static sig_atomic_t s_signal_received = 0;
static const char* s_http_port = "10080";
static struct mg_serve_http_opts s_http_server_opts;

//struct mg_connection* g_nc;
//struct mg_str g_d;

static void signal_handler(int sig_num) {
	signal(sig_num, signal_handler);  // Reinstantiate signal handler
	s_signal_received = sig_num;
}

static int is_websocket(const struct mg_connection* nc) {
	return nc->flags & MG_F_IS_WEBSOCKET;
}


/*
 * 真正处理websocket的业务
 */
static void broadcast(struct mg_connection* nc, const struct mg_str msg) {

	printf("msg: %s", msg);
}

static void ev_handler(struct mg_connection* nc, int ev, void* ev_data) {
	switch (ev) {
	case MG_EV_WEBSOCKET_HANDSHAKE_DONE: {
		/*
		 * New websocket connection.
		 * 当clint连接到server之后，hook消息接收，消息发送到client
		 */
		//g_nc = nc;
		printf("MG_EV_WEBSOCKET_HANDSHAKE_DONE\n");
		mg_send_websocket_frame(nc, WEBSOCKET_OP_TEXT, "{\"from server HANDSHAKE\"}", 0x20);
		break;
	}
	case MG_EV_WEBSOCKET_FRAME: {
		struct websocket_message* wm = (struct websocket_message*)ev_data;
		//struct mg_str d = { (char*)wm->data, wm->size };
		//struct websocket_message* wm = (struct websocket_message*)ev_data;
		printf("%.*s\n", (int)wm->size, wm->data);

		//处理收到的消息
		//broadcast(nc, d);

		//printf("this is server, send FRAME\n");
		mg_send_websocket_frame(nc, WEBSOCKET_OP_TEXT, "{\"from server FRAME\"}", 0x20);

		Sleep(2000);
		break;
	}
	case MG_EV_HTTP_REQUEST: {
		mg_serve_http(nc, (struct http_message*)ev_data, s_http_server_opts);
		break;
	}
	case MG_EV_CLOSE: {
		/* Disconnect. Tell everybody. */
		if (is_websocket(nc)) {
			//broadcast(nc, mg_mk_str("-- left"));
		}
		break;
	}
	}
}


int main()
{
	struct mg_mgr mgr;
	struct mg_connection* nc;

	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);
	//setvbuf(stdout, NULL, _IOLBF, 0);
	//setvbuf(stderr, NULL, _IOLBF, 0);

	mg_mgr_init(&mgr, NULL);

	nc = mg_bind(&mgr, s_http_port, ev_handler);
	mg_set_protocol_http_websocket(nc);
	s_http_server_opts.document_root = ".";  // Serve current directory
	s_http_server_opts.enable_directory_listing = "yes";

	printf("Started on port %s\n", s_http_port);
	while (s_signal_received == 0) {
		mg_mgr_poll(&mgr, 200);
	}
	mg_mgr_free(&mgr);

}

