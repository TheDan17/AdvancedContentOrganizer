#ifndef PROGRAM_H
#define PROGRAM_H

#include "mvc/model.h"
#include "mvc/view.h"
#include "mvc/controller.h"

#include "../utils/resulthandler.h"

class Program {
private:
    Model* model = nullptr;
    View* view = nullptr;
    Controller* controller = nullptr;
public:
    Program();
    int exec(int argc, char** argv);
    Result<> init();
    Result<int> start();
};

#endif // PROGRAM_H
