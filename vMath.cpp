//
// Created by harleyp on 7/24/26.
//

#include "vMath.h"

qreal vMath::magnitude(QPointF a) {
    return sqrtf(a.x()*a.x() + a.y()*a.y());
}

qreal vMath::distance(QPointF a, QPointF b) {
    return magnitude(a - b);
}