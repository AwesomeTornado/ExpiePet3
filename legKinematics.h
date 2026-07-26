//
// Created by harleyp on 7/26/26.
//

#ifndef EXPIEPET3_LEGKINEMATICS_H
#define EXPIEPET3_LEGKINEMATICS_H

#include "spriteNode.h"
#include <QTime>


class legKinematics {
public:
    legKinematics(spriteNode* thigh, spriteNode* crus, spriteNode* foot);
    void update() const;
private:
    spriteNode* thigh;
    spriteNode* crus;
    spriteNode* foot;
};


#endif //EXPIEPET3_LEGKINEMATICS_H
