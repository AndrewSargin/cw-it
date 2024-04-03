#ifndef ENTITY_H
#define ENTITY_H

#include <cstdio>
#include <string>

class entity
{
public:

    entity();

    std::string getId();
    std::string getType();
    std::string getCpu();
    std::string getGpu();
    std::string getRam();
    std::string getMemory();
    std::string getDate();
    std::string getPrice();

    void setId(std::string str);
    void setType(std::string str);
    void setCpu(std::string str);
    void setGpu(std::string str);
    void setRam(std::string str);
    void setMemory(std::string str);
    void setDate(std::string str);
    void setPrice(std::string str);

private:

    std::string id;
    std::string type;
    std::string cpu;
    std::string gpu;
    std::string ram;
    std::string memory;
    std::string date;
    std::string price;
};

#endif // ENTITY_H
