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
    connect(paintTimer, &QTimer::timeout, this, QOverload<>::of(&mainsprite::update));
    paintTimer->start(static_cast<int>(deltaTime));

    auto animTimer = new QTimer(); //The memory leak is intentional.
    connect(animTimer, &QTimer::timeout, this, &mainsprite::incrementAnimation);
    animTimer->start(static_cast<int>(250));
}

void mainsprite::incrementAnimation() {
    if (animStep >= 3) {
        animStep = 0;
    }else {
        animStep++;
    }

}

void mainsprite::paintEvent(QPaintEvent *) {

    //QPixmap pm("/home/harleyp/CLionProjects/ExpiePet3/VeryHappy.webp");
    QPixmap pm;
    if (dragging) {
        pm = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/stick_drag.png");
    }
    else if (velocity.y() > .5) {
        pm = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/stick_fall.png");
    }
    else if (abs(velocity.x()) < .5) {
        pm = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/stick_idle.png");
    }else {
        pm = QPixmap("/home/harleyp/CLionProjects/ExpiePet3/stick_walk.png");
    }
    pm = pm.copy(QRect(animStep * 100, 0, 100,100));
    QPoint screenCenter = QPoint(window()->size().width()/2, window()->size().height()/2);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(screenCenter);
    if (dragging) {
        QPointF newLocation = (ipc->mousePos * .9) - dragOffset;
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
        bool canFall = windowPhysics(mapToGlobal(screenCenter + QPoint(0, 50)));
        if (canFall) {
            addVelY(.25);
        }
        if (pos().y() > 900) {
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
    velocity = pos() - prevLocation;
    painter.setPen(Qt::NoPen);
    float mult = 0;
    if (velocity.x() < -.5) {
        QTransform transf = painter.transform();
        transf.scale(-1, 1);
        painter.setTransform(transf);
        mult = -1;
    }

    if (velocity.x() > .5)
        mult = 1;
    //painter.rotate( mult * 360 * QTime::currentTime().msec()/1000);
    painter.drawImage(QRectF(  QPoint(-50,-50), QPoint(50,50)), pm.toImage());
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
    for (int i = ipc->heightmap.size() - 1; i >= 0; i--) {
        if (ipc->heightmap[i] != NULL) {
            int index = ipc->heightmap[i];
            advancedWindow focusedWindow = ipc->windows.at(index);
            if (!focusedWindow.boundingRect.isNull()) {
                if (focusedWindow.boundingRect.contains(center)) {
                    if (abs(focusedWindow.boundingRect.top() - center.y()) < 50) {
                        velocity.setX(focusedWindow.velocity.x() * .8 + velocity.x() * .2);
                        mulVelX(.5);
                        //if (velocity.y() > 0)
                        //    mulVelY(-.5);
                        //addVelY(std::min(focusedWindow.velocity.y(), 0.0));
                        //addVelY(std::min(focusedWindow.boundingRect.top() - center.y(),0.0));
                        //mulVelY(.5);
                        mulVelY(0);
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


mainsprite::~mainsprite() {
    delete ui;
}
