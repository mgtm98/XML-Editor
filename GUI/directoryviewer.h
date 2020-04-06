#ifndef DIRECTORYVIEWER_H
#define DIRECTORYVIEWER_H

#define CONFIG_PATH ""

#include <QTreeView>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QFileDialog>


class DirectoryViewer : public QTreeView{
    Q_OBJECT
public:
    DirectoryViewer(QWidget *parent = nullptr);
    DirectoryViewer(QString path, QWidget *parent = nullptr);
    void setHeader(QString);
    void setRoot(QString);
    QString getWorkpath();

signals:
    void doubleClicked(QString);

private:
    QFileSystemModel *fmodel;
    QString workspacePath;
    void onDoubleClicked(const QModelIndex&);
};

#endif // DIRECTORYVIEWER_H
