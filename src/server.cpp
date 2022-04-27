#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#include "server.hpp"
#include "logging.h"
#include "third-party/inih/ini.h"

//for logger
FILE *_log_stream;

//forward decls
static int confhandler(void *user, const char *sec, const char *name,
        const char *value);

Server::Server()
{
    LOG_INIT_FILENAME("server.log");
    m_conf = new ServerConf;
}

Server::~Server()
{
    LOG_CLOSE();
    delete m_conf;
}
int Server::start()
{
    load_config();
    LOG_INFO("Port is %s", m_conf->port); 
    return 0;
}

void  Server::load_config()
{
    if (ini_parse("conf.ini", confhandler, m_conf) < 0) {
        LOG_ERROR("Error loading config file");
    }

}


/* config handler */
static int confhandler(void *user, const char *sec, const char *name,
        const char *value)
{
    ServerConf *conf = (ServerConf*) user;

#define MATCH(s, n) \
    (strcmp(sec, s) == 0 && strcmp(name, n) == 0)

    if (MATCH("network", "port")) {
        conf->port = value;
    } else {
        return 0;
    }

    return 1;

}

