//
// Created by harleyp on 7/6/26.
//

#ifndef EXPIEPET3_IPC_H
#define EXPIEPET3_IPC_H

#include <QWidget>
#include <QDBusInterface>

typedef struct {
    QRectF boundingRect;
    QPointF velocity;
} advancedWindow;

class IPC : public QObject{
    Q_OBJECT
public:
    IPC();
    std::vector<advancedWindow> windows = std::vector<advancedWindow>(0);
    std::vector<int> heightmap = std::vector<int>(0);
    QPointF mousePos = QPointF(0,0);
    QPointF mouseVel = QPointF(0,0);
private:
    std::vector<QPointF> oldPoints = std::vector<QPointF>(0);

    const char* DBUS_SERVICE = "com.Choco.ExpiePet3";
    const char* DBUS_INTERFACE = DBUS_SERVICE;
    const char* DBUS_PATH = "/IPC";

    Q_CLASSINFO("D-Bus Interface", "com.Choco.ExpiePet3")
public slots:
    void recomputeHeightmap(int uuid);
    void updateCursor(int x, int y);
    void updateCompositor(int uuid, double x, double y, double width, double height);
    void windowClosed(int uuid);


};


#endif //EXPIEPET3_IPC_H
