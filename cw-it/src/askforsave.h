#ifndef ASKFORSAVE_H
#define ASKFORSAVE_H

#include <QDialog>
#include "filehandler.h"

namespace Ui {
class AskForSave;
}

class AskForSave : public QDialog
{
    Q_OBJECT

public:
    explicit AskForSave(QWidget *parent = nullptr, FileHandler *fileHandler = nullptr, int index = 0);

    ~AskForSave();

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AskForSave *ui;
    FileHandler *fileHandler;
    int index;
};

#endif // ASKFORSAVE_H
