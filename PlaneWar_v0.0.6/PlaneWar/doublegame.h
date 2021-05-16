#ifndef DOUBLEGAME_H
#define DOUBLEGAME_H

#include <QMainWindow>
#include <QCloseEvent>
class DoubleGame : public QMainWindow
{
    Q_OBJECT
public:
    explicit DoubleGame(QWidget *parent = nullptr);


    void closeEvent(QCloseEvent *);
signals:
    void ExitWin();

};

#endif // DOUBLEGAME_H
