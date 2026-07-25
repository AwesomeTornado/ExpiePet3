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
#include <QGraphicsScene>
#include <QGraphicsView>
#include "spriteNode.h"
#include "IPC.h"
#include "twoBoneKinematic.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class mainsprite;
}


QT_END_NAMESPACE

class mainsprite : public QWidget {
    Q_OBJECT

public:
    explicit mainsprite(QWidget *parent = nullptr);

    ~mainsprite() override;

private:
    Ui::mainsprite *ui;
    const IPC *ipc;

    QGraphicsScene scene;

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
    QPointF spoHead = QPointF(120,90);
    QPointF sptHead = QPointF(10,12);
    spriteNode snHead = spriteNode(&scene, spxHead, spoHead, sptHead, -90, 90, spriteSize);

    QPixmap spxUpTorso = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/expie/Body/experimentUpTorso.png");
    QGraphicsPixmapItem spgUpTorso = QGraphicsPixmapItem(spxUpTorso);
    QRectF sprUpTorso = spriteBoundingRect(&spxUpTorso,spriteSize);
    QPointF spoUpTorso = QPointF(100,21 * spriteSize);



    QPixmap spxDownTorso = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/expie/Body/experimentDownTorso.png");
    QGraphicsPixmapItem spgDownTorso = QGraphicsPixmapItem(spxDownTorso);
    QRectF sprDownTorso = spriteBoundingRect(&spxDownTorso,spriteSize);
    QPointF spoDownTorso = QPointF(110,28 * spriteSize);

    QPixmap spxTail = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/expie/Body/experimentTail.png");
    QGraphicsPixmapItem spgTail = QGraphicsPixmapItem(spxTail);
    QRectF sprTail = spriteBoundingRect(&spxTail,spriteSize);
    QPointF spoTail = QPointF(0,32 * spriteSize);

    QPixmap spxThigh = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/expie/Body/experimentThigh.png");
    QPointF spoThigh = QPointF(110,195);
    QPointF sptThigh = QPointF(0,1);
    spriteNode snThigh = spriteNode(&scene, spxThigh, spoThigh, sptThigh, -360, 360, spriteSize);

    QPixmap spxFoot = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/expie/Body/experimentFoot.png");
    //QPointF sptFoot = QPointF(3,1);
    QPointF sptFoot = QPointF(3,1);
    qreal sproFoot = 75;
    qreal spdFoot = 60;
    spriteNode snFoot = spriteNode(&scene, spxFoot, sproFoot, spdFoot, sptFoot, -180, 180, spriteSize, &snThigh);

    twoBoneKinematic rightLeg = twoBoneKinematic(&snThigh, spdFoot, -50, &snFoot, 50, 0);

    QPointF start =  spoThigh + QPointF(20,50);



protected:

    void updateSprite();

    void drawSprite();

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
