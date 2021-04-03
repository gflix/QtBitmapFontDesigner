#ifndef NEWBITMAPFONTDIALOG_H
#define NEWBITMAPFONTDIALOG_H

#include <QDialog>
#include "bitmapfontmetrics.h"

namespace Ui {
class NewBitmapFontDialog;
}

class NewBitmapFontDialog : public QDialog
{
    Q_OBJECT

public:

    explicit NewBitmapFontDialog(
        const BitmapFontMetrics& currentMetrics = BitmapFontMetrics(),
        QWidget *parent = nullptr);
    ~NewBitmapFontDialog();

    BitmapFontMetrics getBitmapFontMetrics(void) const;

private:
    Ui::NewBitmapFontDialog *ui;
};

#endif // NEWBITMAPFONTDIALOG_H
