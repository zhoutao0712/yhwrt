
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>
#include <stdint.h>
#include <syslog.h>
#include <ctype.h>

#include <bcmnvram.h>
#include <shutils.h>

#include <shared.h>

#include "ping.h"

static void killall_tk(const char *name)
{
	int n;

	if (killall(name, SIGTERM) == 0) {
		n = 10;
		while ((killall(name, 0) == 0) && (n-- > 0)) {
//			_dprintf("%s: waiting name=%s n=%d\n", __FUNCTION__, name, n);
			usleep(100 * 1000);
		}
		if (n < 0) {
			n = 10;
			while ((killall(name, SIGKILL) == 0) && (n-- > 0)) {
//				_dprintf("%s: SIGKILL name=%s n=%d\n", __FUNCTION__, name, n);
				usleep(100 * 1000);
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int ret;
	signal(SIGPIPE, SIG_IGN);
	signal(SIGALRM, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGCHLD, chld_reap);

//printf("%d\n", argc);

	if(argc == 1) {
		if (daemon(1, 1) == -1) {
			syslog(LOG_ERR, "daemon: %m");
			return 0;
		}
	}

	sleep(10);

	while (1) {
		sleep(3);
		if(argc ==1) {
			ret = do_ping("172.16.0.1", 8);
		} else {
			ret = do_ping(argv[1], 8);
		}

		if(ret != 0) {
			if(check_if_file_exist("/etc/tinc/gfw/tinc.conf")) {
				killall_tk("tincd");
				eval("tinc", "-n", "gfw", "restart");
			} else {
				eval("service", "restart_tinc");
			}

			sleep(20);
		}
	}

	return 0;
}

