//
// Created by harleyp on 7/26/26.
//

#include "legKinematics.h"

legKinematics::legKinematics(spriteNode *thigh, spriteNode *crus, spriteNode *foot) {
    this->thigh = thigh;
    this->crus = crus;
    this->foot = foot;
}

void legKinematics::update() const {
    qreal scalar = sin((QTime::currentTime().msec() * M_PI * 2.)/1000.) + 1.;
    qreal cosScalar = cos((QTime::currentTime().msec() * M_PI * 2.)/1000.) + 1.;
    this->thigh->rotate(-20.f * scalar + 20*cosScalar - 10);
    this->crus->rotate(40.f* scalar + 10);
    this->foot->rotate(-40.f* scalar - 30);
    //std::printf("%f\n", -40.f* scalar - 30);
}
