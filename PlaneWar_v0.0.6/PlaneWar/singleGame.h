#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include <QMainWindow>
#include <QTimer>
#include "map.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "bomb.h"

#include <QCloseEvent>



class SingleGame : public QMainWindow
{
    Q_OBJECT
public:
    explicit SingleGame(QWidget *parent = nullptr);
    ~SingleGame();

//    static int count;
//    int id;

    // 初始化窗口
    void initWindow();

    // 游戏启动
    void playGame();
    // 更新所有元素坐标
    void updateAll();
    // 绘制   函数名不能改
    void paintEvent(QPaintEvent *);
    // 键盘事件 控制飞机移动
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

    // 敌机出场
    void enemyToScene();
    // 碰撞检测
    void collisionDetection();

    // 游戏退出、结束
    void gameOver();

    // 血量减少
    void loseLife();

    // 地图
    Map m_map;

    // 玩家飞机
    Player m_player;
    //    // 子弹  测试用
    //    Bullet m_bullets;
    // 敌机
    Enemy m_enemys[ENEMY_MAX_NUM];

    int m_recorder;
    // 定时器
    QTimer m_timer;

    // 爆炸效果
    Bomb m_bombs[BOMB_NUM];

    // 红心
    QPixmap m_heart;

    // 用于恢复父窗口
    void closeEvent(QCloseEvent *);
signals:
    void ExitWin();
};

#endif // SINGLEGAME_H
