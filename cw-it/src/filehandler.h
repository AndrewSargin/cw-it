#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QWidget>
#include <cstdio>
#include "openedfile.h"
#include <QTabWidget>

/// \brief Класс для управления всеми файлами, содержащий о них
/// всю необходимую информацию
class FileHandler
{
    public:

        //Конструктор
        FileHandler();

        //Создать новый файл
        void NewFile(OpenedFile *file);

        //Открыть существующий файл
        int open(QWidget *parent, OpenedFile *file, QTabWidget *tabWidget);

        //Закрыть файл
        int close(int index);

        //Сохранить файл
        void save(QWidget *parent, int index);

        //Сохранить как
        void saveAs(QWidget *parent, int index);

        //Получить название файла
        std::string getFileName();

        //Узнать, был ли файл изменен
        bool isFileChanged(int index);

        //Получить все данные из файла
        std::map<int, Entry> getFileData(int index);

    private:

        //Хранит в себе все открытые файлы в виде вектора
        std::vector<OpenedFile*> files_vector;

};

#endif // FILEHANDLER_H
