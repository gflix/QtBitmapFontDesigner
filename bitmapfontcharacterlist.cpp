#include "bitmapfontcharacterlist.h"

#define COLUMN_CHARACTER (0)
#define COLUMN_WIDTH (1)
#define COLUMNS (2)

BitmapFontCharacterList::BitmapFontCharacterList(QObject *parent)
    : QAbstractListModel(parent)
{
}

void BitmapFontCharacterList::update(const BitmapFontCharacters& characters)
{
    beginResetModel();

    m_characters.clear();
    for (auto it = characters.constBegin(); it != characters.constEnd(); ++it)
    {
        m_characters.append(it.value());
    }

    endResetModel();
}

void BitmapFontCharacterList::updateCharacter(const BitmapFontCharacter& character)
{
    int row = 0;
    for (auto& item: m_characters)
    {
        if (item.character == character.character)
        {
            item = character;
            emit dataChanged(index(row, 0), index(row, COLUMNS - 1));
            break;
        }
        ++row;
    }
}

QChar BitmapFontCharacterList::get(const QModelIndex& index) const
{
    if (!index.isValid() || index.row() >= rowCount())
    {
        throw std::invalid_argument("invalid index");
    }

    return m_characters.at(index.row()).character;
}

QModelIndex BitmapFontCharacterList::get(QChar character) const
{
    int row = 0;
    for (auto& item: m_characters)
    {
        if (item.character == character)
        {
            return index(row, 0);
        }
        ++row;
    }
    return QModelIndex();
}

int BitmapFontCharacterList::columnCount(const QModelIndex&) const
{
    return COLUMNS;
}

QVariant BitmapFontCharacterList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case COLUMN_CHARACTER:
            return "Character";
        case COLUMN_WIDTH:
            return "Width";
        default:
            break;
        }
    }
    return QVariant();
}

int BitmapFontCharacterList::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_characters.count();
}

QVariant BitmapFontCharacterList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto character = m_characters.at(index.row());

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case COLUMN_CHARACTER:
            return character.character;
        case COLUMN_WIDTH:
            return character.width;
        default:
            break;
        }
    }

    return QVariant();
}
