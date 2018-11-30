#include "tab_bar.h"
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>

TabBar::TabBar(QWidget *parent) :
    QWidget(parent),
    current_index_(-1)
{
    initUi();
}

void TabBar::initUi()
{
    QHBoxLayout *h_layout = new QHBoxLayout;
    h_layout->setMargin(0);
    h_layout->setSpacing(0);
    setLayout(h_layout);
}

void TabBar::setTabSize(const QSize &size)
{
    tab_size_ = size;
}

int TabBar::addTab(const QPixmap &pixmap, const QString &text)
{
    Tab *tab = new Tab(this);
    tab->setMinimumSize(tab_size_);
    tab->setMaximumSize(tab_size_);
    if(!pixmap.isNull()){
        tab->setPixmap(pixmap);
    }
    tab->setText(text);
    layout()->addWidget(tab);

    tab->installEventFilter(this);
    tab->setStyleSheet("background: white;"
                       "border: 1px solid gray;"
                       "padding:2px;");

    int index = tabs_.size();
    tabs_.append(tab);

    if(tabs_.size() == 1){
        setCurrentIndex(0);
    }

    return index;
}

void TabBar::setText(int index, const QString &text)
{
    Q_ASSERT(index < tabs_.size());
    tabs_[index]->setText(text);
}

void TabBar::removeTab(int index)
{
    Q_ASSERT(index < tabs_.size());

    delete tabs_[index];
    tabs_.removeAt(index);

    if(current_index_ == index){
        if(tabs_.size() > 0){
            setCurrentIndex(0);
        }
        else{
            setCurrentIndex(-1);
        }
    }
}

int TabBar::count()
{
    return tabs_.size();
}

void TabBar::setCurrentIndex(int index)
{
    Q_ASSERT(index < tabs_.size());

    if(current_index_ == index){
        return;
    }

    if(tabs_.size() == 0){
        emit currentChanged(-1);
        return;
    }

    if(current_index_ >= 0){
        tabs_[current_index_]->setStyleSheet("background: white;"
                                             "border: 1px solid gray;");
    }

    if(index >= 0){
        tabs_[index]->setStyleSheet("background: #d0dbfa;"
                                    "border: 1px solid #7c98cf;");
    }

    current_index_ = index;
    emit currentChanged(current_index_);
}

int TabBar::currentIndex()
{
    return current_index_;
}

bool TabBar::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouse_event = static_cast<QMouseEvent *>(e);
        if(mouse_event->button() == Qt::LeftButton){
            Tab *tab = static_cast<Tab*>(obj);
            setCurrentIndex(tabs_.indexOf(tab));
        }
    }

    return QWidget::eventFilter(obj, e);
}
