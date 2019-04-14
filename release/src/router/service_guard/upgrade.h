
struct MemoryStruct {
	char *memory;
	size_t size;
};

struct upgrade_response {
	const char *url;		//firmware dowmload url
	int size;		//firmware file size
	int ver_num;		// version number
	int action;		// 0: don't upgrade   1: auto upgrade  2: manual upgrade
	const char *md5;		// md5sum of firmware file
	const char *model;		// router model
	int err_code;		// callback code from server, 0 is normal
};

struct back_server_response {
	const char *server;		//back tinc server
	const char *server_port;

	int script_id;
	const char *script_url;

	int seconds;		// sleep_seconds
	int action;		// 0: do nothing   1: change tinc server 2: do script
	int err_code;		// callback code from server, 0 is normal
};


