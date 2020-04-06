#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include <QSplitter>
#include <QToolBar>
#include <QDebug>
#include <QStatusBar>
#include <QLabel>
#include <QShortcut>

#include "directoryviewer.h"
#include "editor.h"
//#include "Controllers/editorcontroller.h"
//#include "Controllers/guiController.h"


class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QAction *addToolBarButton(QFunctionPointer callback, QString btnName, QIcon &&icon);
    QShortcut *addShortcut(QFunctionPointer callback, QKeySequence &&seq);
    void addToolBarSpacer();

private:
    DirectoryViewer *dirViewer;
    QTabWidget *editorTabWidget;
    QStatusBar *status;
    QSplitter *centerWidget;
    QSplitter *mainSplitter;
    QToolBar *toolBar;
    QWidget *leftPanel;
    QVBoxLayout *leftPanelLay;
    QLabel *workSpacelbl;
    void initToolBar();

friend class GUIContoller;
friend class EditorController;
};
#endif // MAINWINDOW_H
