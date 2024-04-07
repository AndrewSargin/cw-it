#ifndef TABPAGE_H
#define TABPAGE_H

#include <QWidget>
#include <openedfile.h>

namespace Ui {
class TabPage;
}

class TabPage : public QWidget
{
    Q_OBJECT

public:
    explicit TabPage(QWidget *parent = nullptr, OpenedFile *file = nullptr);
    ~TabPage();

private slots:
    void on_tableWidget_cellChanged(int row, int column);

private:

    Ui::TabPage *ui;
    OpenedFile *currentFile;

};

#endif // TABPAGE_H
