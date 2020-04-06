#ifndef MAINCONTOLLER_H
#define MAINCONTOLLER_H

#include "../GUI/xml_Editor.h"
#include "../GUI/settings.h"
#include "editorcontroller.h"
#include <QObject>
#include <QLineEdit>
#include <QInputDialog>
#include <QShortcut>

class GUIContoller : public QObject{
    Q_OBJECT
public:
    static void registerMainWindow(MainWindow*);
    static void start();

private:
    static MainWindow *main;
    static void openFolder();
    static void newFile();
    static void openFile(QString);
    static void saveFile();
    static void showSettings();
};

#endif // MAINCONTOLLER_H
