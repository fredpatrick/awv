#include "materialrow.h"
#include "materialstore.h"

#include <cmath>

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QLineEdit>

awv::MaterialRow::
MaterialRow(QGroupBox* parent, QGridLayout* layout,  int   irow,
            int        index,  float        density, float modulus)
{
    mat_layout_ = layout;
    irow_       = irow;
    index_      = index;
    density_    = density;
    modulus_    = modulus;

    if ( density_ != 0.0) {
        velocity_ = sqrt(modulus_ / density_);
    } else {
        velocity_ = 0.0;
    }

    QString qs;
    index_e_    = new QLineEdit(qs.setNum(index_),    parent);
    density_e_  = new QLineEdit(qs.setNum(density_),  parent);
    modulus_e_  = new QLineEdit(qs.setNum(density_),  parent);
    velocity_e_ = new QLineEdit(qs.setNum(velocity_), parent);

    mat_layout_->addWidget(index_e_,    irow_, 0);
    mat_layout_->addWidget(density_e_,  irow_, 1);
    mat_layout_->addWidget(modulus_e_,  irow_, 2);
    mat_layout_->addWidget(velocity_e_, irow_, 3);

    connect(index_e_,   SIGNAL(returnPressed() ), this, SLOT( index_entered() ) );
    connect(density_e_, SIGNAL(returnPressed() ), this, SLOT( density_entered() ) );
    connect(modulus_e_, SIGNAL(returnPressed() ), this, SLOT( modulus_entered() ) );
}

awv::MaterialRow::
~MaterialRow()
{
}

void
awv::MaterialRow::
index_entered()
{
    QString qs = index_e_->text();
    bool    ok;
    index_     = qs.toInt(&ok);
    if ( !ok ) {
        index_ = 0;
        index_e_->setText(qs.setNum(index_) );
    }
}

void
awv::MaterialRow::
density_entered()
{
    QString qs = density_e_->text();
    bool    ok;
    density_     = qs.toInt(&ok);
    if ( !ok ) {
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
awv::MaterialRow::
modulus_entered()
{
    QString qs = modulus_e_->text();
    bool    ok;
    modulus_     = qs.toInt(&ok);
    if ( !ok ) {
        modulus_ = 0;
        modulus_e_->setText(qs.setNum(modulus_) );
    }
    if ( density_ != 0.0) {
        velocity_ = sqrt(modulus_ / density_);
    } else {
        velocity_ = 0.0;
    }
    velocity_e_->setText(qs.setNum(velocity_) );
}


