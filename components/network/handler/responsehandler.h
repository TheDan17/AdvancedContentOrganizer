#ifndef RESPONSEHANDLER_H
#define RESPONSEHANDLER_H

#include <QObject>

#include "basehandler.h"
#include "../items/response.h"
#include "../items/networkdata.h"

class ResponseHandler : public QObject, public BaseHandler<Response>{
    Q_OBJECT
public:
    ResponseHandler();
    Result<> process_elem(Response elem);
    void add_response(NetworkData response);
    void add_response(Response response);
};

#endif // RESPONSEHANDLER_H
