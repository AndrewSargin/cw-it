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

        void NewFile(OpenedFile *file);
        int open(QWidget *parent, OpenedFile *file, QTabWidget *tabWidget);
        int close(int index);
        void save(QWidget *parent, int index);
        void saveAs(QWidget *parent, int index);
        std::string getFileName();
        bool isFileChanged(int index);
        std::map<int, Entry> getFileData(int index);

    private:

        std::vector<OpenedFile*> files_vector;

};

#endif // FILEHANDLER_H
