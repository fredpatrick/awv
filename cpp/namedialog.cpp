#include "namedialog.h"
#include "parmstore.h"

#include <iostream>
#include <string>
#include <vector>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

awv::NameDialog::
NameDialog(QWidget* parent) : QDialog(parent)
{
    std::cout  << "awv::NameDialog::ctor" << std::endl;
    model_name_   = "";

    QGroupBox*   main_group    = new QGroupBox("Select Model Name for Session", this);
    main_group->setStyleSheet(
        "QGroupBox{"
            "background-color: wheat;"
            "border: 2px black;"
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
    QVBoxLayout* main_layout   = new QVBoxLayout;
    main_layout->setSpacing(0);

    name_label_ = new QLabel("Name", this);
    name_edit_  = new QLineEdit(this);
    name_list_  = new QListWidget(this);
    main_layout->addWidget(name_label_);
    main_layout->addWidget(name_edit_);
    main_layout->addWidget(name_list_);

    connect(name_edit_, SIGNAL(returnPressed() ), 
            this,      SLOT  (name_entered() ) );
    connect(name_list_, SIGNAL(itemClicked(QListWidgetItem*) ), 
            this,      SLOT  (name_selected(QListWidgetItem*) ) );

    name_edit_->setPlaceholderText("Type or select name");

    ParmStore* mnstore = ParmStore::instance();
    std::vector<std::string> mns = mnstore->names();
    int l = mns.size();
    std::cout << "awv::ParmDialog:ctor- #of names = " << l << std::endl;
    int n = 0;
    for ( auto p = mns.begin(); p != mns.end(); ++p) {
        std::string s = *p;
        std::cout << "awv::NameDialog::ctor: n = " << n << " " << s << std::endl;
        QListWidgetItem* item = new QListWidgetItem(s.c_str() );
        name_list_->addItem(item);
        n+=1;
    }

    
    main_group->setLayout(main_layout);

    resize( 200, 200);
    move  ( 100, 0);
}

awv::NameDialog::
~NameDialog()
{
}

std::string
awv::NameDialog::
model_name()
{
    return model_name_;
}

void 
awv::NameDialog::
name_entered()
{
    std::cout << "awv::NamsDialog::name_entered()-0" << std::endl;

    QString          name_s = name_edit_->text();
    name_edit_->clear();
    std::string      s      = name_s.toStdString();
    model_name_             =s;
    ParmStore* parm_store = ParmStore::instance();
    if ( parm_store->name_exists(s) ) {
        std::cout << "awv::NameDialog::name_entered()-1, " << s << 
                                                 " added to store" << std::endl;
        QListWidgetItem* item   = new QListWidgetItem( s.c_str());
        name_list_->addItem(item);
        name_edit_->insert(model_name_.c_str() );
        std::cout << "awv::NameDialog::name_entered()-2" << std::endl;
    } else {
        std::cout << "Error duplicate name in store: " << s << std::endl;
        name_edit_->setPlaceholderText("Type or select name");
    }
    done(QDialog::Accepted);
}

void 
awv::NameDialog::
name_selected(QListWidgetItem* item)
{
    QString     qs = item->text();
    std::string nm = qs.toStdString();
    std::cout << "awv::NameDialog::item_selected: name = " << nm << std::endl;
    model_name_ = nm;
    name_edit_->insert(model_name_.c_str() );
    done(QDialog::Accepted);              // Send accepted() signal
}
