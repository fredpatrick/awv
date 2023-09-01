#include "cmainwindow.h"

#include <iostream>
#include <string>

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QSize>
#include <QRect>

awv::CMainWindow::
CMainWindow(QWidget* )
{
    resize(200,600);
    QWidget* central_widget  = new QWidget(this);
    setCentralWidget(central_widget);
    QGroupBox* m_group    = new QGroupBox("Test Box", central_widget);
//  m_group->setAlignment(Qt::AlignHCenter);
    m_group->setStyleSheet(
        "QGroupBox{"
            "background-color: rgb(238, 232,170);"
            "border: 4px black;"
            "border-style: solid;"
            "margin-top: 1ex;"
       "}"
       "QGroupBox::title{"
            "background-color: white;"
            "subcontrol-origin: margin; "
            "subcontrol-position: top center; "
            "padding: 0 3px 0 3px;"
       "}"
    );
/*
    QGroupBox* m_group    = new QGroupBox("Test Box", central_widget);
    m_group->setStyleSheet("QGroupBox::title{background-color green;subcontrol-origin: margin; subcontrol-position: top center; padding: 0 3px;}");
*/
    QVBoxLayout* m_layout = new QVBoxLayout;

    QGroupBox*   c_group  = new QGroupBox(m_group);
    c_group->setStyleSheet("background-color: yellow;border: 2px red;border-style: solid");
    QString cs = " background-color: yellow;"
                 " border: 2px red;"
                 " border-style: solid";

    QHBoxLayout* c_layout = new QHBoxLayout;
    c_layout->setSpacing(0);

    QLabel*    text_l = new QLabel("Text", c_group);
    text_l->setStyleSheet("border: none;");
    QLineEdit* text_e = new QLineEdit(c_group);
    text_e->setStyleSheet("background: lightblue;border: 2px black; border-style: solid;");
    QPushButton* bb   = new QPushButton("PushMe", c_group);
    bb->setStyleSheet(
            "QPushButton{"
                 "background-color: gold;"
                 "border-top-style: solid;"
                 "border-left-style: solid;"
                 "border-right-style: none;"
                 "border-bottom-style: none;"
                 "border-color: grey;"
                 "border-width: 4px;"
                 "font: bold 14px;"
                 "min-width: 10em;"
                 "padding: 6px;"
            "}"
    );
    c_layout->addWidget(text_l);
    c_layout->addSpacing(20);
    c_layout->addWidget(text_e);
    c_layout->addSpacing(50);
    c_layout->addWidget(bb);

    connect(text_e, SIGNAL(returnPressed() ), this, SLOT(text_entered() ) );
    connect(bb    , SIGNAL( clicked() ),      this, SLOT(pushme_pressed() ) );

    c_group->setLayout(c_layout);

    m_layout->addWidget(c_group);
    m_layout->addStretch(50);
    m_group->setLayout(m_layout);
    resize(500,300);
    QSize sz = bb->size();
    std::cout << "awv::CMainWindow-ctor, height = " << sz.height() << 
                                         ", width = " << sz.width() << std::endl;
    QFont f = bb->font();
    std::cout << "awv::CMainWindow-ctor, font size = " << f.pointSize() << std::endl;
    QString qs = f.family();
    std::string s = qs.toStdString();
    std::cout << "awv::CMainWindow-ctor, family    = " << s << std::endl;
    bb->setFixedSize(200,40);
}

awv::CMainWindow::
~CMainWindow()
{
}

void
awv::CMainWindow::
text_entered()
{
    std::cout << "awv::CMainWindow::text_entered = " << std::endl;
}

void
awv::CMainWindow::
pushme_pressed()
{
    std::cout << "awv::CMainWindow::pushme_pressed" << std::endl;
}
