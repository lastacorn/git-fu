#ifndef GITFU_H
#define GITFU_H

#include <QtGui/QMainWindow>
#include "ui_gitfu.h"

class GitFu : public QMainWindow
{
    Q_OBJECT

public:
    GitFu(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~GitFu();

private:
    Ui::GitFuClass ui;
};

#endif // GITFU_H
