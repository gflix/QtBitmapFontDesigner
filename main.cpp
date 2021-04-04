#include <QApplication>
#include <QDebug>
#include <QImageWriter>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    if (!QImageWriter::supportedImageFormats().contains("png"))
    {
        qCritical() << "Your Qt installation does not support writing PNG files! Aborting.";
        return -1;
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
