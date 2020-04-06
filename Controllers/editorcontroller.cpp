#include "editorcontroller.h"

MainWindow *EditorController::main;
QMap <QString, EditorController::EditorFile*> EditorController::activeFiles;

void EditorController::registerMainWindow(MainWindow *m){
    main = m;
}

void EditorController::addEditor(QString path){
    QString name = path.mid(path.lastIndexOf("/")+1, path.size());
    QString type = path.mid(path.lastIndexOf(".")+1, path.size()-path.lastIndexOf("."));
    if(!path.compare(type)) type = "";
    if(type.size()) name = name.mid(0,name.size()-type.size()-1);

    QString tabName;
    if(type.size() == 0) tabName = name;
    else tabName = name + "." + type;

    QDir dir(path);
    if(!dir.exists()){
        QFile f(path);
        f.open(QIODevice::Text | QIODevice::ReadOnly);
        QString content = f.readAll();
        f.close();
        Editor *e = new Editor(Highlighter(type), main);
        int tabIndex = main->editorTabWidget->addTab(e,tabName);
        main->editorTabWidget->setTabIcon(tabIndex, Icon(type));
        e->setPlainText(content);
        EditorFile *eFile = new EditorFile();
        eFile->editor = e;
        eFile->filePath = path;
        activeFiles.insert(tabName,eFile);
        setSyntaxController(type,e);
    }
}

void EditorController::closeEditor(int index){
    QString editorName = main->editorTabWidget->tabText(index);
     main->editorTabWidget->removeTab(index);
    delete activeFiles.value(editorName);
    activeFiles.remove(editorName);
}

EditorController::EditorFile EditorController::getActiveEditorFile(){
    EditorFile ef;
    if(main->editorTabWidget->currentIndex() > -1){
        QString activeFile = main->editorTabWidget->tabText(main->editorTabWidget->currentIndex());
        ef.filePath = activeFiles.value(activeFile)->filePath;
        ef.editor = activeFiles.value(activeFile)->editor;
    }
    return ef;
}

QPixmap EditorController::Icon(QString &type){
    if(!type.compare("py")){
        return QPixmap(":/icons/icons/python.png");
    }else if(!type.compare("xml")){
        return QPixmap(":/icons/icons/xmlIcon.png");
    }else{
        return QPixmap(":/icons/icons/txt.png");
    }
}

QSyntaxHighlighter* EditorController::Highlighter(QString &type){
    if(!type.compare("py")){
        return new class::PythonHighlighter();
    }else if(!type.compare("xml")){
        return new XMLHighlighter;
    }else{
        return nullptr;
    }
}

void EditorController::setSyntaxController(QString &type, Editor *e){
    if(!type.compare("xml")){
        XMLController *controller = new XMLController(e);
        connect(e, &Editor::textChanged, controller, &XMLController::onTextChanged);
        qDebug() << "Registerd";
    }
}
