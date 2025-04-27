cmake_minimum_required(VERSION 3.5)

project(CWLibrary VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(MySQL_LIBRARY "C:/Program Files/MySQL/MySQL Server 8.0/lib/libmysql.lib")
set(MySQL_INCLUDE_DIR "C:/Program Files/MySQL/MySQL Server 8.0/include")

find_package(QT NAMES Qt6)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Network)
find_package(MySQL REQUIRED) # MYSQL

set(FORMS
    ui/mainwindow.ui
    ui/dialogs/addserverconnectdialog.ui
    ui/dialogs/addserverlogindialog.ui
)
set(PROJECT_SOURCES
    main.cpp

    ui/mainwindow.h
    ui/mainwindow.cpp
    ui/mainwindow.ui

    ui/dialogs/addserverconnectdialog.h
    ui/dialogs/addserverconnectdialog.cpp
    ui/dialogs/addserverconnectdialog.ui

    ui/dialogs/addserverlogindialog.h
    ui/dialogs/addserverlogindialog.cpp
    ui/dialogs/addserverlogindialog.ui

    ui/dialogs/additemtoserverdialog.h
    ui/dialogs/additemtoserverdialog.cpp
    ui/dialogs/additemtoserverdialog.ui

    ui/dialogs/watchdbdialog.h
    ui/dialogs/watchdbdialog.cpp

    ui/widgets/servertreeview.h ui/widgets/servertreeview.cpp


    main/program.h main/program.cpp
    main/appinit.h main/appinit.cpp
    main/globalinstances.h main/globalinstances.cpp

    main/mvc/model.h
    main/mvc/model.cpp
    main/mvc/view.h
    main/mvc/view.cpp
    main/mvc/controller.h
    main/mvc/controller.cpp

    components/logs/logger.h components/logs/logger.cpp
    components/logs/logdata.h components/logs/logdata.cpp



    components/database/databaserel.h components/database/databaserel.cpp
    components/database/dbrelbuilder.h components/database/dbrelbuilder.cpp
    components/database/tables.h components/database/tables.cpp

    components/database/strategies/common/dbrelbuilderstrategy.h components/database/strategies/common/dbrelbuilderstrategy.cpp
    components/database/strategies/common/dbrelcontrolstrategy.h components/database/strategies/common/dbrelcontrolstrategy.cpp
    components/database/strategies/common/dbrelpack.h components/database/strategies/common/dbrelpack.cpp

    components/database/strategies/mysql/dbrelbuildermysql.h components/database/strategies/mysql/dbrelbuildermysql.cpp
    components/database/strategies/mysql/dbrelcontrolmysql.h components/database/strategies/mysql/dbrelcontrolmysql.cpp
    components/database/strategies/mysql/dbrelpackmysql.h components/database/strategies/mysql/dbrelpackmysql.cpp
    components/database/strategies/mysql/mysql.h

    components/database/dbconfig.h components/database/dbconfig.cpp


    components/network/client.h components/network/client.cpp
    components/network/host.h components/network/host.cpp
    components/network/hostlistener.h components/network/hostlistener.cpp
    components/network/networksender.h components/network/networksender.cpp
    components/network/networkconvert.h components/network/networkconvert.cpp

    components/network/handler/basehandler.h
    components/network/handler/requesthandler.h components/network/handler/requesthandler.cpp
    components/network/handler/responsehandler.h components/network/handler/responsehandler.cpp

    components/network/items/request.h components/network/items/request.cpp
    components/network/items/response.h components/network/items/response.cpp
    components/network/items/networkdata.h components/network/items/networkdata.cpp


    components/network/transfer/streamnetworktransfer.h components/network/transfer/streamnetworktransfer.cpp
    components/network/transfer/filenetworktransfer.h components/network/transfer/filenetworktransfer.cpp
    components/network/transfer/filenetworkworker.h components/network/transfer/filenetworkworker.cpp


    utils/resulthandler.h
    utils/strdict.h utils/strdict.cpp
    utils/datetimeutils.h utils/datetimeutils.cpp
    utils/networkjsoncreator.h utils/networkjsoncreator.cpp
    utils/helpers.h utils/helpers.cpp

    utils/filesystemutils.h utils/filesystemutils.cpp #???
    utils/MySQL_create_tables_query.txt # ???
)

qt6_wrap_ui(UI_HEADERS ${FORMS})
qt_add_executable(CWLibrary
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(CWLibrary PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(CWLibrary PRIVATE ${MySQL_LIBRARY}) # MYSQL
target_link_libraries(CWLibrary PRIVATE Qt6::Sql Qt6::Network)

set_target_properties(CWLibrary PROPERTIES
    WIN32_EXECUTABLE TRUE
)

include_directories(${MySQL_INCLUDE_DIR}) # MYSQL
include(GNUInstallDirs)
install(TARGETS CWLibrary
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CWLibrary)
endif()
