#ifndef TABPAGE_H
#define TABPAGE_H

#include <QWidget>
#include <filestructure.h>

namespace Ui {
class TabPage;
}

class TabPage : public QWidget
{
    Q_OBJECT

public:
    explicit TabPage(QWidget *parent = nullptr, openedFile *file = nullptr);
    ~TabPage();

private:

    Ui::TabPage *ui;
    openedFile *file;

};

#endif // TABPAGE_H
