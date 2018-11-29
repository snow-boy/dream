#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>

#include <vw/entity.h>
#include <vw/cube.h>
#include <vw/cone.h>
#include <vw/grid.h>
#include <life/life.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    current_toolbox_(nullptr)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addToolboxView(IToolboxView *toolbox_view)
{
    Q_ASSERT(!toolbox_views_.contains(toolbox_view));
    toolbox_views_.push_back(toolbox_view);
    ui->widget_tab->addTab(QPixmap(), toolbox_view->name());
}

void MainWindow::removeToolboxView(IToolboxView *toolbox_view)
{
    Q_ASSERT(toolbox_views_.contains(toolbox_view));
    ui->widget_tab->removeTab(toolbox_views_.indexOf(toolbox_view));
    toolbox_views_.removeAll(toolbox_view);
}

void MainWindow::init()
{
    // this button is just for save layout
    ui->pushButton_save_layout->hide();

    vw::Entity *scene = Life::get()->createScene("default");
    Life::get()->setCurrentScene(scene);
    ui->widget_scene_view->setScene(scene);

    {
        QFile file(R"(E:\develop\my_projects\dream\src\modules\main_ui\src\layout\init\main_splitter.dat)");
        file.open(QIODevice::ReadOnly);
        ui->splitter_main_vertical->restoreState(file.readAll());
    }

    {
        QFile file(R"(E:\develop\my_projects\dream\src\modules\main_ui\src\layout\init\central_splitter.dat)");
        file.open(QIODevice::ReadOnly);
        ui->splitter_central_horizon->restoreState(file.readAll());
    }

    left_panel_layout_ = new QVBoxLayout;
    ui->widget_left_panel->setLayout(left_panel_layout_);
    left_panel_layout_->setMargin(0);

    bottom_panel_layout_ = new QVBoxLayout;
    ui->widget_bottom_panel->setLayout(bottom_panel_layout_);
    bottom_panel_layout_->setMargin(0);

    right_panel_layout_ = new QVBoxLayout;
    ui->widget_right_panel->setLayout(right_panel_layout_);
    right_panel_layout_->setMargin(0);

    ui->widget_tab->setTabSize(QSize(60, 20));
    connect(ui->widget_tab, &TabBar::currentChanged, this, &MainWindow::setCurrentToolbox);
}

void MainWindow::on_pushButton_save_layout_clicked()
{
    {
        QFile file(R"(E:\develop\my_projects\dream\src\modules\main_ui\src\layout\init\main_splitter.dat)");
        file.open(QIODevice::WriteOnly);
        file.write(ui->splitter_main_vertical->saveState());
    }

    {
        QFile file(R"(E:\develop\my_projects\dream\src\modules\main_ui\src\layout\init\central_splitter.dat)");
        file.open(QIODevice::WriteOnly);
        file.write(ui->splitter_central_horizon->saveState());
    }
}

void MainWindow::setCurrentToolbox(int index)
{
    if(current_toolbox_ != nullptr){
        if(current_toolbox_->leftPanel() != nullptr){
            left_panel_layout_->removeWidget(current_toolbox_->leftPanel());
        }
        if(current_toolbox_->rightPanel() != nullptr){
            right_panel_layout_->removeWidget(current_toolbox_->rightPanel());
        }
        if(current_toolbox_->bottomPanel() != nullptr){
            bottom_panel_layout_->removeWidget(current_toolbox_->bottomPanel());
        }

        current_toolbox_ = nullptr;
    }

    if(index < 0){
        return;
    }

    Q_ASSERT(index < toolbox_views_.size());

    IToolboxView *toolbox_view = toolbox_views_[index];
    if(toolbox_view->leftPanel() != nullptr){
        left_panel_layout_->addWidget(toolbox_view->leftPanel());
        ui->widget_left_panel->show();
        ui->widget_left_panel->setMaximumWidth(toolbox_view->leftPanel()->maximumWidth());
        ui->widget_left_panel->setMinimumWidth(toolbox_view->leftPanel()->minimumWidth());
    }
    else{
        ui->widget_left_panel->hide();
    }

    if(toolbox_view->rightPanel() != nullptr){
        right_panel_layout_->addWidget(toolbox_view->rightPanel());
        ui->widget_right_panel->show();
    }
    else{
        ui->widget_right_panel->hide();
    }

    if(toolbox_view->bottomPanel() != nullptr){
        bottom_panel_layout_->addWidget(toolbox_view->bottomPanel());
        ui->widget_bottom_panel->show();
    }
    else{
        ui->widget_bottom_panel->hide();
    }

    current_toolbox_ = toolbox_view;
}
