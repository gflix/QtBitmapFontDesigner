#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "bitmapfontprotocol.h"
#include "newbitmapfontdialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_bitmapFontCharacterList(this)
{
    ui->setupUi(this);
    updateWindowTitle();

    m_characterEditor = new CharacterEditor();
    ui->frameLayout->insertWidget(0, m_characterEditor);

    ui->treeViewCharacters->setModel(&m_bitmapFontCharacterList);

    connect(m_characterEditor, &CharacterEditor::characterUpdated, this, &MainWindow::on_characterUpdated);
    connect(
        ui->treeViewCharacters->selectionModel(), &QItemSelectionModel::currentChanged,
        this, &MainWindow::on_changedCharacter
    );
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

        targetFilename.clear();
        updateWindowTitle();
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

    auto currentIndex = ui->treeViewCharacters->currentIndex();
    if (currentIndex.isValid())
    {
        auto& currentCharacter = m_bitmapFont.characters[m_bitmapFontCharacterList.get(currentIndex)];
        m_bitmapFont.characters[newCharacter[0]] = BitmapFontCharacter(newCharacter[0], currentCharacter.width, currentCharacter.matrix);
    }
    else
    {
        m_bitmapFont.characters[newCharacter[0]] = BitmapFontCharacter(newCharacter[0]);
    }

    m_bitmapFontCharacterList.update(m_bitmapFont.characters);
    ui->treeViewCharacters->setCurrentIndex(m_bitmapFontCharacterList.get(newCharacter[0]));
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

void MainWindow::on_removeCharacterColumn_clicked()
{
    m_characterEditor->removeCharacterColumn();
}

void MainWindow::on_addCharacterColumn_clicked()
{
    m_characterEditor->addCharacterColumn();
}

void MainWindow::on_characterUpdated(void)
{
    auto currentIndex = ui->treeViewCharacters->currentIndex();
    if (currentIndex.isValid())
    {
        auto selectedCharacter = m_bitmapFontCharacterList.get(currentIndex);
        auto updatedCharacter = m_characterEditor->getBitmapFontCharacter();
        updatedCharacter.character = selectedCharacter;
        m_bitmapFont.characters[selectedCharacter] = updatedCharacter;
        m_bitmapFontCharacterList.updateCharacter(updatedCharacter);
    }
    else
    {
        qInfo() << "nothing selected";
    }
}

void MainWindow::on_changedCharacter(const QModelIndex& index, const QModelIndex&)
{
    if (index.isValid())
    {
        qInfo() << "MainWindow::on_changedCharacter(" << index << ")";
        m_characterEditor->setBitmapFontCharacter(m_bitmapFont.characters[m_bitmapFontCharacterList.get(index)]);
    }
}

void MainWindow::updateWindowTitle(void)
{
    if (targetFilename.isEmpty())
    {
        setWindowTitle("QtBitmapFontDesigner - untitled");
    }
    else
    {
        setWindowTitle(QString("QtBitmapFontDesigner - %1").arg(targetFilename));
    }
}

void MainWindow::on_action_Save_triggered()
{
    if (targetFilename.isEmpty())
    {
        on_action_SaveAs_triggered();
    }
    else
    {
        saveTo(targetFilename);
    }
}

void MainWindow::on_action_SaveAs_triggered()
{
    auto filename = QFileDialog::getSaveFileName(this, "Save to", QString(), "XML files (*.xml)");
    if (filename.isEmpty())
    {
        return;
    }
    saveTo(filename);
}

void MainWindow::saveTo(const QString& filename)
{
    try
    {
        auto domDocument = bitmapFontToDomDocument(m_bitmapFont);
        auto processingInstructions = domDocument.createProcessingInstruction("xml", R"x(version="1.0" encoding="utf-8")x");
        domDocument.insertBefore(processingInstructions, domDocument.firstChild());

        QFile xmlFile(filename);
        if (!xmlFile.open(QFile::WriteOnly | QFile::Text))
        {
            throw std::runtime_error("error opening XML file \"" + filename.toStdString() + "\" for writing");
        }
        QTextStream xmlStream(&xmlFile);
        domDocument.save(xmlStream, 2);

        targetFilename = filename;
        updateWindowTitle();
    }
    catch (const std::exception& e)
    {
        QMessageBox::critical(this, "Error", QString("Could not save the bitmap font (%1)!").arg(e.what()));
    }
}

void MainWindow::on_action_Quit_triggered()
{
    close();
}

void MainWindow::on_action_Open_triggered()
{
    auto filename = QFileDialog::getOpenFileName(this, "Open bitmap font", QString(), "XML files (*.xml)");
    if (filename.isEmpty())
    {
        return;
    }

    try
    {
        QFile xmlFile(filename);
        if (!xmlFile.open(QFile::ReadOnly))
        {
            throw std::runtime_error("error opening XML file \"" + filename.toStdString() + "\" for reading");
        }
        QDomDocument domDocument;
        QString parseError;
        if (!domDocument.setContent(&xmlFile, &parseError))
        {
            throw std::runtime_error(
                QString("error parsing XML file \"%1\": %2").arg(filename).arg(parseError).toStdString());
        }

        m_bitmapFont = bitmapFontFromDomDocument(domDocument);
        m_characterEditor->setBitmapFontMetrics(m_bitmapFont.metrics);
        m_bitmapFontCharacterList.update(m_bitmapFont.characters);

        targetFilename = filename;
        updateWindowTitle();
    }
    catch (const std::exception& e)
    {
        QMessageBox::critical(this, "Error", QString("Could not load the bitmap font (%1)!").arg(e.what()));
    }
}
