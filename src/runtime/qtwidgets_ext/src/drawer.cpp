#include "drawer.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

Drawer::Drawer(const QString &name, QWidget *parent) :
    QWidget(parent),
    title_bar_(nullptr),
    content_widget_(nullptr),
    name_(name),
    is_folded_(false)
{
    init();
}

void Drawer::init()
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout(layout);

    QPushButton *button = new QPushButton(name_);
    connect(button, &QPushButton::clicked, this, [=](bool){
        if(is_folded_){
            expand();
        }
        else{
            fold();
        }
    });

    title_bar_ = button;
    title_bar_->setMinimumHeight(25);
    title_bar_->setMaximumHeight(25);
    layout->addWidget(title_bar_);
}

void Drawer::setName(const QString &name)
{
    name_ = name;

    QPushButton *button = qobject_cast<QPushButton *>(title_bar_);
    if(button != nullptr){
        button->setText(name_);
    }
}

QString Drawer::name() const
{
    return name_;
}

void Drawer::setTitleBar(QWidget *title_bar)
{
    if(title_bar_ != nullptr){
        delete title_bar_;
        title_bar_ = nullptr;
    }

    title_bar_ = title_bar;
    QVBoxLayout *v_layout = static_cast<QVBoxLayout *>(layout());
    v_layout->insertWidget(0, title_bar_);
}

QWidget *Drawer::titleBar() const
{
    return title_bar_;
}

QWidget *Drawer::takeTitleBar()
{
    QWidget *current_title_bar = title_bar_;
    title_bar_ = nullptr;
    return current_title_bar;
}

void Drawer::setContentWidget(QWidget *content_widget)
{
    if(content_widget_ != nullptr){
        delete content_widget_;
        content_widget_ = nullptr;
    }

    content_widget_ = content_widget;
    QVBoxLayout *v_layout = static_cast<QVBoxLayout *>(layout());
    v_layout->addWidget(content_widget_);
}

QWidget *Drawer::contentWidget() const
{
    return content_widget_;
}

QWidget *Drawer::takeContentWidget()
{
    QWidget *current_content_widget = content_widget_;
    content_widget_ = nullptr;
    return current_content_widget;
}

void Drawer::expand()
{
    is_folded_ = false;
    if(content_widget_ != nullptr){
        content_widget_->show();
    }
}

void Drawer::fold()
{
    is_folded_ = true;
    if(content_widget_ != nullptr){
        content_widget_->hide();
    }
}

bool Drawer::isFolded() const
{
    return is_folded_;
}
