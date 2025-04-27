#include "program.h"

#include <string>

#include "appinit.h"
#include "globalinstances.h"
#include "mvc/controller.h"
#include "../utils/resulthandler.h"
#include "../utils/strdict.h"
#include "../components/logs/logger.h"

Program::Program() {}

int Program::exec(int argc, char** argv){
    auto app = QApplication(argc, argv);

    auto init_result = init();
    if (!init_result.is_ok())
        throw (init_result.error());

    auto exec_result = start();
    if (!exec_result.is_ok())
        throw (exec_result.error());

    return exec_result.value();
}

Result<> error_event(Logger* logger, std::string error_msg){
    logger->log_msg(ERROR, error_msg);
    logger->log_msg(INFO, StrDict::Log::Init::InitCorrupted);
    logger->log_msg(INFO, StrDict::Log::Init::ProgramEndLog);
    delete logger;
    return error(error_msg);
}
Result<> Program::init(){
    // Settings
    QCoreApplication::setOrganizationName(QString(str::Info::CompanyName.c_str()));
    QCoreApplication::setOrganizationDomain(QString(str::Info::CompanyName.c_str())+".com");
    QCoreApplication::setApplicationName(QString(str::Info::AppName.c_str()));

    // Logger
    Logger* logger = new Logger(DEBUG);
    logger->log_msg(DEBUG, StrDict::Log::Init::ProgramBeginLog+" "+
                           StrDict::Log::Init::LoggerClassCreated);

    AppInit app_init = AppInit(logger);
    auto logger_init_result = app_init.init_logger();
    if (logger_init_result.is_ok())
        global::add_one(LOGGER, logger_init_result.value());

    // GlobalInstances
    auto global_result = app_init.init_all();
    if (global_result.is_ok() != true)
        return error_event(logger, StrDict::Log::Init::GlobalClassNotInit);
    global::add_instances(global_result.value());

    // MVC
    this->model = new Model(); this->model->init_model();
    this->controller = new Controller(model);
    this->view = new View(controller);
    QObject::connect(model->host, &Host::getMessageFromClient,
                     view, &View::receivedMsg);

    auto res = model->init_model(); if (!res.is_ok()) return error_event(logger, res.error().what());
    res = view->init_ui(); if (!res.is_ok()) return error_event(logger, res.error().what());

    return value(); // success
}

Result<int> Program::start(){
    auto result = this->view->start_qloop();
    if (result.is_ok())
        global::logger()->log_msg(INFO, "Controller start() finished successfully.");
    else
        global::logger()->log_error("Controller start() finished with error: ", result.error());

    global::delete_instances();
    return result;
}
