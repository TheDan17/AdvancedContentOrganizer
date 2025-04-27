#include "strdict.h"

std::string StrDict::Info::CompanyName = "Danissimo";
std::string StrDict::Info::AppName = "CWLibrary";
std::string StrDict::Info::AppVersion = "v0.0";

std::string StrDict::Log::Init::ProgramBeginLog = "The begin of 'Program' init.";
std::string StrDict::Log::Init::ProgramEndLog = "'Program' work done. Exiting.";
std::string StrDict::Log::Init::InitCorrupted = "Init corrupted.";
std::string StrDict::Log::Init::LoggerClassCreated = "'Logger' created.";
std::string StrDict::Log::Init::LoggerClassInitSucceed = "'Logger' fully initializated.";
std::string StrDict::Log::Init::DBRelClassNotInit = "Some error occurred while initing rel database.";
std::string StrDict::Log::Init::DBRelClassInitSucceed = "'DBRelInstance' successfully created.";
std::string StrDict::Log::Init::ConnectManagerNotInit = "'ConnectManager' init failed.";
std::string StrDict::Log::Init::ConnectManagerInitSucceed = "'ConnectManger' fully inited.";
std::string StrDict::Log::Init::GlobalClassNotInit = "'GlobalInstances' init failed, fatal error.";
std::string StrDict::Log::Init::GlobalClassInit = "'GlobalInstances' fully inited, success.";
std::string StrDict::Log::Init::UIFilesLoaded = ".ui files loaded without errors.";
std::string StrDict::Log::Init::UIFilesLoadErr = "Oh no. It is not known why .ui not loaded.";
std::string StrDict::Log::Init::MainWindowInited = "'MainWindow' created and inited.";
std::string StrDict::Log::Init::MainWindowCrushed = "Oh no! Main window crushed!";
std::string StrDict::Log::Init::QApplicationInited = "'QApplication' successful inited!";
std::string StrDict::Log::Init::QApplicationGetError = "'QApplication'.. Errored..";
std::string StrDict::Log::Init::MVCNotInited = "ModelViewControl patter successfully inited!";
std::string StrDict::Log::Init::MVCInited = "ModelViewControl pattern not inited. Something error occurred.";

std::string StrDict::UIMsg::Init::teststr = "test string";

std::string StrDict::Error::ResultNotValue = "Undefined result value.";
std::string StrDict::Error::ResultNotError = "Undefined result error.";
