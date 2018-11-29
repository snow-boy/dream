#ifndef _TAB_H
#define _TAB_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class Tab;
}

class Tab : public QLabel
{
    Q_OBJECT

public:
    explicit Tab(QWidget *parent = 0);
    ~Tab();

    void setText(const QString &text);

    void setPixmap(const QPixmap &pixmap);

private:
    Ui::Tab *ui;
};

#endif // _TAB_H
