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

    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

    void on_addAfter_triggered();

    void on_addBefore_triggered();

    void on_deleteEntry_triggered();

    void NewRow(int row);

    void on_lineEdit_textChanged(const QString &arg1);

private:

    Ui::TabPage *ui;
    OpenedFile *currentFile;

};

#endif // TABPAGE_H
