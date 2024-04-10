#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QWidget>
#include <cstdio>
#include "openedfile.h"
#include <QTabWidget>

class FileHandler
{
    public:

        FileHandler();

        int open(QWidget *parent, OpenedFile *file, QTabWidget *tabWidget);
        int close(int index);
        void save(int index);
        std::string getFileName();
        bool isFileChanged(int index);

    private:

        std::vector<OpenedFile*> files_vector;

};

#endif // FILEHANDLER_H
