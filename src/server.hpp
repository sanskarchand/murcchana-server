#ifndef SERVER_H
#define SERVER_H

typedef struct {
    const char *port; 
} ServerConf;

class Server
{
public:
    Server();
    ~Server();

    int start();
    void load_config();

private:
    ServerConf *m_conf;
    

};

#endif //SERVER_H
