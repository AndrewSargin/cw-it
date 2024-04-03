#include "entity.h"
#include <string>

entity::entity()
{  

}

std::string entity::getId()
{
    return id;
}

std::string entity::getType()
{
    return type;
}

std::string entity::getCpu()
{
    return cpu;
}

std::string entity::getGpu()
{
    return gpu;
}

std::string entity::getRam()
{
    return ram;
}
std::string entity::getMemory()
{
    return memory;
}

std::string entity::getDate()
{
    return date;
}

std::string entity::getPrice()
{
    return price;
}

void entity::setId(std::string str)
{
    id = str;
}

void entity::setType(std::string str)
{
    type = str;
}

void entity::setCpu(std::string str)
{
    cpu = str;
}

void entity::setGpu(std::string str)
{
    gpu = str;
}

void entity::setRam(std::string str)
{
    ram = str;
}

void entity::setMemory(std::string str)
{
    memory = str;
}

void entity::setDate(std::string str)
{
    date = str;
}

void entity::setPrice(std::string str)
{
    price = str;
}
