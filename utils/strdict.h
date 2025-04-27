#ifndef STRDICT_H
#define STRDICT_H

#include <string>

class StrDict {
public:
    class Info {
    public:
        static std::string CompanyName;
        static std::string AppName;
        static std::string AppVersion;
    };
    class Log {
    public:
        class Init {
        public:
            static std::string ProgramBeginLog;
            static std::string ProgramEndLog;
            static std::string InitCorrupted;
            static std::string LoggerClassCreated;
            static std::string LoggerClassInitSucceed;
            static std::string DBRelClassNotInit;
            static std::string DBRelClassInitSucceed;
            static std::string ConnectManagerNotInit;
            static std::string ConnectManagerInitSucceed;
            static std::string GlobalClassNotInit;
            static std::string GlobalClassInit;
            static std::string UIFilesLoaded;
            static std::string UIFilesLoadErr;
            static std::string MainWindowInited;
            static std::string MainWindowCrushed;
            static std::string QApplicationInited;
            static std::string QApplicationGetError;
            static std::string MVCNotInited;
            static std::string MVCInited;
        };
    };
    class Error {
    public:
        static std::string ResultNotValue;
        static std::string ResultNotError;
    };
    class UIMsg {
        class Init {
        public:
            static std::string teststr;
        };
    };
};

using str = StrDict;
using globalstr = StrDict;

#endif // STRDICT_H
