//
// Created by harleyp on 7/6/26.
//

#include "IPC.h"

//todo: add window minimization logic. (Implement in KWINSCRIPT first)
IPC::IPC() {
    auto connection = QDBusConnection::sessionBus();

    if (!connection.isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.\n"
                 "To start it, run:\n"
                 "\teval `dbus-launch --auto-syntax`\n");
    }

    if (!connection.registerService(DBUS_SERVICE)) {
        qWarning("%s\n", qPrintable(connection.lastError().message()));
        exit(1);
    }
    connection.registerObject(DBUS_PATH, this, QDBusConnection::ExportAllSlots);
}

void IPC::recomputeHeightmap(const int uuid) {
    bool beginShifting = false;
    for (int i = 0; i < windows.size() - 1; i++) {
        advancedWindow focusedWindow = windows.at(i);
        if (!focusedWindow.boundingRect.isNull()) {
            if (heightmap[i] == uuid)
                beginShifting = true;
            if (beginShifting)
                heightmap[i] = heightmap[i + 1];
        }
    }
    if (beginShifting)
        heightmap.pop_back();
    heightmap.push_back(uuid);
}

void IPC::updateCursor(const int x, const int y)
{
    const auto p = QPointF(x,y);
    mouseVel += p - mousePos;
    mouseVel *= .5; //Rudimentary smoothing.
    mousePos = p;
}

void IPC::updateCompositor(const int uuid, double x, double y, double width, double height) {
    x *= .9;
    y *= .9;
    width *= .9;
    height *= .9;
    std::printf("%d, %.2f,%.2f    %.2f,%.2f \n",uuid, x,y,width,height);
    if (uuid >= windows.size()) {
        windows.resize(uuid + 1);
        oldPoints.resize(uuid + 1);
        heightmap.resize(uuid + 1);
    }
    if (windows.at(uuid).boundingRect.isNull()) {
        advancedWindow newWindow = advancedWindow();
        newWindow.boundingRect = QRectF(x,y, width,height);
        newWindow.velocity = QPointF(0,0);
        oldPoints[uuid] = QPointF(x,y);
        windows[uuid] = newWindow;
    }
    advancedWindow focusedWindow = windows.at(uuid);
    focusedWindow.boundingRect = QRectF(x,y, width,height);
    focusedWindow.velocity = focusedWindow.boundingRect.topLeft() - oldPoints[uuid];
    if (abs(focusedWindow.velocity.x()) > 50)
        focusedWindow.velocity.setX(0);
    if (abs(focusedWindow.velocity.y()) > 50)
        focusedWindow.velocity.setY(0);
    windows[uuid] = focusedWindow;
    oldPoints[uuid] = QPointF(x,y);
}

void IPC::windowClosed(int uuid) {
    if (uuid >= windows.size()) {
        windows.resize(uuid + 1);
        oldPoints.resize(uuid + 1);
        heightmap.resize(uuid + 1);
    }
    const auto* newWindow = new advancedWindow();
    windows[uuid] = *newWindow;
    delete(newWindow);
}
