#include <QMessageBox>
#include "newbitmapfontdialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_bitmapFontCharacterList(this)
{
    ui->setupUi(this);

    m_characterEditor = new CharacterEditor();
    ui->frameLayout->insertWidget(0, m_characterEditor);

    ui->treeViewCharacters->setModel(&m_bitmapFontCharacterList);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_New_triggered()
{
    NewBitmapFontDialog dialog(m_bitmapFont.metrics, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        auto bitmapFontMetrics = dialog.getBitmapFontMetrics();

        m_characterEditor->setBitmapFontMetrics(bitmapFontMetrics);
        m_bitmapFont = BitmapFont(bitmapFontMetrics);
        m_bitmapFontCharacterList.update(m_bitmapFont.characters);
    }
}

void MainWindow::on_pushButtonAddCharacter_clicked()
{
    auto newCharacter = ui->lineEditCharacter->text();
    if (newCharacter.length() != 1)
    {
        return;
    }
    if (m_bitmapFont.characters.contains(newCharacter[0]))
    {
        QMessageBox::critical(this, "Error", QString("The character \"%1\" was already defined!").arg(newCharacter));
        return;
    }

    m_bitmapFont.characters[newCharacter[0]] = BitmapFontCharacter(newCharacter[0]);
    m_bitmapFontCharacterList.update(m_bitmapFont.characters);
}

void MainWindow::on_pushButtonRemoveCharacter_clicked()
{
    auto selectedItem = ui->treeViewCharacters->currentIndex();
    if (!selectedItem.isValid())
    {
        return;
    }

    auto selectedCharacter = m_bitmapFontCharacterList.get(selectedItem);
    if (QMessageBox::question(this, "Error", QString("Do you really want to delete the character \"%1\"?").arg(selectedCharacter)) == QMessageBox::Yes)
    {
        m_bitmapFont.characters.remove(selectedCharacter);
        m_bitmapFontCharacterList.update(m_bitmapFont.characters);
    }
}
