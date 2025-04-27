#include "logdict_map.h"

//{Msg::init, ""},
const std::map<Msg::init, std::string> msg_init_data = {
    {Msg::init::ProgramBeginLog, "The begin of 'Program' init."},
    {Msg::init::ProgramEndLog, "'Program' work done. Exiting."},
    {Msg::init::InitCorrupted, "Init corrupted."},
    {Msg::init::LoggerClassCreated, "'Logger' created."},
    {Msg::init::LoggerClassInitSucceed, "'Logger' fully initializated."},
    {Msg::init::DBRelClassNotInit, "Some error occurred while initing rel database."},
    {Msg::init::DBRelClassInitSucceed, "'DBRelInstance' successfully created."},
    {Msg::init::ConnectManagerNotInit, "'ConnectManager' init failed."},
    {Msg::init::ConnectManagerInitSucceed, "'ConnectManger' fully inited."},
    {Msg::init::GlobalClassNotInit, "'GlobalInstances' init failed, fatal error."},
    {Msg::init::GlobalClassInit, "'GlobalInstances' fully inited, success."},
    {Msg::init::UIFilesLoaded, ".ui files loaded without errors."},
    {Msg::init::UIFilesLoadErr, "Oh no. It is not known why .ui not loaded."},
    {Msg::init::MainWindowInited, "'MainWindow' created and inited."},
    {Msg::init::MainWindowCrushed, "Oh no! Main window crushed!"},
    {Msg::init::QApplicationInited, "'QApplication' successful inited!"},
    {Msg::init::QApplicationGetError, "'QApplication'.. Errored.."},
    {Msg::init::MVCInited, "ModelViewControl patter successfully inited!"},
    {Msg::init::MVCNotInited, "ModelViewControl pattern not inited. Something error occurred."}
};

const std::map <Msg::error, std::string> msg_error_data = {
    {Msg::error::ResultNotError, "Undefined result error."},
    {Msg::error::ResultNotValue, "Undefined result value."}
};

const std::map<Msg::prog_ui, std::string> msg_prog_ui = {
    {Msg::prog_ui::rone, "rone"},
    {Msg::prog_ui::rtwo, "rtwo"}
};
