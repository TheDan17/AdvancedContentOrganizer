#ifndef TABLES_H
#define TABLES_H

#include <string>

class DBTablePrototype {
private:
    std::string name;
public:
    DBTablePrototype(std::string local_name);
    std::string get_name();
};

#endif // TABLES_H
