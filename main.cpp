#include "GUI/xml_Editor.h"
#include "Controllers/guiController.h"
#include "Controllers/editorcontroller.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    QFile styleFile ("://style.css");
    styleFile.open(QIODevice::ReadOnly);
    QString style = styleFile.readAll();
    a.setStyleSheet(style);

    MainWindow w;
    GUIContoller::registerMainWindow(&w);
    EditorController::registerMainWindow(&w);
    w.show();
    return a.exec();
}
