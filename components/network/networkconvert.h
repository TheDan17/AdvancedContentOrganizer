#ifndef NETWORKCONVERT_H
#define NETWORKCONVERT_H

#include "items/networkdata.h"
#include "items/request.h"
#include "items/response.h"

class NetworkConvert {
public:
    static Response* toResponse(NetworkData value);
    static NetworkData fromResponse(Response* value);
    static Request* toRequest(NetworkData value);
    static NetworkData fromRequest(Request* value);
};

#endif // NETWORKCONVERT_H
