#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include<QGraphicsScene>
#include<QPainter>
#include<QDebug>
class GridScene : public QGraphicsScene
{
    public:
        GridScene(qreal x, qreal y, qreal w, qreal h);

    protected:
        void drawBackground(QPainter *painter, const QRectF &rect);

};

#endif // GRIDSCENE_H
