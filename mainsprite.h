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

    QPixmap spxHead = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/expie/Head/experimentHead.png");
    QRectF sprHead = QRectF(spriteSize * spxHead.size().width() / -2,spriteSize * spxHead.size().height() / -2, spriteSize * spxHead.size().width(), spriteSize * spxHead.size().height());
    QPointF spoHead = QPointF(0,20 * spriteSize);

    QPixmap spxUpTorso = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/expie/Body/experimentUpTorso.png");
    QRectF sprUpTorso = QRectF(spriteSize * spxUpTorso.size().width() / -2,spriteSize * spxUpTorso.size().height() / -2, spriteSize * spxUpTorso.size().width(), spriteSize * spxUpTorso.size().height());
    QPointF spoUpTorso = QPointF(0,12 * spriteSize);

    QPixmap spxDownTorso = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/expie/Body/experimentDownTorso.png");
    QRectF sprDownTorso = QRectF(spriteSize * spxDownTorso.size().width() / -2,spriteSize * spxDownTorso.size().height() / -2, spriteSize * spxDownTorso.size().width(), spriteSize * spxDownTorso.size().height());
    QPointF spoDownTorso = QPointF(0,4 * spriteSize);

    QPixmap spxTail = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/expie/Body/experimentTail.png");
    QRectF sprTail = QRectF(spriteSize * spxTail.size().width() / -2,spriteSize * spxTail.size().height() / -2, spriteSize * spxTail.size().width(), spriteSize * spxTail.size().height());
    QPointF spoTail = QPointF(0,0 * spriteSize);
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
