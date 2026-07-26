//
// Created by harleyp on 7/6/26.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainsprite.h" resolved

#include "mainsprite.h"

#include <iostream>

#include "ui_mainsprite.h"


mainsprite::mainsprite(QWidget *parent) : QWidget(parent), ui(new Ui::mainsprite) {
    ui->setupUi(this);

    ipc = new IPC();

    setWindowFlags(Qt::Window  | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    setParent(nullptr); // Create TopLevel-Widget
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_AlwaysStackOnTop, true);
    location = pos();

    auto paintTimer = new QTimer(); //The memory leak is intentional.
    connect(paintTimer, &QTimer::timeout, this, QOverload<>::of(&mainsprite::updateSprite));
    paintTimer->start(static_cast<int>(deltaTime));

    scene.addItem(&spgDownTorso);
    scene.addItem(&spgUpTorso);
    scene.addItem(&spgTail);
    spgDownTorso.setScale(spriteSize);
    spgUpTorso.setScale(spriteSize);
    spgTail.setScale(spriteSize);
    spgDownTorso.moveBy(spoDownTorso.x(), spoDownTorso.y());
    spgUpTorso.moveBy(spoUpTorso.x(), spoUpTorso.y());
    spgTail.moveBy(spoTail.x(), spoTail.y());

    this->ui->FancyCanvas->setScene(&scene);
    this->ui->FancyCanvas->show();
}

void mainsprite::updateSprite() {
    QPoint screenCenter = QPoint(window()->size().width()/2, window()->size().height()/2);
    if (dragging) {
        QPointF newLocation = ipc->getMousePos() - dragOffset;
        velocity = ipc->mouseVel;
        move(newLocation.toPoint());
        location = pos(); //Can this be simplified to location = newlocation?
    }else {


        if (pos().x() < 0 && velocity.x() < 0) {
            //this causes deltatime issues and wall sliding
            mulVelX(-.7f);
        }
        if (pos().x() > screen()->size().width() - window()->size().width() && velocity.x() > 0) {
            mulVelX(-.7f);
        }
        float windowHeight = this->window()->size().height() / 2;
        //float windowHeight = 0;
        bool canFall = windowPhysics(mapToGlobal(screenCenter + QPoint(0, windowHeight)));
        if (canFall) {
            addVelY(.25);
        }
        if (pos().y() > this->screen()->size().height() - 350) {
            mulVelX(.5);
            velocity.setY(0);
        }
        if (pos().y() < 0 && velocity.y() < 0) {
            mulVelY(-.5f);
        }

    }
    prevLocation = location;
    location += velocity;//this section could be cleaned up to get rid of prevLocation probably.
    move(location.toPoint());
    velocity = location - prevLocation;
    static int currentScale = 1;
    if (abs(velocity.x()) > 4) {
        if (velocity.x() > 0) {
            this->ui->FancyCanvas->scale((-1 == currentScale) ? -1 : 1,1);
            currentScale = 1;
        }else {
            this->ui->FancyCanvas->scale((1 == currentScale) ? -1 : 1, 1);
            currentScale = -1;
        }
    }

    drawSprite();
}

QRectF offsetRect(QRectF* rect, QPointF* offset) {
    return rect->adjusted(-offset->x(), -offset->y(), -offset->x(),-offset->y());
};

void mainsprite::drawSprite() {

    

    snHead.rotate(5 * sin((QTime::currentTime().msec() * M_PI * 2)/1000));
    //snFoot.rotate((50 * QTime::currentTime().msec()/1000) * 2);
    //snThigh.rotate((50 * QTime::currentTime().msec()/1000) * -1);
    QPointF target = start - QPointF(-2, 18 * sin((QTime::currentTime().msec() * M_PI * 2)/1000) + 28);
    rightLeg.setGoal(target);
    rightLeg.setOrigin(start);
    rightLeg.update();

}

void mainsprite::mousePressEvent(QMouseEvent *event) {
    handleMouseEvent(event);
}

void mainsprite::mouseReleaseEvent(QMouseEvent *event) {
    handleMouseEvent(event);
}

void mainsprite::handleMouseEvent( QMouseEvent *event) {
    Qt::MouseButtons buttons = event->buttons();
    if (buttons & Qt::LeftButton) {
        dragging = true;
        dragOffset = event->position().toPoint();
    } else {
        dragging = false;
    }
}

bool mainsprite::windowPhysics(const QPoint center) {
    float windowHeight = this->window()->size().height();
    for (int i = ipc->heightmap.size() - 1; i >= 0; i--) {
        if (ipc->heightmap[i] != NULL) {
            int index = ipc->heightmap[i];
            advancedWindow focusedWindow = ipc->windows.at(index);
            if (!focusedWindow.boundingRect.isNull()) {
                if (focusedWindow.boundingRect.contains(center)) {
                    qreal distToTop = focusedWindow.boundingRect.top() - center.y();
                    if ((distToTop > (- 15 - abs(focusedWindow.velocity.y())))  && velocity.y() - focusedWindow.velocity.y() >= 0) {
                        velocity.setX(focusedWindow.velocity.x() * .90 + velocity.x() * .1);
                        //mulVelX(.5);
                        //if (velocity.y() > 0)
                        //    mulVelY(-.5);
                        mulVelY(0);
                        addVelY(std::min(focusedWindow.velocity.y(), 0.0));
                        //addVelY(std::min(focusedWindow.boundingRect.top() - center.y(),0.0));
                        //mulVelY(.5);
                        addPosY(std::min(distToTop,0.));
                        //mulVelY(0);
                        return false;
                    }
                    return true;
                }
            }
        }
    }
    return true;
}

void mainsprite::mulVelX(const float mult) {
    velocity.setX(velocity.x() * mult);
}
void mainsprite::mulVelY(const float mult) {
    velocity.setY(velocity.y() * mult);
}
void mainsprite::addVelX(const float add) {
    velocity.setX(velocity.x() + add);
}
void mainsprite::addVelY(const float add) {
    velocity.setY(velocity.y() + add);
}
void mainsprite::setPosY(const float pos) {
    location.setY(pos);
    prevLocation.setY(pos);
}
void mainsprite::setPosX(const float pos) {
    location.setX(pos);
    prevLocation.setX(pos);
}

void mainsprite::addPosY(float pos) {
    location.setY(location.y() + pos);
}

void mainsprite::addPosX(float pos) {
    location.setX(location.x() + pos);
}

mainsprite::~mainsprite() {
    delete ui;
}
