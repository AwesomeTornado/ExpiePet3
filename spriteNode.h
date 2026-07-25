//
// Created by harleyp on 7/22/26.
//

#ifndef EXPIEPET3_SPRITENODE_H
#define EXPIEPET3_SPRITENODE_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "vMath.h"

class spriteNode {
public:
    spriteNode(QGraphicsScene *scene, QPixmap pixmap, qreal rotationOffset, qreal distance, QPointF origin,
               qreal rotation_min, qreal rotation_max, qreal size, spriteNode *parent);

    spriteNode(QGraphicsScene *scene, QPixmap pixmap, QPointF offset, QPointF origin, qreal rotation_min,
               qreal rotation_max, qreal size);

    void rotate(qreal rotation);
    QGraphicsPixmapItem graphics_item = QGraphicsPixmapItem();
    QPointF transform_origin;
    qreal rotation();
private:
    spriteNode* parent;
    bool orphan = 0;
    QPointF offset;
    qreal rotation_min;
    qreal rotation_max;
    qreal scale;
    qreal local_rotation;
protected:
    QPointF offset_transform_origin;
    qreal distance_from_parent;
    qreal rotation_offset;
    std::vector<spriteNode*> children = std::vector<spriteNode*>();
    void inheritLocation();
    void inheritRotation();
};


#endif //EXPIEPET3_SPRITENODE_H
