#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QString>
#include <QtWidgets/QMainWindow>
#include "bitmapfont.h"
#include "bitmapfontcharacterlist.h"
#include "charactereditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_New_triggered();

    void on_pushButtonAddCharacter_clicked();

    void on_pushButtonRemoveCharacter_clicked();

private:
    Ui::MainWindow* ui;
    CharacterEditor* m_characterEditor;

    BitmapFont m_bitmapFont;
    BitmapFontCharacterList m_bitmapFontCharacterList;
};
#endif // MAINWINDOW_H
