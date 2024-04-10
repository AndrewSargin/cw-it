#ifndef FILEREADINGERROR_H
#define FILEREADINGERROR_H

#include <QDialog>

namespace Ui {
class FileReadingError;
}

class FileReadingError : public QDialog
{
    Q_OBJECT

public:
    explicit FileReadingError(QWidget *parent = nullptr);
    ~FileReadingError();

private:
    Ui::FileReadingError *ui;
};

#endif // FILEREADINGERROR_H
