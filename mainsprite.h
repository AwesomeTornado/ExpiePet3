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

    ~mainsprite() override;

private:
    Ui::mainsprite *ui;
    const IPC *ipc;

    QPointF prevLocation = QPointF(0,0);
    QPointF velocity = QPointF(0,0);
    QPointF location = QPointF(0,0);
    QPointF dragOffset = QPointF(0,0);
    bool dragging = false;

    const float deltaTime = 10.f;

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void handleMouseEvent(QMouseEvent *event);

    void windowPhysics(QPoint center);

    void mulVelX(float mult);

    void mulVelY(float mult);

    void addVelX(float add);

    void addVelY(float add);
};


#endif //EXPIEPET3_MAINSPRITE_H
