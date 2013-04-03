#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <stdio.h>
#include <string>

#include <lua5.2/lua.hpp>
using namespace std;
class Config {
    public:
        ~Config();
        static class Config* instance();
        void readconfig(string file);
        string db_host;
        string db_username;
        string db_password;
        string db_database;
        string server_ip;
        int server_port;
        int school_id;
        int game_count;
    private:
        Config();
        static class Config* p_;
};
#define CONFIG Config::instance()
#endif
