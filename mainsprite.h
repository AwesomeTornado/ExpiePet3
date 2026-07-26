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
#include "legKinematics.h"
#include "twoBoneKinematic.h"
#include "vMath.h"

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
//All of these transforms, offsets, distances, and rotations should really be put in a json file.
    QPixmap spxHead = QPixmap("../expie/Head/experimentHead.png");
    QPointF spoHead = QPointF(120,90);
    QPointF sptHead = QPointF(10,12);
    spriteNode snHead = spriteNode(&scene, spxHead, spoHead, sptHead, -90, 90, spriteSize);

    QPixmap spxUpTorso = QPixmap("../expie/Body/experimentUpTorso.png");
    QPointF spoUpTorso = QPointF(105,100);
    QPointF sptUpTorso = QPointF(0,0);
    spriteNode snUpTorso = spriteNode(&scene, spxUpTorso, spoUpTorso, sptUpTorso, -90, 90, spriteSize);



    QPixmap spxDownTorso = QPixmap("../expie/Body/experimentDownTorso.png");
    QPointF spoDownTorso = QPointF(115,140);
    QPointF sptDownTorso = QPointF(0,0);
    spriteNode snDownTorso = spriteNode(&scene, spxDownTorso, spoDownTorso, sptDownTorso, -90,90, spriteSize);

    QPixmap spxTail = QPixmap("../expie/Body/experimentTail.png");
    QPointF spoTail = QPointF(0,160);
    QPointF sptTail = QPointF(0,0);
    spriteNode snTail = spriteNode(&scene, spxTail, spoTail, sptTail, -90,90, spriteSize);

    QPixmap spxThigh = QPixmap("../expie/Body/experimentThigh.png");
    QPointF spoThigh = QPointF(120,195);
    //QPointF spoThigh = QPointF(50,50);
    QPointF sptThigh = QPointF(3,4);
    spriteNode snThigh = spriteNode(&scene, spxThigh, spoThigh, sptThigh, -360, 360, spriteSize);

    QPixmap spxCrus = QPixmap("../expie/Body/experimentCrus.png");
    qreal sproCrus = 70;
    qreal spdCrus = 40;
    QPointF sptCrus = QPointF(2,0);
    spriteNode snCrus = spriteNode(&scene, spxCrus, sproCrus, spdCrus, sptCrus, -180, 180, spriteSize, &snThigh);

    QPixmap spxFoot = QPixmap("../expie/Body/experimentFoot.png");
    QPointF sptFoot = QPointF(5,3);
    qreal sproFoot = 70;
    qreal spdFoot = 40;
    spriteNode snFoot = spriteNode(&scene, spxFoot, sproFoot, spdFoot, sptFoot, -180, 90, spriteSize, &snCrus);

    //twoBoneKinematic rightLeg = twoBoneKinematic(&snThigh, spdFoot, -50, &snFoot, 50, 0);

    legKinematics legSolver = legKinematics(&snThigh, &snCrus, &snFoot);

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

    void addPosY(float pos);
    void addPosX(float pos);
};


#endif //EXPIEPET3_MAINSPRITE_H
