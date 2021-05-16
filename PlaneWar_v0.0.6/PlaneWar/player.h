#ifndef PLAYER_H
#define PLAYER_H
#include <QPixmap>
#include <QRect>
#include "bullet.h"
class Player
{
public:
    Player();

    // 射击
    void shoot(void);
    // 设置位置
    void setPosition(int, int);

    void updateByKey();

    // 飞机贴图
    QPixmap m_plane;
    // 飞机左上角坐标
    int m_x;
    int m_y;
    // 碰撞体积
    QRect m_rect;

    //移动标志
    bool m_mov_right;
    bool m_mov_left;
    bool m_mov_up;
    bool m_mov_down;

    // 发射间隔记录
    int m_record;

    // 弹匣
    Bullet m_bullets[BULLET_MAX_NUM];
    // 由键盘控制射击，没有那个自动射击间隔了
    // 射击标志
    bool m_fire;


    // 血量
    int heart_num = LIFE;
};

#endif // PLAYER_H
