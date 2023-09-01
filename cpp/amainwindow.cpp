#include "amainwindow.h"
#include "namedialog.h"
#include "parmdialog.h"
#include "parmstore.h"
#include "materialdialog.h"
#include "materialstore.h"

#include <iostream>

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QGroupBox>

awv::AMainWindow::
AMainWindow(QWidget* )
{
    resize(813,600);
    central_widget_ = new QGroupBox(this);
    setCentralWidget(central_widget_);
    central_widget_->setStyleSheet(
        "background-color: rgb(255, 245, 179);");

    QMenuBar* menu_bar = new QMenuBar();
    menu_bar->setGeometry(QRect(0, 0, 813,19) );
    setMenuBar(menu_bar);

    QMenu*   menu_file        = menu_bar->addMenu("File");
    QMenu*   menu_model       = menu_bar->addMenu("Model");
    exit_action_              = menu_file->addAction("Exit");
    name_action_              = menu_model->addAction("Model Name");
    edit_action_              = menu_model->addAction("Edit Parameters");
    material_action_          = menu_model->addAction("Edit Materials");
//  QAction* load_action      = menu_model->addAction("Load Parms");
//  print_action_ = menu_model->addAction("Print");

    connect(exit_action_,     SIGNAL(triggered() ), this, SLOT(exit() ) );
    connect(name_action_,     SIGNAL(triggered() ), this, SLOT(get_modelname() ) );
    connect(edit_action_,     SIGNAL(triggered() ), this, SLOT(edit_parameters() ) );
    connect(material_action_, SIGNAL(triggered() ), this, SLOT(edit_materials() ) );

    edit_action_->setEnabled(false);
    material_action_->setEnabled(false);
    parm_dialog_      = 0;
    name_dialog_      = 0;
    material_dialog_  = 0;
    parm_store_       = ParmStore::instance();
    material_store_   = MaterialStore::instance();
}

awv::AMainWindow::
~AMainWindow()
{
}

void
awv::AMainWindow::
get_modelname()
{
    std::cout << "awv::AMainWindow::get_modelname" << std::endl;
    if ( !name_dialog_ ) {
        name_dialog_ = new NameDialog(this);
        connect(name_dialog_, SIGNAL(accepted() ), this, SLOT(name_accepted() ) );
    }
    name_dialog_->show();
    name_dialog_->raise();
    name_dialog_->activateWindow();
}

void
awv::AMainWindow::
name_accepted()
{
    std::cout << "awv::AMainWindow::name_accepted" << std::endl;
    model_name_ = name_dialog_->model_name();
    std::cout << "awv::AMainWindow::name_accepted, material and property stores opened()" <<
                                 std::endl;
    edit_action_->setEnabled(true);
    material_action_->setEnabled(true);
    std::cout << "awv::AMainWindow::name_accepted, edit parms and materials enabled" << 
                                                             std::endl;
}

void
awv::AMainWindow::
edit_parameters()
{
    std::cout << "awv::AMainWindow::edit_parameters" << std::endl;
    if ( !parm_dialog_ ) {
        parm_dialog_ = new ParmDialog(model_name_, this);
        connect(parm_dialog_, SIGNAL(accepted() ), this, SLOT(parm_accepted() ) );
        connect(parm_dialog_, SIGNAL(rejected() ), this, SLOT(parm_rejected() ) );
    }
    parm_dialog_->refresh();
    parm_dialog_->show();
    parm_dialog_->raise();
    parm_dialog_->activateWindow();
}

void
awv::AMainWindow::
parm_accepted()
{
    delete parm_dialog_;
    parm_dialog_ = nullptr;
}

void
awv::AMainWindow::
parm_rejected()
{
    delete parm_dialog_;
    parm_dialog_ = nullptr;
}

void
awv::AMainWindow::
edit_materials()
{
    std::cout << "awv::AMainWindow::edit_materials" << std::endl;
    if ( !material_dialog_ ) {
        material_dialog_ = new MaterialDialog(model_name_, this);
        connect(material_dialog_, SIGNAL(accepted() ), this, SLOT(material_accepted() ) );
        connect(material_dialog_, SIGNAL(rejected() ), this, SLOT(material_rejected() ) );
    }
    material_dialog_->show();
    material_dialog_->raise();
    material_dialog_->activateWindow();
    std::cout << "awv::AMainWindow::editmaterials - ready to do work" << std::endl;
}

void
awv::AMainWindow::
material_accepted()
{
    delete material_dialog_;
    material_dialog_ = nullptr;
}

void
awv::AMainWindow::
material_rejected()
{
    delete material_dialog_;
    material_dialog_ = nullptr;
}

void
awv::AMainWindow::
exit()
{
    std::cout <<  "awv::AMainWindow::exit()" << std::endl;
    close();
}

/*
void
awv::AMainWindow::
print()
{
    std::cout <<  "awv::AMainWidow::print()" << std::endl;
    ModelNamesStore* mstore = ModelNamesStore::instance();
    mstore->print();
}
*/
