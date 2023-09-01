#include "bmainwindow.h"

#include <iostream>

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLayoutItem>
#include <QCheckBox>
#include <QButtonGroup>

awv::BMainWindow::
BMainWindow(QWidget* )
{
    resize(200,600);
    QWidget* central_widget  = new QWidget(this);
    setCentralWidget(central_widget);

    QGridLayout* cb_layout = new QGridLayout;
    cb_layout->setSpacing(0);

    QButtonGroup* button_group = new QButtonGroup();

    QCheckBox* cb_0 = new QCheckBox(central_widget);
    cb_layout->addWidget(cb_0, 0, 0);
    button_group->addButton(cb_0, 0);
    cb_0->setVisible(false);
    cb_0->setChecked(true);

    QCheckBox* cb_1 = new QCheckBox(central_widget);
    cb_layout->addWidget(cb_1, 1, 0);
    button_group->addButton(cb_1, 1);

    QCheckBox* cb_2 = new QCheckBox(central_widget);
    cb_layout->addWidget(cb_2, 2, 0);
    button_group->addButton(cb_2, 2);

    QCheckBox* cb_3 = new QCheckBox(central_widget);
    cb_layout->addWidget(cb_3, 3, 0);
    button_group->addButton(cb_3, 3);

    central_widget->setLayout(cb_layout);

    connect( button_group, SIGNAL( idToggled(int, bool) ),
             this,         SLOT( button_toggled(int, bool) ) );
    std::cout << "QCheckBox size = " << cb_1->width() << ", " << cb_1->height() << std::endl;
    QLayoutItem* item = cb_layout->itemAtPosition(2, 0);
    QWidget*     w    = item->widget();
    QCheckBox* p =  dynamic_cast<QCheckBox*>(w);
    if ( !p->isChecked() ) std::cout << " checkbox is not checked" << std::endl;
}

awv::BMainWindow::
~BMainWindow()
{
}

void
awv::BMainWindow::
button_toggled(int id, bool state)
{
    std::cout << "awv::BMainWindow::button_taggled, id = " << 
                             id << " state = " << state << std::endl;
}
