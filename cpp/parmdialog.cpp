#include "parmdialog.h"
#include "typedialog.h"
#include "parmstore.h"

#include <iostream>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

awv::ParmDialog::
ParmDialog(const std::string& model_name, QWidget* parent) : QDialog(parent)
{
    std::cout << "awv::ParmDialog::ctor" << std::endl;
    type_dialog_ = 0;
    file_dialog_ = 0;

//  this->setStyleSheet("QDialog{background-color: rgb(255, 245, 179);}");
    QVBoxLayout* main_layout = new QVBoxLayout();
    main_layout->setSpacing(10);

    QString qs(model_name.c_str() );
    QString title = "Parameters for " + qs;
    parm_group_ = new QGroupBox(title, this);
    parm_group_->setStyleSheet(
        "QGroupBox{"
            "background-color: lightblue;"
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
    QGridLayout* parm_layout = new QGridLayout;
    parm_group_->setLayout(parm_layout);

    setStyleSheet(
            "QDialog{"
                "background-color: rgb(255, 246, 179);"
            "}"
            "QPushButton#button01{"
                 "background-color: moccasin;"
                 "border-top-style: solid;"
                 "border-left-style: solid;"
                 "border-right-style: none;"
                 "border-bottom-style: none;"
                 "border-color: grey;"
                 "border-width: 4px;"
                 "font: bold 11px;"
                 "min-width: 8em;"
                 "padding: 2px;"
            "}"
            "QLineEdit{"
                  "background: yellow;"
            "}"
            "QLineEdit:read-only{"
                  "background: white;"
            "}"
    );

    QPushButton* type_b = new QPushButton("Model Type", parm_group_);
    QPushButton* dir_b  = new QPushButton("Model Dir" , parm_group_);
    QLabel* nt_l        = new QLabel("NT", parm_group_);
    QLabel* nx_l        = new QLabel("NX", parm_group_);
    QLabel* nz_l        = new QLabel("NZ", parm_group_);
    QLabel* dt_l        = new QLabel("DT", parm_group_);
    QLabel* dh_l        = new QLabel("DH", parm_group_);
    type_e_             = new QLineEdit(parm_group_);
    dir_e_              = new QLineEdit(parm_group_);
    nt_e_               = new QLineEdit(parm_group_);
    nx_e_               = new QLineEdit(parm_group_);
    nz_e_               = new QLineEdit(parm_group_);
    dt_e_               = new QLineEdit(parm_group_);
    dh_e_               = new QLineEdit(parm_group_);

    for ( int i = 0; i < 11; i +=2) {
        parm_layout->setColumnMinimumWidth(i    , 50);
        parm_layout->setColumnMinimumWidth(i + 1, 10);
    }
    parm_layout->addWidget(type_b,  0, 0, 1, 3);
    parm_layout->addWidget(type_e_, 0, 4, 1, 3);
    parm_layout->addWidget(dir_b ,  1, 0, 1, 3);
    parm_layout->addWidget(dir_e_ , 1, 4, 1, 7);
    parm_layout->addWidget(nt_l  ,  2, 0, 1, 1);
    parm_layout->addWidget(nt_e_ ,  2, 2, 1, 3);
    parm_layout->addWidget(dt_l  ,  2, 6, 1, 1);
    parm_layout->addWidget(dt_e_ ,  2, 8, 1, 3);
    parm_layout->addWidget(nx_l  ,  3, 0, 1, 1);
    parm_layout->addWidget(nx_e_ ,  3, 2, 1, 3);
    parm_layout->addWidget(dh_l  ,  3, 6, 1, 1);
    parm_layout->addWidget(dh_e_ ,  3, 8, 1, 3);
    parm_layout->addWidget(nz_l  ,  4, 0, 1, 1);
    parm_layout->addWidget(nz_e_ ,  4, 2, 1, 3);

    type_e_->setText("Press button to select");
    dir_e_->setText("Press button to select");
    type_e_->setReadOnly(true);
    dir_e_->setReadOnly(true);
    type_b->setAutoDefault(false);
    dir_b->setAutoDefault(false);

    connect(type_b, SIGNAL(pressed() ),        this, SLOT(type_pressed() ) );
    connect(dir_b , SIGNAL(pressed() ),        this, SLOT(dir_pressed() ) );
    connect(nt_e_,  SIGNAL(returnPressed() ), this, SLOT(nt_entered() ) );
    connect(nx_e_,  SIGNAL(returnPressed() ), this, SLOT(nx_entered() ) );
    connect(nz_e_,  SIGNAL(returnPressed() ), this, SLOT(nz_entered() ) );
    connect(dt_e_,  SIGNAL(returnPressed() ), this, SLOT(dt_entered() ) );
    connect(dh_e_,  SIGNAL(returnPressed() ), this, SLOT(dh_entered() ) );

    QGroupBox* button_group    = new QGroupBox(this);
    QHBoxLayout* button_layout = new QHBoxLayout;
    QPushButton* accept_b      = new QPushButton("Accept", button_group);
    QPushButton* cancel_b      = new QPushButton("Cancel", button_group);
    accept_b->setAutoDefault(false);
    cancel_b->setAutoDefault(false);
    accept_b->setObjectName("button01");
    cancel_b->setObjectName("button01");
    button_layout->addWidget(accept_b);
    button_layout->addWidget(cancel_b);
    connect( accept_b, SIGNAL( clicked() ),this, SLOT(accepted() ) );
    connect( cancel_b, SIGNAL( clicked() ),this, SLOT(canceled() ) );
    button_group->setLayout(button_layout);

    main_layout->addWidget(parm_group_);
    main_layout->addWidget(button_group);
    setLayout(main_layout);

    parm_store_ = ParmStore::instance();
    parm_store_->open(model_name);
    resize( 400, 300);
    move  ( 100,0);
}

awv::ParmDialog::
~ParmDialog()
{
}

void
awv::ParmDialog::
type_pressed()
{
    std::cout << "awv::ParmDialog::type_pressed" << std::endl;
    if ( !type_dialog_ ) {
        type_dialog_ = new TypeDialog(this);
        connect(type_dialog_, SIGNAL(accepted() ), this, SLOT(type_accepted() ) );
    }
    type_dialog_->show();
    type_dialog_->raise();
    type_dialog_->activateWindow();
}

void
awv::ParmDialog::
type_accepted()
{
    std::cout << "Type Accepted" << std::endl;
    model_type_ = type_dialog_->model_type();
    type_e_ ->setText(model_type_.c_str() );
    parm_store_->model_type(model_type_);
}

void
awv::ParmDialog::
dir_pressed()
{
    std::cout << "Dir Pressed" << std::endl;
    if( !file_dialog_ ) {
        file_dialog_ = new QFileDialog(this);
        file_dialog_->setFileMode(QFileDialog::Directory);
        connect(file_dialog_, SIGNAL(accepted() ), this, SLOT(dir_accepted() ) );
    }
    file_dialog_->show();
    file_dialog_->raise();
    file_dialog_->activateWindow();
}

void
awv::ParmDialog::
dir_accepted()
{
    std::cout << "Dir Accepted" << std::endl;
    QDir qd = file_dialog_->directory();
    QString qs = qd.absolutePath();
    model_dir_ = qs.toStdString();
    dir_e_->setText(model_dir_.c_str() );
    parm_store_->model_dir(model_dir_);
}

void
awv::ParmDialog::
nt_entered()
{
    std::cout << "awv::ParmDialog::nt_entered" << std::endl;
    QString qs = nt_e_->text();
    bool    ok;
    int nt     = qs.toInt(&ok);
    if ( !ok ) {
        nt_e_->clear();
        nt = 0;
    } 
    parm_store_->nt(nt);
}


void
awv::ParmDialog::
nx_entered()
{
    std::cout << "awv::ParmDialog::nx_entered" << std::endl;
    QString qs = nx_e_->text();
    bool    ok;
    int nx     = qs.toInt(&ok);
    if ( !ok ) {
        nx_e_->clear();
        nx = 0;
    } 
    parm_store_->nx(nx);
}

void
awv::ParmDialog::
nz_entered()
{
    std::cout << "awv::ParmDialog::nz_entered" << std::endl;
    QString qs = nz_e_->text();
    bool    ok;
    int nz     = qs.toInt(&ok);
    if ( !ok ) {
        nz_e_->clear();
        nz = 0;
    } 
    parm_store_->nz(nz);
}

void
awv::ParmDialog::
dt_entered()
{
    std::cout << "awv::ParmDialog::dt_entered" << std::endl;
    QString qs = dt_e_->text();
    bool    ok;
    float dt     = qs.toFloat(&ok);
    if ( !ok ) {
        dt_e_->clear();
        dt = 0.0;
    } 
    parm_store_->dt(dt);
}

void
awv::ParmDialog::
dh_entered()
{
    std::cout << "awv::ParmDialog::dh_entered" << std::endl;
    QString qs = dh_e_->text();
    bool    ok;
    float dh     = qs.toFloat(&ok);
    if ( !ok ) {
        dh_e_->clear();
        dh = 0.0;
    } 
    parm_store_->dh(dh);
}

void
awv::ParmDialog::
accepted()
{
    std::cout << "awv::ParmDialog::accepted()" << std::endl;
    parm_store_->save();
    done(QDialog::Accepted);
}

void
awv::ParmDialog::
canceled()
{
    std::cout << "awv::ParmDialog::canceled()" << std::endl;
    done(QDialog::Rejected);
}

void
awv::ParmDialog::
refresh()
{
    std::cout << "awv::ParmDialog::refresh" << std::endl;
    QString qs;
    std::string s;
    s = parm_store_->model_type();
    type_e_->setText(s.c_str() );
    s = parm_store_->model_dir();
    dir_e_->setText(s.c_str() );
    nt_e_->setText(qs.setNum(parm_store_->nt() ) );
    nx_e_->setText(qs.setNum(parm_store_->nx() ) );
    nz_e_->setText(qs.setNum(parm_store_->nz() ) );
    dt_e_->setText(qs.setNum(parm_store_->dt() ) );
    dh_e_->setText(qs.setNum(parm_store_->dh() ) );
}
    
