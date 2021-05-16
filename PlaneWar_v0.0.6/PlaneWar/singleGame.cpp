#include "singleGame.h"
#include "config.h"
#include <QDebug>
#include <QIcon>
#include <QPainter>
#include <QKeyEvent>
#include <ctime>
#include <QMessageBox>
#include <QCoreApplication>
#include "mainwindow.h"
#include <QLabel>
#include <QMovie>

//int SingleGame::count;

SingleGame::SingleGame(QWidget *parent) : QMainWindow(parent)
{
    // 敌机出场横坐标的随机数种子
    srand( (unsigned int)time(NULL) );


    initWindow();
    playGame();

    setAttribute(Qt::WA_DeleteOnClose);

//    count++;
//    id = count;
//    qDebug() << "单人游戏" << id;
}

SingleGame::~SingleGame()
{
    //qDebug() << "退出单人游戏！" << id;

}
// 初始化窗口
void SingleGame::initWindow(void)
{
    // 设置窗口大小，且无法修改
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // 设置标题
    setWindowTitle(GAME_TITEL);
    // 设置图标
    setWindowIcon(QIcon(GAME_ICO_PATH));

    // 初始化定时器
    m_timer.setInterval(GAME_FPS);

    // 敌机出场间隔初始化
    m_recorder = 0;


    m_heart.load(HEART_PATH);

}

// 用于恢复父窗口
void SingleGame::closeEvent(QCloseEvent *){
    qDebug() << "发送退出信号";
    // 发射一个信号
    emit ExitWin();
}


// 游戏启动
void SingleGame::playGame()
{
    // 开场倒计时相关
    // 实际是播放gif，label用来确定位置
    QLabel *waiting;
    QMovie *movie;
    waiting = new QLabel(this);	//创建label
    waiting->setGeometry(0, 0, 512, 768);//设置位置和大小
    waiting->setAlignment(Qt::AlignCenter);//设置居中（动图在label的位置）
    waiting->setStyleSheet("background:transparent");//叫背景颜色透明（当然动图背景也要选透明的）
    movie = new QMovie(":/resource/321_transparent.gif");   // gif资源文件
    movie->setScaledSize(QSize(500,500));//设置动图大小
    waiting->setMovie(movie);// movie 放入
    movie->start(); // 开始
    waiting->show();

    // singleshot实际上是异步执行的。。。
    // 不过对于现在来说，只要m_timer不计数，画面就不会有变化，就有了同步阻塞的效果（大概。。
    // 这里捕获得是值捕获，在表达式创建时捕获（引用捕获是在调用时）,主要是对于movie和waiting这俩，m_timer似乎不太影响
    // 3400ms和选用的gif图相关
    QTimer::singleShot(3400, this, [=]{
        qDebug() << "计时结束";

        movie->stop();
        waiting->close();

        delete movie;
        delete waiting;
         // 启动定时器
        m_timer.start();
    });

    // 启动定时器
    //m_timer.start();

    // 监听定时器的信号
    connect(&m_timer, &QTimer::timeout, [=]{
        // 更新并绘制
        enemyToScene();

        updateAll();

        update(); // 调用paintEvent

        collisionDetection();
    });
}
// 更新所有元素坐标
void SingleGame::updateAll()
{
    m_map.updateMap();
//    //测试子弹
//    m_bullets.m_free = false;
//    m_bullets.updatePosition();
    // 发射子弹
    m_player.shoot();
    for(int i = 0; i < BULLET_MAX_NUM; ++i){
        if(m_player.m_bullets[i].m_free == false){
            m_player.m_bullets[i].updatePosition();
        }
    }

    // 敌机出场
    for(int i = 0; i < ENEMY_MAX_NUM; ++i){
        // 找非空闲敌机
        if(m_enemys[i].m_free == false){
            m_enemys[i].updatePosition();
            m_enemys[i].shoot();
            // 敌机发射
            for(int j = 0; j < BULLET_MAX_NUM; ++j){
                if(m_enemys[i].m_bullets[j].m_free == false){
                    m_enemys[i].m_bullets[j].updatePosition();
                }
            }
        }
    }

    // 爆炸效果
    for(int i = 0; i < BOMB_NUM; ++i){
        if(m_bombs[i].m_Free == false){
            m_bombs[i].updateInfo();
        }
    }

}
// 绘制
void SingleGame::paintEvent(QPaintEvent *)
{
    //在当前窗口绘制
    QPainter painter(this);

    // 绘制地图
    painter.drawPixmap(0, m_map.m_map1_Y, m_map.m_map1);
    painter.drawPixmap(0, m_map.m_map2_Y, m_map.m_map2);
    // 绘制飞机
    //qDebug() << "飞机位置: " << m_player.m_x << ' ' << m_player.m_y;
    painter.drawPixmap(m_player.m_x, m_player.m_y, m_player.m_plane);


    // 绘制子弹
    //painter.drawPixmap(m_bullets.m_x, m_bullets.m_y, m_bullets.m_bullet);
    for(int i = 0; i < BULLET_MAX_NUM; ++i){
        if(m_player.m_bullets[i].m_free == false){
            painter.drawPixmap(m_player.m_bullets[i].m_x,
                               m_player.m_bullets[i].m_y,
                               m_player.m_bullets[i].m_bullet);
        }
    }

    // 绘制血量
    for(int i = 0; i < m_player.heart_num; ++i){
        painter.drawPixmap(i * HEART_WIDTH, 0, m_heart);
    }

    // 绘制敌机
    for(int i = 0; i < ENEMY_MAX_NUM; ++i){
        // 找非空闲敌机
        if(m_enemys[i].m_free == false){
            painter.drawPixmap(m_enemys[i].m_x,
                               m_enemys[i].m_y,
                               m_enemys[i].m_enemy);
            //绘制敌机的子弹
            for(int j = 0; j < BULLET_MAX_NUM; ++j){
                if(m_enemys[i].m_bullets[j].m_free == false){
                    painter.drawPixmap(m_enemys[i].m_bullets[j].m_x,
                                       m_enemys[i].m_bullets[j].m_y,
                                       m_enemys[i].m_bullets[j].m_bullet);
                }
            }
        }
    }
    // 绘制爆炸图片
    for(int i = 0; i < BOMB_NUM; ++i){
        if(m_bombs[i].m_Free == false){
            painter.drawPixmap(m_bombs[i].m_X,
                               m_bombs[i].m_Y,
                               m_bombs[i].m_pixArr[m_bombs[i].m_Index]);
        }
    }
}

void SingleGame::keyPressEvent(QKeyEvent *event)
{
    // 键盘控制
    // WSAD 上下左右
    // space 射击
    switch (event->key()) {
        case Qt::Key_W:
            qDebug() << "w";
            m_player.m_mov_up = true;
            break;
        case Qt::Key_S:
            qDebug() << "s";
            m_player.m_mov_down = true;
            break;
        case Qt::Key_A:
            qDebug() << "a";
            m_player.m_mov_left = true;
            break;
        case Qt::Key_D:
            qDebug() << "d";
            m_player.m_mov_right = true;
            break;
        case Qt::Key_Space:
            qDebug() << "space";
            m_player.m_fire = true;
            break;
    }
    m_player.updateByKey();

}

void SingleGame::keyReleaseEvent(QKeyEvent *event)
{
    // 松开按键，标志恢复
    switch (event->key()) {
        case Qt::Key_W:
            qDebug() << "w";
            m_player.m_mov_up = false;
            break;
        case Qt::Key_S:
            qDebug() << "s";
            m_player.m_mov_down = false;
            break;
        case Qt::Key_A:
            qDebug() << "a";
            m_player.m_mov_left = false;
            break;
        case Qt::Key_D:
            qDebug() << "d";
            m_player.m_mov_right = false;
            break;
        case Qt::Key_Space:
            qDebug() << "space";
            m_player.m_fire = false;
            break;
    }
}

void SingleGame::enemyToScene()
{
    // 敌机登场
    ++m_recorder;
    if(m_recorder < ENEMY_INTERVAL){
        return;
    }

    m_recorder = 0;
    for(int i = 0; i < ENEMY_MAX_NUM; ++i){
        // 找空闲敌机
        if(m_enemys[i].m_free){
            m_enemys[i].m_free = false;

            // 随机出场坐标
            m_enemys[i].m_x = rand() % (WINDOW_WIDTH - m_enemys[i].m_enemy.width());

            m_enemys[i].m_y = -m_enemys[i].m_enemy.height();

            break;
        }
    }

}

void SingleGame::collisionDetection()
{
    // 碰撞检测
    for(int i = 0; i < ENEMY_MAX_NUM; ++i){

        // 遍历非空闲敌机
        if(m_enemys[i].m_free == false){

            // 如果玩家撞上敌机 ， 玩家gg
            if(m_enemys[i].m_rect.intersects(m_player.m_rect)){
               gameOver();
            }


            // 遍历玩家的非空闲子弹 -- 玩家射击敌机
            for(int j = 0; j < BULLET_MAX_NUM; ++j){
                if(m_player.m_bullets[j].m_free == false){

                    // 矩形是否相交
                    if(m_enemys[i].m_rect.intersects(m_player.m_bullets[j].m_rect)){
                            // 碰上了令敌机和该子弹消失
                            // 暂不考虑血量之类的
                            m_enemys[i].m_free = true;
                            m_player.m_bullets[j].m_free = true;

                            // 该敌机的子弹也消失
                            for(int k = 0; k < BULLET_MAX_NUM; ++k)
                                m_enemys[i].m_bullets[k].m_free = true;

                            // 播放爆炸效果
                            for(int k = 0;k < BOMB_NUM;k++){
                                if(m_bombs[k].m_Free) {
                                    m_bombs[k].m_Free = false;
                                    m_bombs[k].m_X = m_enemys[i].m_x;
                                    m_bombs[k].m_Y = m_enemys[i].m_y;
                                    break;
                                }
                            }
                    }
                }
            }

            // 遍历敌机的非空闲子弹  --- 敌机射击玩家
            for(int j = 0; j < BULLET_MAX_NUM; ++j){
                if(m_enemys[i].m_bullets[j].m_free == false){
                    if(m_enemys[i].m_bullets[j].m_rect.intersects(m_player.m_rect))
                    {
                        // 玩家被击中，扣除生命值
                        loseLife();
                        m_enemys[i].m_bullets[j].m_free = true;
                    }
                }
            }

        }


    }
}

void SingleGame::loseLife()
{
    m_player.heart_num--;
    if(m_player.heart_num == 0)
    {
        gameOver();
    }
}

void SingleGame::gameOver()
{

    auto result = QMessageBox::question(this, "游戏结束", "本次游戏结束\n是否重新开始", QMessageBox::Yes|QMessageBox::No);
    m_timer.stop();
    this->close();
    if(result == QMessageBox::Yes){
        auto p = (MainWindow *)parentWidget();
        p->restartGame(1);
    }
}
