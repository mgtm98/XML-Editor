#include "editorcontroller.h"

MainWindow *EditorController::main;
QMap <QString, EditorController::EditorFile*> EditorController::activeFiles;

void EditorController::registerMainWindow(MainWindow *m){
    main = m;
}

bool EditorController::addEditor(QString path){
    main->setCursor(Qt::WaitCursor);
    QString name = path.mid(path.lastIndexOf("/")+1, path.size());
    QString type = path.mid(path.lastIndexOf(".")+1, path.size()-path.lastIndexOf("."));
    if(!path.compare(type)) type = "";
    if(type.size()) name = name.mid(0,name.size()-type.size()-1);

    QString tabName;
    if(type.size() == 0) tabName = name;
    else tabName = name + "." + type;

    if(activeFiles.contains(tabName)) return false;
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
        setSyntaxController(type,e,eFile);
    }
    main->setCursor(Qt::ArrowCursor);
    return true;
}

void EditorController::closeEditor(int index){
    QString editorName = main->editorTabWidget->tabText(index);
    main->editorTabWidget->removeTab(index);
    LangController *cont = activeFiles.value(editorName)->langController;
    if(cont != nullptr) delete cont;
    delete activeFiles.value(editorName);
    activeFiles.remove(editorName);
}

EditorController::EditorFile EditorController::getActiveEditorFile(){
    EditorFile ef;
    if(main->editorTabWidget->currentIndex() > -1){
        QString activeFile = main->editorTabWidget->tabText(main->editorTabWidget->currentIndex());
        ef.filePath = activeFiles.value(activeFile)->filePath;
        ef.editor = activeFiles.value(activeFile)->editor;
        ef.langController = activeFiles.value(activeFile)->langController;
    }
    return ef;
}

QPixmap EditorController::Icon(QString &type){
    if(!type.compare("py")){
        return QPixmap(":/icons/icons/python.png");
    }else if(!type.compare("xml")){
        return QPixmap(":/icons/icons/xml.svg");
    }else if(!type.compare("json")){
        return QPixmap(":/icons/icons/json.svg");
    }else{
        return QPixmap(":/icons/icons/txt.png");
    }
}

QSyntaxHighlighter* EditorController::Highlighter(QString &type){
    if(!type.compare("py")){
        return new class::PythonHighlighter();
    }else if(!type.compare("xml")){
        return new XMLHighlighter;
    }else if(!type.compare("json")){
        return new JSONHighlighter;
    }else{
        return nullptr;
    }
}

void EditorController::setSyntaxController(QString &type, Editor *e, EditorFile *efile){
    if(!type.compare("xml")){
        XMLController *controller = new XMLController(e, efile->filePath);
        efile->langController = controller;
        e->setTabWidth(3);
        main->status->showMessage("Synsets Number : " + QString::number(controller->getSynsetNumber()), 10000);
        connect(e, &Editor::textChanged, controller, &XMLController::onTextChanged);
        connect(e, &Editor::beautify, controller, &XMLController::beautify);
        connect(e, &Editor::minify, controller, &XMLController::minify);
        connect(e, &Editor::showSynsetInfo, controller, &XMLController::showSynsetInfo);
        connect(e, &Editor::convertToJson, controller, &XMLController::convert2JSON);
    }
}

