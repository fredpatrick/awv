#include "materialdialog.h"
#include "materialstore.h"

#include <iostream>
#include <utility>

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QButtonGroup>

awv::MaterialDialog::
MaterialDialog(const std::string& model_name, QWidget* parent) : QDialog(parent)
{
    std::cout << "awv::MaterialDialog-ctor" << std::endl;

    QString       title       = "Materials for " + QString(model_name.c_str() );
    QGroupBox*    main_group  = new QGroupBox(title, this);
    std::cout << "addressof main_group = " << std::addressof(main_group) << std::endl;
    main_group->setStyleSheet(
        "QGroupBox{"
            "background-color: rgb(255, 245, 179);"
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

    setStyleSheet(
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
            /*
            "QCheckBox::indicator::checked{"
                "width: 10px;"
                "height: 10px;"
                "border-width: 1px;"
                "border-style: solid;"
                "border-color: black;"
                "background-color none;"
                "color: black;"
                "image: url(:/images/checkbox_checked.png);"
            "}"
            */
    );
    main_group->resize(600,300);
    QVBoxLayout*  main_layout  = new QVBoxLayout;
    
    scroll_area_               = new QScrollArea(main_group);
    scroll_bar_                = scroll_area_->verticalScrollBar();
    scroll_bar_->setTracking(false);
    connect(scroll_bar_, SIGNAL(valueChanged(int) ), this, SLOT(value_changed(int) ) );
    connect(scroll_bar_, SIGNAL(sliderMoved(int) ), this, SLOT(slider_moved(int) ) );
    scroll_group_              = new QGroupBox(main_group);
    scroll_layout_             = new QVBoxLayout;
    material_group_            = new QGroupBox(main_group);
    scroll_group_->setStyleSheet( 
            "QGroupBox{"
                 "background-color: lightblue;"
                 "border: 2px black;"
                 "border-style: solid;"
                 "margin: 1ex;"
            "}"
    );

    material_group_->setStyleSheet( 
            "QGroupBox{"
                 "background-color: lightblue;"
                 "border-style: none;"
            "}"
    );

    material_layout_           = new QGridLayout;
    material_layout_->setSizeConstraint(QLayout::SetMinAndMaxSize);
    button_group_              = new QButtonGroup;
    button_group_->setExclusive(true);

    for ( int i = 0; i < 5; i+=2) {
        material_layout_->setColumnMinimumWidth(i,   100);    
        material_layout_->setColumnMinimumWidth(i+1, 10 );    
        material_layout_->setColumnMinimumWidth(i+1, 10 );    
    }

    row0_cb_              = new QCheckBox(material_group_);
    row0_cb_->setObjectName("box01");
    QLabel*    index_l    = new QLabel("Index", material_group_);
    QLabel*    density_l  = new QLabel("Density", material_group_);
    QLabel*    modulus_l  = new QLabel("Modulus", material_group_);
    QLabel*    velocity_l = new QLabel("Velocity`", material_group_);
    edit_row_             = 0;
    material_layout_->addWidget(row0_cb_,      0, 0);
    material_layout_->addWidget(index_l,       0, 2);
    material_layout_->addWidget(density_l,     0, 4);
    material_layout_->addWidget(modulus_l,     0, 6);
    material_layout_->addWidget(velocity_l,    0, 8);

    
    button_group_->addButton(row0_cb_, 0);
    row0_cb_->setVisible(false);
    row0_cb_->setChecked(true);
    connect(button_group_, SIGNAL(idToggled(int, bool) ),
            this,          SLOT  (edit_mode(int, bool) ) );

    material_group_->setLayout(material_layout_);
    scroll_layout_->addWidget(material_group_);
    scroll_layout_->addStretch(50);
    scroll_group_->setLayout(scroll_layout_);
    scroll_area_->setWidget(scroll_group_);
    scroll_area_->setWidgetResizable(true);

    QGroupBox*   cmnd_group  = new QGroupBox(main_group);
    QHBoxLayout* cmnd_layout = new QHBoxLayout;
    QPushButton* add_l       = new QPushButton("Add Row",    cmnd_group);
    QPushButton* edit_l      = new QPushButton("Edit Row",   cmnd_group);
    QPushButton* save_l      = new QPushButton("Save Row",   cmnd_group);
    QPushButton* remove_l    = new QPushButton("Remove Row", cmnd_group);
    cmnd_layout->addWidget(add_l);
    cmnd_layout->addWidget(edit_l);
    cmnd_layout->addWidget(save_l);
    cmnd_layout->addWidget(remove_l);
    cmnd_group->setLayout(cmnd_layout);

    connect(add_l,       SIGNAL(pressed() ), this, SLOT(add_row() ) );
    connect(edit_l,      SIGNAL(pressed() ), this, SLOT(edit_pressed() ) );
    connect(remove_l,    SIGNAL(pressed() ), this, SLOT(remove_pressed() ) );

    add_l->setAutoDefault(false);
    add_l->setObjectName("button01");
    edit_l->setAutoDefault(false);
    edit_l->setObjectName("button01");
    save_l->setAutoDefault(false);
    save_l->setObjectName("button01");
    remove_l->setAutoDefault(false);
    remove_l->setObjectName("button01");

    QGroupBox*   accept_group  = new QGroupBox(main_group);
    QHBoxLayout* accept_layout = new QHBoxLayout;
    QPushButton* accept_b      = new QPushButton("Accept", accept_group);
    QPushButton* cancel_b      = new QPushButton("Cancel", accept_group);
    accept_layout->addWidget(accept_b);
    accept_layout->addWidget(cancel_b);
    accept_b->setAutoDefault(false);
    cancel_b->setAutoDefault(false);
    connect( accept_b, SIGNAL( clicked() ),this, SLOT(accepted() ) );
    connect( cancel_b, SIGNAL( clicked() ),this, SLOT(canceled() ) );
    accept_group->setLayout(accept_layout);

    accept_b->setObjectName("button01");
    cancel_b->setObjectName("button01");

    main_layout->addWidget(scroll_area_);
    main_layout->addWidget(cmnd_group);
    main_layout->addWidget(accept_group);
    setLayout(main_layout);

    material_store_ = MaterialStore::instance();
    material_store_->open(model_name);
    load_from_material_store();
    resize( 600, 300);
    move( 100, 10);
}

awv::MaterialDialog::
~MaterialDialog()
{
}

void
awv::MaterialDialog::
add_row()
{
    edit_row_   = material_layout_->rowCount();
    index_cb_   = new QCheckBox(material_group_);
    index_cb_->setObjectName("box01");
    QString    qs;
    index_e_              = new QLineEdit(qs.setNum(-999), material_group_);

    material_layout_->setRowMinimumHeight(edit_row_, 30);
    material_layout_->addWidget(index_cb_,   edit_row_, 0);
    material_layout_->addWidget(index_e_,    edit_row_, 2);

    index_e_->setReadOnly(false);

    connect(index_e_,   SIGNAL(returnPressed() ), this, SLOT( index_entered() ) );

    int   mx = scroll_bar_->maximum();
    scroll_bar_->setMaximum(mx + 36);
    scroll_bar_->setValue(scroll_bar_->maximum());
}

void
awv::MaterialDialog::
index_entered()
{
    QString      qs      = index_e_->text();
    bool         ok;
    int index     = qs.toInt(&ok);
    if ( !ok  ) {
        std::cout << "awv::MaterialDialog::index_entered - index = " << index << 
                                      " not ok" << std::endl;
        index_e_->setText(qs.setNum(-999) );
        return;
    }
    if ( material_store_->index_exists(index) ) {
        std::cout << "awv::MaterialDialog::index_entered- index = " << index_ << 
                        "already exists, seclect another" << std::endl;
        index_e_->setText(qs.setNum(-999) );
        return;
    }
    button_group_->addButton(index_cb_, index);
    row_map_.insert(std::make_pair(index, edit_row_) );
    index_e_->setReadOnly(true);

    init_property_row(edit_row_, 0.0, 0.0);
    index_cb_->setChecked(true);
}

void 
awv::MaterialDialog::
init_property_row(int irow, float density, float modulus)
{
    float velocity = 0.0;
    if (density != 0.0) velocity = sqrt( modulus / density);

    QString    qs;
    QLineEdit* density_e  = new QLineEdit(qs.setNum(density),  material_group_);
    QLineEdit* modulus_e  = new QLineEdit(qs.setNum(modulus),  material_group_);
    QLineEdit* velocity_e = new QLineEdit(qs.setNum(velocity), material_group_);
    material_layout_->addWidget(density_e,  irow, 4);
    material_layout_->addWidget(modulus_e,  irow, 6);
    material_layout_->addWidget(velocity_e, irow, 8);
    connect(density_e, SIGNAL(returnPressed() ), this, SLOT( density_entered() ) );
    connect(modulus_e, SIGNAL(returnPressed() ), this, SLOT( modulus_entered() ) );
    density_e->setReadOnly(true);
    modulus_e->setReadOnly(true);
    velocity_e->setReadOnly(true);
}

void
awv::MaterialDialog::
edit_mode(int index, bool checked)
{
    if ( index == 0 ) return;
    if ( !checked   ) {
        save_row(index);
        return;
    }

    auto p = row_map_.find(index);
    if ( p == row_map_.end() ) {
        std::cout << "awv::MaterialDialog::edit_mode, error index not in map" << std::endl;
        return;
    }
    edit_row_ = p->second;
    QLayoutItem* item      = material_layout_->itemAtPosition(edit_row_, 4);
    density_e_             = dynamic_cast<QLineEdit*>(item->widget() );
    item                   = material_layout_->itemAtPosition(edit_row_, 6);
    modulus_e_             = dynamic_cast<QLineEdit*>(item->widget() );
    item                   = material_layout_->itemAtPosition(edit_row_, 8);
    velocity_e_            = dynamic_cast<QLineEdit*>(item->widget() );
    density_e_->setReadOnly(false);
    modulus_e_->setReadOnly(false);
    velocity_e_->setReadOnly(true);
}

void
awv::MaterialDialog::
density_entered()
{
    std::cout << "awv::MarertialDialog::density_entered() " << std::endl;
    QString qs = density_e_->text();
    bool    ok;
    density_     = qs.toFloat(&ok);
    if ( !ok ) {
        std::cout << "awv::MaterialDialog::density_entered, not ok" << std::endl;
        density_ = 0;
        density_e_->setText(qs.setNum(density_) );
    }
    if ( density_ != 0.0) {
        velocity_ = sqrt(modulus_ / density_);
    } else {
        velocity_ = 0.0;
    }
    velocity_e_->setText(qs.setNum(velocity_) );
}

void
awv::MaterialDialog::
modulus_entered()
{
    QString qs = modulus_e_->text();
    bool    ok;
    modulus_     = qs.toFloat(&ok);
    if ( !ok ) {
        std::cout << "awv::MaterialDialog::modulus_entered, not ok" << std::endl;
        modulus_e_->setText(qs.setNum(0.0) );
    }
    if ( density_ != 0.0) {
        velocity_ = sqrt(modulus_ / density_);
    } else {
        velocity_ = 0.0;
    }
    velocity_e_->setText(qs.setNum(velocity_) );
}

void
awv::MaterialDialog::
save_row(int index)
{
    auto p = row_map_.find(index);
    if ( p == row_map_.end() ) {
        std::cout << "awv::MaterialDialog::edit_mode, error index not in map" << std::endl;
        return;
    }
    edit_row_ = p->second;
    QLayoutItem* item      = material_layout_->itemAtPosition(edit_row_, 4);
    QLineEdit*   density_e = dynamic_cast<QLineEdit*>(item->widget() );
    item                   = material_layout_->itemAtPosition(edit_row_, 6);
    QLineEdit*   modulus_e = dynamic_cast<QLineEdit*>(item->widget() );
    QString      qs        = density_e_->text();
    bool         ok;
    float        density   = qs.toFloat(&ok);
    qs                     = modulus_e->text();
    float        modulus   = qs.toFloat(&ok);
    density_e->setReadOnly(true);
    modulus_e->setReadOnly(true);
    material_store_->properties(index, std::make_pair(density, modulus ) );
}

void
awv::MaterialDialog::
load_from_material_store()
{
    row_map_ = material_store_->indexes();
    for (auto p = row_map_.begin(); p != row_map_.end(); p++) {
        int index = p->first;
        int irow  = p->second;
        QCheckBox* cb = new QCheckBox;
        button_group_->addButton(cb, index);
        QString    qs;
        QLineEdit* index_e = new QLineEdit(qs.setNum(index), material_group_);
        index_e->setReadOnly(true);
        material_layout_->addWidget(cb,       irow, 0);
        material_layout_->addWidget(index_e,  irow, 2);
        std::pair<float, float> props = material_store_->properties(index);
        init_property_row(irow, props.first, props.second);
    }
    return;
}

void
awv::MaterialDialog::
edit_pressed()
{
    std::cout << "awv::MaterialDialog::edit_pressed not implemented" << std::endl;
}

void
awv::MaterialDialog::
remove_pressed()
{
    std::cout << "awv::MaterialDialog::remove_pressed - row = " << edit_row_ << std::endl;
    QLayoutItem* item    = material_layout_->itemAtPosition(edit_row_, 2);
    QLineEdit*   index_e = dynamic_cast<QLineEdit*>(item->widget() );
    QString      qs      = index_e->text();
    bool         ok;
    int index     = qs.toInt(&ok);
    item                 = material_layout_->itemAtPosition(edit_row_, 0);
    QCheckBox* cb        = dynamic_cast<QCheckBox*>(item->widget() );
    button_group_->removeButton(cb);
    int nr = material_layout_->rowCount();
    std::cout << "awv::MaterialDialog::remove_pressed -1 nr = " << nr << std::endl;
    material_layout_->removeWidget(cb);
    delete cb;
    material_layout_->removeWidget(index_e);
    delete index_e;
    material_layout_->removeWidget(density_e_);
    delete density_e_;
    material_layout_->removeWidget(modulus_e_);
    delete modulus_e_;
    material_layout_->removeWidget(velocity_e_);
    delete velocity_e_;
    std::cout << "awv::MaterialDialog::remove_pressed -2" << std::endl;
    nr = material_layout_->rowCount();
    std::cout << "awv::MaterialDialog::remove_pressed -3 nr = " << nr << std::endl;

    material_store_->erase_properties(index);
    row_map_.erase(index);
}

void
awv::MaterialDialog::
accepted()
{
    std::cout << "awv::MaterialDialog::accepted()" << std::endl;
    row0_cb_->setChecked(true);
    material_store_->save();
    material_store_->close();
    done(QDialog::Accepted);
}

void
awv::MaterialDialog::
canceled()
{
    std::cout << "awv::MaterialDialog::canceled()" << std::endl;
    material_store_->close();
    done(QDialog::Rejected);
}

void
awv::MaterialDialog::
value_changed(int value)
{
/*
    std::cout << "awv::MaterialDialog::value_changed, value   = " << value << std::endl;
    int mx = scroll_bar_->maximum();
    std::cout << "awv::MaterialDialog::value_changed, maximum = " << mx << std::endl;
*/
}

void
awv::MaterialDialog::
slider_moved(int value)
{
}
/*
    std::cout << "awv::MaterialDialog::slider_moved, value   = " << value << std::endl;
    int mx = scroll_bar_->maximum();
    std::cout << "awv::MaterialDialog::slider_moved, maximum = " << mx << std::endl;
*/
