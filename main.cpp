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

    qSetGlobalQHashSeed(0);
    QApplication a(argc, argv);
    QString initialProject;
    if (argc > 1)
    {
        initialProject = argv[argc - 1];
    }
    MainWindow w { initialProject };
    w.show();
    return a.exec();
}
