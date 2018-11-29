#include "tab.h"
#include "ui_tab.h"

Tab::Tab(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::Tab)
{
    ui->setupUi(this);

    ui->label_icon->hide();
    ui->label_text->setAlignment(Qt::AlignCenter);
}

Tab::~Tab()
{
    delete ui;
}

void Tab::setText(const QString &text)
{
    ui->label_text->setText(text);
}

void Tab::setPixmap(const QPixmap &pixmap)
{
    ui->label_text->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    ui->label_icon->show();
    ui->label_icon->setPixmap(pixmap);
}
