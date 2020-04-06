#include "settings.h"

Settings::Settings(){
    mainLayout = new QFormLayout();
    setWorkSpaceBtn = new QPushButton("Browse");

    this->setFixedSize(500,200);
    this->setWindowTitle("XML IDE Settings");
    this->setWindowIcon(QIcon(":/icons/Settings.png"));

    this->setLayout(mainLayout);
    mainLayout->addRow("Set Work Space   ", setWorkSpaceBtn);
}
