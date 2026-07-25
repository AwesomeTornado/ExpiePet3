//
// Created by harleyp on 7/22/26.
//

#include "spriteNode.h"


spriteNode::spriteNode(QGraphicsScene* scene, QPixmap pixmap, qreal rotationOffset, qreal distance, QPointF origin, qreal rotation_min, qreal rotation_max, qreal size, spriteNode* parent) {
    orphan = false;
    this->transform_origin = origin + parent->offset;
    this->rotation_min = rotation_min;
    this->rotation_max = rotation_max;
    this->offset_transform_origin = origin;
    this->scale = size;
    this->parent = parent;
    this->rotation_offset = rotationOffset;
    parent->children.push_back(this);
    distance_from_parent = distance;
    inheritLocation();

    graphics_item.setPixmap(pixmap);
    graphics_item.setScale(scale);
    scene->addItem(&graphics_item);
}

spriteNode::spriteNode(QGraphicsScene* scene, QPixmap pixmap, QPointF offset, QPointF origin, qreal rotation_min, qreal rotation_max, qreal size) {
    orphan = true;
    this->offset = offset;
    this->transform_origin = origin + offset;
    this->rotation_min = rotation_min;
    this->rotation_max = rotation_max;
    this->rotation_offset = 0;
    this->offset_transform_origin = origin;
    this->scale = size;

    graphics_item.setOffset(offset);
    graphics_item.setTransformOriginPoint(transform_origin);
    graphics_item.setPixmap(pixmap);
    graphics_item.setScale(scale);

    scene->addItem(&graphics_item);
}

void spriteNode::rotate(qreal rotation) {
    rotation = remainderf(rotation,360.f);
    this->local_rotation = rotation;
    if (!orphan)
        rotation += parent->rotation();
    rotation = std::max(rotation,rotation_min);
    rotation = std::min(rotation,rotation_max);
    graphics_item.setRotation(rotation);
    for(int i = 0; i < children.size(); i++) {
        spriteNode* child = children[i];
        child->inheritRotation();
        child->inheritLocation();
    }
}

qreal spriteNode::rotation() {
    if (orphan)
        return graphics_item.rotation();
    return parent->rotation() + graphics_item.rotation();
}

void spriteNode::inheritLocation() {
    //todo: fix this degrees to radians conversion I think its messed up.
    qreal x = cosf((parent->rotation() + rotation_offset) * 0.017) * distance_from_parent;
    qreal y = sinf((parent->rotation() + rotation_offset) * 0.017) * distance_from_parent;
    QPointF offset_from_parent = QPointF(x,y);
    transform_origin = parent->offset + offset_from_parent + offset_transform_origin;
    graphics_item.setOffset(parent->offset + offset_from_parent);
    graphics_item.setTransformOriginPoint(transform_origin);
}

void spriteNode::inheritRotation() {
    this->rotate(local_rotation);
}
