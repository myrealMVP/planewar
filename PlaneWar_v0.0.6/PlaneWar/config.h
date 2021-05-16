#ifndef CONFIG_H
#define CONFIG_H
// 游戏配置文件

constexpr int WINDOW_WIDTH = 512;
constexpr int WINDOW_HEIGHT = 768;
constexpr auto GAME_TITEL = "PlaneWar";
constexpr auto GAME_RES_PATH = "./plane.rcc";
constexpr auto GAME_ICO_PATH = ":/resource/app.ico";
constexpr int GAME_FPS = 10;       // 多少毫秒刷新一次画面

constexpr auto MAP_PATH = ":/resource/background1.png";
constexpr int MAP_SCROLL_SPEED = 2;

constexpr auto PLANE_PATH1 = ":/resource/icons8-fighter-96.png";
constexpr int PLANE_SPEED = 15;

constexpr auto BULLET_PATH = ":/resource/bullet2.png";
constexpr int BULLET_SPEED = 10;
constexpr int BULLET_MAX_NUM = 30;

constexpr auto ENEMY_PATH1 = ":/resource/icons8-fighter-jet-80 (1).png";
constexpr int ENEMY_SPEED = 5;
constexpr int ENEMY_MAX_NUM = 20;
constexpr int ENEMY_INTERVAL = 30; // 敌机出场间隔
constexpr int ENEMY_FIRE_INTERVAL = 20; // 敌机开火间隔
constexpr auto ENEMY_BULLET_PATH = ":/resource/enemy_bullet1.png";

#define BOMB_PATH ":/resource/bomb-%1.png"
constexpr int BOMB_NUM = 20;    // 最大爆炸数量
constexpr int BOMB_MAX = 7;        // 爆炸效果的图片数
constexpr int BOMB_INTERVAL = 20;   // 更新爆炸图片的间隔

constexpr int HEART_WIDTH = 56; // 红心宽度
constexpr auto HEART_PATH = ":/resource/heart.png";
constexpr int LIFE = 3;    //初始血量
constexpr int score = 0;    //得分


#endif // CONFIG_H
