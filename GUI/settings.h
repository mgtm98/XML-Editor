#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QFormLayout>
#include <QWidget>
#include <QIcon>
#include <QPushButton>

class Settings : public QDialog{
public:
    Settings();
private:
    QFormLayout *mainLayout;
    QPushButton *setWorkSpaceBtn;
};

#endif // SETTINGS_H
