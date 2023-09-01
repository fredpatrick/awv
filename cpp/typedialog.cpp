#include "typedialog.h"
#include "buildermanager.h"

#include <iostream>
#include <vector>

#include <QGroupBox>
#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>

awv::TypeDialog::
TypeDialog(QWidget* parent) : QDialog(parent)
{
    std::cout <<  "awv::TypeDialog::ctor: " << std::endl;
    QGroupBox*   list_group  = new QGroupBox("Select Model Type", this);
    QVBoxLayout* list_layout = new QVBoxLayout;

    QListWidget* type_list = new QListWidget(list_group);
    list_layout->addWidget(type_list);

    list_group->setLayout(list_layout);

    connect( type_list, SIGNAL(itemClicked(QListWidgetItem*) ),
             this     , SLOT(type_selected(QListWidgetItem*) ) );
    
    BuilderManager* bmgr = BuilderManager::instance();
    std::vector<std::string> ts = bmgr->types();
    int n = 0;
    for ( auto p = ts.begin(); p != ts.end(); ++p) {
        std::string s = *p;
        std::cout << "awv::TypeDialog::ctor: n = " << n << " " << s << std::endl;
        QListWidgetItem* item = new QListWidgetItem(s.c_str() );
        type_list->addItem(item);
        n+=1;
    }
    resize( 200, 200);
    move  ( 100, 0);
}

awv::TypeDialog::
~TypeDialog()
{
}

void
awv::TypeDialog::
type_selected(QListWidgetItem* item)
{
    QString qs  = item->text();
    model_type_ = qs.toStdString();
    std::cout << "awv::TypeDialog::type_selected, model_type = " << model_type_ << std::endl;
    done(QDialog::Accepted);
}

std::string
awv::TypeDialog::
model_type()
{
    return model_type_;
}
