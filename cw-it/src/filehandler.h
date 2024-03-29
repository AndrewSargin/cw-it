#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QWidget>
#include <cstdio>
#include "filestructure.h"

class FileHandler
{
    public:

        FileHandler();

        int open(QWidget *parent, struct openedFile *);
        int close(struct openedFile *);
        void save();
        std::string getFileName();

    private:

        std::vector<openedFile*> files_vector;

        std::vector<std::string> SeparateLine(std::string line, std::string delimiter);

};

#endif // FILEHANDLER_H
