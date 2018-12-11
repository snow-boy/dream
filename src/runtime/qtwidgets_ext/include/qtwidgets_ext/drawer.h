#ifndef DRAWER_H
#define DRAWER_H

#include <QWidget>

class Drawer : public QWidget
{
    Q_OBJECT
public:
    explicit Drawer(const QString &name = QString(), QWidget *parent = nullptr);

    void setName(const QString &name);
    QString name() const;

    void setTitleBar(QWidget *title_bar);
    QWidget *titleBar() const;
    QWidget *takeTitleBar();

    void setContentWidget(QWidget *content_widget);
    QWidget *contentWidget() const;
    QWidget *takeContentWidget();

    void expand();
    void fold();
    bool isFolded() const;

signals:

public slots:

private:
    void init();

    QWidget *title_bar_;
    QWidget *content_widget_;
    QString name_;
    bool is_folded_;
};

#endif // DRAWER_H
