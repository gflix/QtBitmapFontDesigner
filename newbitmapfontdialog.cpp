#include "newbitmapfontdialog.h"
#include "ui_newbitmapfontdialog.h"

NewBitmapFontDialog::NewBitmapFontDialog(
    const BitmapFontMetrics& currentMetrics,
    QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewBitmapFontDialog)
{
    ui->setupUi(this);

    ui->spinBoxAscenders->setValue(currentMetrics.ascenders);
    ui->spinBoxDescenders->setValue(currentMetrics.descenders);
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
