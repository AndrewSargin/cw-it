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

private:

    Ui::TabPage *ui;
    OpenedFile file;

};

#endif // TABPAGE_H
