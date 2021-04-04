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

    void on_removeCharacterColumn_clicked();

    void on_addCharacterColumn_clicked();

    void on_characterUpdated(void);
    void on_changedCharacter(const QModelIndex& index, const QModelIndex& previous);

    void on_action_Save_triggered();

    void on_action_SaveAs_triggered();

    void on_action_Quit_triggered();

private:
    Ui::MainWindow* ui;
    CharacterEditor* m_characterEditor;
    QString targetFilename;

    BitmapFont m_bitmapFont;
    BitmapFontCharacterList m_bitmapFontCharacterList;

    void updateWindowTitle(void);
    void saveTo(const QString& filename);
};
#endif // MAINWINDOW_H
