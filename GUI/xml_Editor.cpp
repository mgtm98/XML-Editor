#include "xml_Editor.h"

#include <QDebug>
#include <QDirModel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    // --------------------------------------------- Init GUI Pointers ---------------------------------------------
    centerWidget = new QSplitter(Qt::Horizontal);
    editorTabWidget = new QTabWidget();
    mainSplitter = new QSplitter(Qt::Vertical);
    leftPanel = new QWidget();
    leftPanelLay = new QVBoxLayout();
    workSpacelbl = new QLabel("   Workspace");
    dirViewer = new DirectoryViewer("/",this);
    initToolBar();

    // ------------------------------- Directory Viewer Panel Section ---------------------------------------------
    leftPanel->setLayout(leftPanelLay);
    leftPanelLay->addWidget(workSpacelbl);
    leftPanelLay->addWidget(dirViewer);
    leftPanelLay->setContentsMargins(0,0,0,0);
    leftPanel->setMaximumWidth(250);
    leftPanel->setObjectName("LeftPanel");
    workSpacelbl->setObjectName("WorkSpace");
    workSpacelbl->setMinimumWidth(170);
    workSpacelbl->setMinimumHeight(25);

    // ------------------------------- Centeral Widget Section -----------------------------------------------------
    centerWidget->addWidget(leftPanel);
    centerWidget->addWidget(mainSplitter);
    mainSplitter->addWidget(editorTabWidget);
    mainSplitter->setObjectName("mainSplitter");
    editorTabWidget->setTabsClosable(true);
    setCentralWidget(centerWidget);
    centerWidget->setContentsMargins(0,0,0,0);

    showMaximized();

    status = statusBar();
    status->setMaximumHeight(20);
}

void MainWindow::initToolBar(){
    toolBar = new QToolBar();
    toolBar->setOrientation(Qt::Vertical);
    toolBar->setMovable(false);
    addToolBar(Qt::LeftToolBarArea, toolBar);
}

QAction *MainWindow::addToolBarButton(QFunctionPointer callback, QString btnName, QIcon &&icon){
    QAction *t = toolBar->addAction(icon, btnName);
    connect(t, &QAction::triggered, callback);
    return t;
}

void MainWindow::addToolBarSpacer(){
    QWidget *spacer  = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar->addWidget(spacer);
}

QShortcut *MainWindow::addShortcut(QFunctionPointer callback, QKeySequence &&seq){
    QShortcut *sh = new QShortcut(seq, this);
    connect(sh, &QShortcut::activated, callback);
    return sh;
}

MainWindow::~MainWindow(){
}

