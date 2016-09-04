all:
	cc -o exercise1_wc exercise1_wc.c
	cc -o exercise3_ID3read exercise3_ID3read.c
	cc -o tcp_chat_server tcp_chat_server.c -pthread
	cc -o tcp_chat_client tcp_chat_client.c -pthread
	cc -o sntp_server sntp_server.c
	cc -o sntp_client sntp_client.c



