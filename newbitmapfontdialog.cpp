#include "newbitmapfontdialog.h"
#include "ui_newbitmapfontdialog.h"

NewBitmapFontDialog::NewBitmapFontDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewBitmapFontDialog)
{
    ui->setupUi(this);
}

NewBitmapFontDialog::~NewBitmapFontDialog()
{
    delete ui;
}

BitmapFontMetrics NewBitmapFontDialog::getBitmapFontMetrics(void) const
{
    return BitmapFontMetrics(
        ui->spinBoxAscenders->value(),
        ui->spinBoxDescenders->value());
}
