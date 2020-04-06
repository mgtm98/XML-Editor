#include "guiController.h"

MainWindow *GUIContoller::main;

void GUIContoller::registerMainWindow(MainWindow *m){
    main = m;
    start();
}

void GUIContoller::start(){
    main->addToolBarButton(&newFile, "New",  QPixmap(":/icons/icons/new.png"));
    main->addToolBarButton(&openFolder, "Open",  QPixmap(":/icons/icons/open.png"));
    main->addToolBarButton(&saveFile, "Save",  QPixmap(":/icons/icons/save.png"));
    main->addToolBarSpacer();
    main->addToolBarButton(&showSettings, "Settings",  QPixmap(":/icons/icons/Settings.png"));

    main->addShortcut(&newFile, QKeySequence("Ctrl+n"));
    main->addShortcut(&openFolder, QKeySequence("Ctrl+o"));
    main->addShortcut(&saveFile, QKeySequence("Ctrl+s"));

    connect(main->dirViewer, &DirectoryViewer::doubleClicked, &openFile);
    connect(main->editorTabWidget, &QTabWidget::tabCloseRequested, &EditorController::closeEditor);

}

void GUIContoller::openFolder(){
    QString path = QFileDialog::getExistingDirectory(main, ("Open Workspace"), main->dirViewer->getWorkpath());
    if(!path.compare("")) main->dirViewer->setRoot(main->dirViewer->getWorkpath());
    else main->dirViewer->setRoot(path);
}

void GUIContoller::newFile(){
    QString path = QFileSystemModel().filePath(main->dirViewer->currentIndex());
    if (!QFileInfo(path).isDir()) path = QFileInfo(path).dir().path();
    bool ok;
    QString newFileName = QInputDialog::getText(main, "Create new File", "Name :", QLineEdit::Normal, "newFile", &ok);
    if(ok){
        QFile f (path+"/"+newFileName);
        f.open(QIODevice::WriteOnly);
        f.close();
    }
    EditorController::addEditor(path+"/"+newFileName);
}

void GUIContoller::openFile(QString path){
    EditorController::addEditor(path);
}

void GUIContoller::saveFile(){
    EditorController::EditorFile ef = EditorController::getActiveEditorFile();
    if(ef.editor != nullptr){
         QFile f(ef.filePath);
         if(f.open(QIODevice::WriteOnly)){
             f.write(ef.editor->toPlainText().toUtf8());
             f.close();
             main->status->showMessage("File Saved",2000);
         }
    }
}

void GUIContoller::showSettings(){
    Settings *s = new Settings();
    s->show();
}
