//
// Created by harleyp on 7/22/26.
//
#include "spriteNode.h"
#ifndef EXPIEPET3_TWOBONEKINEMATIC_H
#define EXPIEPET3_TWOBONEKINEMATIC_H


class twoBoneKinematic {
public:
    twoBoneKinematic(spriteNode* parent, qreal radiusA, qreal parentRotationOffset, spriteNode* child, qreal radiusB, qreal childRotationOffset);

    void setGoal(QPointF goal);
    void setOrigin(QPointF origin);
    void update();
private:
    QPointF goal;
    QPointF origin;
    qreal radiusParent;
    qreal radiusChild;
    qreal parentRotationOffset;
    qreal childRotationOffset;

    spriteNode* parent;
    spriteNode* child;
};


#endif //EXPIEPET3_TWOBONEKINEMATIC_H
