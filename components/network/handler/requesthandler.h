#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <QObject>

#include "basehandler.h"
#include "../items/request.h"
#include "../items/networkdata.h"

class RequestHandler : public QObject, public BaseHandler<Request> {
    Q_OBJECT
public:
    RequestHandler();
    Result<> process_elem(Request elem);
signals:
    void need_process_request(NetworkData request);
public slots:
    void request_processed();
};

#endif // REQUESTHANDLER_H
