#ifndef LOGDICT_ENUM_H
#define LOGDICT_ENUM_H

class Msg {
public:
    enum init {
        ProgramBeginLog,
        ProgramEndLog,
        InitCorrupted,
        LoggerClassCreated,
        LoggerClassInitSucceed,
        DBRelClassNotInit,
        DBRelClassInitSucceed,
        ConnectManagerNotInit,
        ConnectManagerInitSucceed,
        GlobalClassNotInit,
        GlobalClassInit,
        UIFilesLoaded,
        UIFilesLoadErr,
        MainWindowInited,
        MainWindowCrushed,
        QApplicationInited,
        QApplicationGetError,
        MVCNotInited,
        MVCInited
    };

    enum error {
        ResultNotValue,
        ResultNotError
    };

    enum prog_ui {
        rone,
        rtwo,
        rthree
    };
};

#endif // LOGDICT_ENUM_H
