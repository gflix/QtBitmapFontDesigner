#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include "charactereditor.h"

#define BLOCK_MARGIN (4)

QColor CharacterEditor::ledEdge = QColor::fromHsv(36, 255, 44);
QColor CharacterEditor::ledOff = QColor::fromHsv(36, 255, 52);
QColor CharacterEditor::ledOn = QColor::fromHsv(36, 255, 255);

CharacterEditor::CharacterEditor(QWidget* parent):
    QWidget(parent)
{
}

void CharacterEditor::setBitmapFontCharacter(const BitmapFontCharacter& character)
{
    m_character = character;

    update();
}

void CharacterEditor::setBitmapFontMetrics(const BitmapFontMetrics& metrics)
{
    m_metrics = metrics;

    update();
}

const BitmapFontCharacter& CharacterEditor::getBitmapFontCharacter(void) const
{
    return m_character;
}

void CharacterEditor::addCharacterColumn(void)
{
    ++m_character.width;
    m_character.matrix.append(BitmapFontCharacterColumn());
    update();

    emit characterUpdated();
}

void CharacterEditor::removeCharacterColumn(void)
{
    if (m_character.width <= 1)
    {
        return;
    }
    --m_character.width;
    m_character.matrix.removeLast();
    update();

    emit characterUpdated();
}

void CharacterEditor::mousePressEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton)
    {
        return;
    }

    int xOffset = (width() - getBlockEdgeLength() * getTotalWidth()) / 2;
    int column = -1;
    if (event->x() > xOffset)
    {
        column = (event->x() - xOffset) / getBlockEdgeLength();
    }

    int yOffset = (height() - getBlockEdgeLength() * getTotalHeight()) / 2;
    int row = -1;
    if (event->y() > yOffset)
    {
        row = (event->y() - yOffset) / getBlockEdgeLength();
    }

    if (column >=0 && m_character.matrix.count() > column)
    {
        auto& matrixColumn = m_character.matrix[column];
        if (row >= 0 && matrixColumn.count() >= row)
        {
            matrixColumn[row] = !matrixColumn[row];
            update();

            emit characterUpdated();
        }
    }
}

void CharacterEditor::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
//    painter.fillRect(event->rect(), QBrush(Qt::black));

    if (getTotalWidth() > 0 && getTotalHeight() > 0)
    {
        painter.translate(
            (width() - getBlockEdgeLength() * getTotalWidth()) / 2,
            (height() - getBlockEdgeLength() * getTotalHeight()) / 2);

        painter.setPen(QPen(ledEdge, getBlockEdgeLength() / 25.0));
        for (auto x = 0; x < getTotalWidth(); ++x)
        {
            if (m_character.matrix.count() <= x)
            {
                m_character.matrix.append(BitmapFontCharacterColumn());
            }
            auto& column = m_character.matrix[x];
            for (auto y = 0; y < getTotalHeight(); ++y)
            {
                if (column.count() <= y)
                {
                    column.append(false);
                }

                QPainterPath path;
                path.addRoundedRect(
                    QRect(
                        x * getBlockEdgeLength() + BLOCK_MARGIN,
                        y * getBlockEdgeLength() + BLOCK_MARGIN,
                        getBlockEdgeLength() - BLOCK_MARGIN,
                        getBlockEdgeLength() - BLOCK_MARGIN),
                    getBlockEdgeLength() / 5.0,
                    getBlockEdgeLength() / 5.0);
                painter.fillPath(path, QBrush(column[y] ? ledOn : ledOff));
                painter.drawPath(path);
            }
        }

        painter.setPen(QPen(QBrush(Qt::black), 4));
        painter.drawLine(
            0,
            m_metrics.ascenders * getBlockEdgeLength(),
            getTotalWidth() * getBlockEdgeLength(),
            m_metrics.ascenders * getBlockEdgeLength());
    }

    painter.end();
}

int CharacterEditor::getTotalHeight(void) const
{
    return m_metrics.ascenders + m_metrics.descenders;
}

int CharacterEditor::getTotalWidth(void) const
{
    return m_character.width;
}

int CharacterEditor::getBlockEdgeLength(void) const
{
    return qMin(width() / getTotalWidth(), height() / getTotalHeight());
}
