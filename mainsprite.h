//
// Created by harleyp on 7/6/26.
//

#ifndef EXPIEPET3_MAINSPRITE_H
#define EXPIEPET3_MAINSPRITE_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include "IPC.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class mainsprite;
}

QT_END_NAMESPACE

class mainsprite : public QWidget {
    Q_OBJECT

public:
    explicit mainsprite(QWidget *parent = nullptr);

    void incrementAnimation();

    ~mainsprite() override;

private:
    Ui::mainsprite *ui;
    const IPC *ipc;

    QPointF prevLocation = QPointF(0,0);
    QPointF velocity = QPointF(0,0);
    QPointF location = QPointF(0,0);
    QPointF dragOffset = QPointF(0,0);
    int animStep = 0;
    bool dragging = false;

    const float deltaTime = 10.f;

    const float spriteSize = 5.f;

    static QRectF spriteBoundingRect(QPixmap* pixmap, float size) {
        return QRectF(size * pixmap->size().width() / -2,size * pixmap->size().height() / -2, size * pixmap->size().width(), size * pixmap->size().height());
    };

//todo: make a struct for these and put them in an array for auto drawing.

    QPixmap spxHead = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/expie/Head/experimentHead.png");
    QGraphicsPixmapItem spgHead = QGraphicsPixmapItem(spxHead);
    QRectF sprHead = spriteBoundingRect(&spxHead,spriteSize);
    QPointF spoHead = QPointF(0,20 * spriteSize);

    QPixmap spxUpTorso = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/expie/Body/experimentUpTorso.png");
    QGraphicsPixmapItem spgUpTorso = QGraphicsPixmapItem(spxUpTorso);
    QRectF sprUpTorso = spriteBoundingRect(&spxUpTorso,spriteSize);
    QPointF spoUpTorso = QPointF(0,11 * spriteSize);

    QPixmap spxDownTorso = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/expie/Body/experimentDownTorso.png");
    QGraphicsPixmapItem spgDownTorso = QGraphicsPixmapItem(spxDownTorso);
    QRectF sprDownTorso = spriteBoundingRect(&spxDownTorso,spriteSize);
    QPointF spoDownTorso = QPointF(0,2 * spriteSize);

    QPixmap spxTail = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/expie/Body/experimentTail.png");
    QGraphicsPixmapItem spgTail = QGraphicsPixmapItem(spxTail);
    QRectF sprTail = spriteBoundingRect(&spxTail,spriteSize);
    QPointF spoTail = QPointF(0,-2 * spriteSize);

    QPixmap spxThigh = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/expie/Body/experimentThigh.png");
    QGraphicsPixmapItem spgThigh = QGraphicsPixmapItem(spxThigh);
    QRectF sprThigh = spriteBoundingRect(&spxThigh,spriteSize);
    QPointF spoThigh = QPointF(0,-8 * spriteSize);

    QPixmap spxFoot = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/expie/Body/experimentFoot.png");
    QGraphicsPixmapItem spgFoot = QGraphicsPixmapItem(spxFoot);
    QRectF sprFoot = spriteBoundingRect(&spxFoot,spriteSize);
    QPointF spoFoot = QPointF(0,-16 * spriteSize);
    //QPointF  = QPointF(0,0);

protected:
    void paintEvent(QPaintEvent*) override;

    void drawSprite(QPainter *painter);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void handleMouseEvent(QMouseEvent *event);

    bool windowPhysics(QPoint center);

    void mulVelX(float mult);

    void mulVelY(float mult);

    void addVelX(float add);

    void addVelY(float add);

    void setPosY(float pos);

    void setPosX(float pos);
};


#endif //EXPIEPET3_MAINSPRITE_H
