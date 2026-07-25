//
// Created by harleyp on 7/22/26.
//

#include "twoBoneKinematic.h"

twoBoneKinematic::twoBoneKinematic(spriteNode* parent, qreal radiusA, qreal parentRotationOffset, spriteNode* child, qreal radiusB, qreal childRotationOffset) {
    this->parent = parent;
    this->child = child;
    this->radiusParent = radiusA;
    this->radiusChild = radiusB;
    this->parentRotationOffset = parentRotationOffset;
    this->childRotationOffset = childRotationOffset;
}

void twoBoneKinematic::setGoal(QPointF goal) {
    this->goal = goal;
}

void twoBoneKinematic::setOrigin(QPointF origin) {
    this->origin = origin;
}

qreal magnitude(QPointF a) {
    return sqrtf(a.x()*a.x() + a.y()*a.y());
}

qreal distance(QPointF a, QPointF b) {
    return magnitude(a - b);
}

void twoBoneKinematic::update() {
    QPointF parent_transform_origin = parent->transform_origin;
    QPointF local_goal = goal - parent_transform_origin;
    qreal goal_magnitude_sq = magnitude(local_goal);
    qreal radius_difference = radiusParent - radiusChild;
    //qreal goal_slope =  local_goal.x()/local_goal.y();
    qreal goal_slope =  local_goal.y()/local_goal.x();
    qreal denominator = 2. * (local_goal.x() + (goal_slope * local_goal.y()));
    qreal x_centerline = (radius_difference + goal_magnitude_sq) / denominator;
    qreal y_centerline = goal_slope * local_goal.x();
    QPointF centerpoint = QPointF(x_centerline, y_centerline);
    qreal a_top = magnitude(centerpoint);
    qreal a_angle_top = acosf(a_top/radiusParent);
    qreal c_angle = (M_1_PIf/2.) - a_angle_top;
    qreal a_bottom = magnitude(local_goal) - a_top;
    qreal a_angle_bottom = asinf(a_bottom / radiusChild);
    qreal a_angle = a_angle_top + a_angle_bottom;

    qreal parent_angle = c_angle;
    qreal child_angle = a_angle - parent_angle;

    if (qIsInf(parent_angle))
        return;
    if (qIsInf(child_angle))
        return;
    if (qIsNaN(parent_angle))
        return;
    if (qIsNaN(child_angle))
        return;
    if (qIsNull(parent_angle))
        return;
    if (qIsNull(child_angle))
        return;

    parent->rotate(parent_angle*(180./M_1_PIf) + parentRotationOffset);
    child->rotate(child_angle*(180./M_1_PIf) + childRotationOffset);
}
