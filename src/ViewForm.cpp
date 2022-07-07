#include "ViewForm.h"
#include "ui_ViewForm.h"

ViewForm::ViewForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewForm)
{
    ui->setupUi(this);
}

ViewForm::~ViewForm()
{
    delete ui;
}

void ViewForm::setViewWidget(QWidget *w)
{
//    ui->gridLayout->addItem(ui->horizontalSpacer, 0,0);
//    ui->gridLayout->addWidget(ui->pushButton, 0,1);
//    ui->gridLayout->addWidget(ui->pushButton_2,0,2);
//    ui->gridLayout->addWidget(ui->pushButton_3, 0,3);
//    ui->gridLayout->addItem(ui->horizontalSpacer_2, 0,4);
    ui->gridLayout->addWidget(w, 0,0, 1,6);
    _view = w;
}

void ViewForm::updateIndex(int i)
{
    _index = i;
}

QWidget *ViewForm::getView()
{
    return _view;
}

void ViewForm::hideLayoutButtons()
{
    ui->pushButton_Close->hide();
    ui->pushButton_Left->hide();;
    ui->pushButton_Right->hide();
}


void ViewForm::on_pushButton_Left_clicked()
{
    _index = (_index-1) > 0 ? _index-1 : 1;
    emit moveSplitterView(this, _index);
}


void ViewForm::on_pushButton_Right_clicked()
{
    _index++;
    emit moveSplitterView(this, _index);
}


void ViewForm::on_pushButton_Close_clicked()
{
    emit closeSplitterView(this);
}

