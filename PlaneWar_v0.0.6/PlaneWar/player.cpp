#include "player.h"
#include "config.h"
Player::Player()
{
    // 初始化飞机贴图
    m_plane.load(PLANE_PATH1);

    // 初始化坐标
    // 靠下居中
    m_x = (WINDOW_WIDTH - m_plane.width()) / 2;
    m_y = WINDOW_HEIGHT - m_plane.height();
    // 初始化碰撞体积
    m_rect.setWidth(m_plane.width());
    m_rect.setHeight(m_plane.height());
    m_rect.moveTo(m_x, m_y);

    // 初始化移动标志
    m_mov_down = m_mov_up = m_mov_left = m_mov_right = false;

    //初始化子弹方向
    for(int i = 0; i < BULLET_MAX_NUM; ++i){
        m_bullets[i].m_direction = {0, 1};
        m_bullets[i].adjust();  // 转为qt坐标系中的方向
    }


}

void Player::shoot()
{
    // 不发射
    if(!m_fire){
        return;
    }
    ++m_record;
    if(m_record < 12){
        return;
    }
    m_record = 0;

    for(int i = 0; i < BULLET_MAX_NUM; ++i){
        // 找空闲子弹
        if(m_bullets[i].m_free){
            m_bullets[i].m_free = false;
            m_bullets[i].m_x = m_x;
            m_bullets[i].m_y = m_y;
            break;
        }
    }
}

void Player::setPosition(int x, int y)
{
    // 移动
    m_x = x;
    m_y = y;
    m_rect.moveTo(x, y);
}

void Player::updateByKey()
{
    // 移动
    if(m_mov_up)
        m_y -= PLANE_SPEED;
    if(m_mov_down)
        m_y += PLANE_SPEED;
    if(m_mov_left)
        m_x -= PLANE_SPEED;
    if(m_mov_right)
        m_x += PLANE_SPEED;

    if(m_x < 0)
        m_x = 0;
    if(m_x >= WINDOW_WIDTH - m_plane.width())
        m_x = WINDOW_WIDTH - m_plane.width();
    if(m_y < 0)
        m_y = 0;
    if(m_y >= WINDOW_HEIGHT - m_plane.height())
        m_y = WINDOW_HEIGHT - m_plane.height();

    m_rect.moveTo(m_x, m_y);
}
