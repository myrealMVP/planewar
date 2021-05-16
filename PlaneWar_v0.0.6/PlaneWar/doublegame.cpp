#include "doublegame.h"
#include "config.h"
#include <QLabel>
#include <QMovie>

DoubleGame::DoubleGame(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(WINDOW_WIDTH * 1.5, WINDOW_HEIGHT);
    // 设置标题
    setWindowTitle(GAME_TITEL);
    // 设置图标
    setWindowIcon(QIcon(GAME_ICO_PATH));

}

void DoubleGame::closeEvent(QCloseEvent *){
    emit ExitWin();
}
