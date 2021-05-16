#include "bullet.h"
#include <QtMath>
Bullet::Bullet()
{
    //  贴图
    m_bullet.load(BULLET_PATH);
    // 速度
    m_speed = BULLET_SPEED;
    // 位置
    m_x = (WINDOW_WIDTH - m_bullet.width()) / 2;
    m_y = WINDOW_HEIGHT;
    // 初始闲置
    m_free = true;
    // 碰撞体积
    m_rect.setWidth(m_bullet.width());
    m_rect.setHeight(m_bullet.height());
    m_rect.moveTo(m_x, m_y);

}

static bool isOut(int x, int y, int xl = 0, int xr = WINDOW_WIDTH, int yl = 0, int yr = WINDOW_HEIGHT){
    return x < xl || x > xr || y < yl || y > yr;
}


void Bullet::updatePosition()
{
    // 空闲的子弹，无需更新
    if(m_free){
        return;
    }
//    // 这里是默认向上运动，还没用到m_direction
//    m_y -= m_speed;

    if(m_direction.first == 0){
        m_y += (m_direction.second > 0 ? 1 : -1) * m_speed;
    }else{

        double theta = atan((double)m_direction.second / m_direction.first);
        int dx = m_speed * cos(theta);
        int dy = m_speed * sin(theta);

        m_x += dx;
        m_y += dy;
    }


    m_rect.moveTo(m_x, m_y);

    // 出屏幕则恢复空闲
    if(isOut(m_x, m_y)){
        m_free = true;
    }

}

void Bullet::adjust()
{
    // 变换
    m_direction.second = -m_direction.second;
}
