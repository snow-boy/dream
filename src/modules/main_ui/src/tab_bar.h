#ifndef TAB_BAR_H
#define TAB_BAR_H

#include <QWidget>
#include "tab.h"

class TabBar : public QWidget
{
    Q_OBJECT
public:
    explicit TabBar(QWidget *parent = nullptr);

    void setTabSize(const QSize &size);

    int addTab(const QPixmap &pixmap, const QString &text);

    void setText(int index, const QString &text);

    void removeTab(int index);

    int count();

    void setCurrentIndex(int index);

    int currentIndex();

    virtual bool eventFilter(QObject *obj, QEvent *e) override;

signals:
    void currentChanged(int index);

public slots:

private:
    void initUi();

    QVector<Tab *> tabs_;
    QSize tab_size_;
    int current_index_;
};

#endif // TAB_BAR_H
