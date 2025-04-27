#include <string>
#include <chrono>

#include "../../utils/resulthandler.h"

#ifndef CONNECTION_H
#define CONNECTION_H

class InfoConnection; class DataConnection;
class FileConnection; class StreamConnection;

class Connection {
private:
    bool is_to_host;
    std::string password;

    std::string ip;
    short port;

    int buffer_size;
    std::chrono::seconds timeout = std::chrono::seconds(10);

public:
    InfoConnection* info;
    DataConnection* data;
    FileConnection* file;
    StreamConnection* stream;

    Connection(std::string ip, int port, bool is_to_server);
    void set_buffer_size(int bytes);
    void set_timeout(std::chrono::seconds seconds);
    bool is_from_client();
};


class InfoConnection {
private:
    Connection* connection;
public:
    InfoConnection(Connection* connection);
    Result<> check_connection();
};

class DataConnection {
private:
    Connection* connection;
public:
    DataConnection(Connection* connection);
};

class FileConnection {
private:
    Connection* connection;
public:
    FileConnection(Connection* connection);
};

class StreamConnection {
private:
    Connection* connection;
public:
    StreamConnection(Connection* connection);
};

#endif // CONNECTION_H
