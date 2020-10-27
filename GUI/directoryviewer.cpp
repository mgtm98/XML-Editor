#include "directoryviewer.h"
DirectoryViewer::DirectoryViewer(QWidget *parent):DirectoryViewer("/",parent){
}

#include <QDebug>

DirectoryViewer::DirectoryViewer(QString path, QWidget *parent):QTreeView(parent){
    fmodel = new QFileSystemModel(this);
    fmodel->setRootPath(path);
    this->setModel(fmodel);
    this->setAnimated(true);
    this->setIndentation(15);
    this->setRootIndex(fmodel->index(path));
    this->setSortingEnabled(false);
    for (int i = 1; i < fmodel->columnCount(); ++i)
        this->hideColumn(i);
    this->header()->hide();



    QFile configFile(QString(CONFIG_PATH)+"config.txt");
    qDebug() << QGuiApplication::platformName();
    if(configFile.exists()){
        configFile.open(QIODevice::ReadWrite);
        workspacePath = configFile.readLine();
        configFile.close();
    }else{
        QString path = QFileDialog::getExistingDirectory(this,tr("Select Workspace"), "/");
        configFile.open(QIODevice::ReadWrite);
        configFile.write(path.toUtf8());
        configFile.close();
        workspacePath = path;
    }
    if(workspacePath.endsWith("\n")){
        workspacePath.chop(1);
    }
    this->setRoot(workspacePath);

    connect(this, &QTreeView::doubleClicked, this, &DirectoryViewer::onDoubleClicked);

}

void DirectoryViewer::setHeader(QString title){
    fmodel->setHeaderData(0,Qt::Horizontal,title);
     this->header()->show();
}

void DirectoryViewer::setRoot(QString path){
    fmodel->setRootPath(path);
    this->setRootIndex(fmodel->index(path));
}

QString DirectoryViewer::getWorkpath(){
    return workspacePath;
}

void DirectoryViewer::onDoubleClicked(const QModelIndex &i){
    QString path = fmodel->filePath(i);
    emit DirectoryViewer::doubleClicked(path);
}
