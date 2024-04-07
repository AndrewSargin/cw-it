#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QWidget>
#include <cstdio>
#include "openedfile.h"

class FileHandler
{
    public:

        FileHandler();

        int open(QWidget *parent, OpenedFile *file);
        int close(int index);
        void save(int index);
        std::string getFileName();

    private:

        std::vector<OpenedFile*> files_vector;

};

#endif // FILEHANDLER_H
