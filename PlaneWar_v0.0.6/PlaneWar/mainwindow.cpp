#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "config.h"
#include <QIcon>
#include "singleGame.h"
#include "doublegame.h"
#include "intro.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setFixedSize(640, 480);
    // 设置标题
    setWindowTitle(GAME_TITEL);
    // 设置图标
    setWindowIcon(QIcon(GAME_ICO_PATH));

    // 重开游戏相关
    connect(this, SIGNAL(restart_single()), ui->pushButton, SLOT(click()));
    connect(this, SIGNAL(restart_double()), ui->pushButton_2, SLOT(click()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 重开游戏相关
void MainWindow::restartGame(int id)
{

    if(id == 1){
        emit restart_single();
    }else if(id == 2){
        emit restart_double();
    }

}

// 单人游戏按钮
void MainWindow::on_pushButton_clicked()
{
    qDebug() << "单人游戏！！";
    SingleGame *sg = new SingleGame(this);
    sg->show();
    // 显示其中一个时，菜单窗口关闭
    this->hide();
    //qDebug() << "执行退出";
    // 子窗口关闭后，菜单窗口重新显示
    connect(sg, SIGNAL(ExitWin()), this, SLOT(show()));
}
// 双人游戏按钮
void MainWindow::on_pushButton_2_clicked()
{

    qDebug() << "双人游戏！！";
    DoubleGame *dg = new DoubleGame(this);
    dg->show();
    this->hide();
    connect(dg, SIGNAL(ExitWin()),this,SLOT(show()));
}

// 游戏说明按钮
void MainWindow::on_pushButton_3_clicked()
{

    qDebug() << "游戏说明！！";
    Intro *intro = new Intro(this);
    intro->show();
    this->hide();
    connect(intro, SIGNAL(ExitWin()),this,SLOT(show()));
}

