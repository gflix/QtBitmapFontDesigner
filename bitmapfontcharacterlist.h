#ifndef BITMAPFONTCHARACTERLIST_H
#define BITMAPFONTCHARACTERLIST_H

#include <QAbstractListModel>
#include <QList>
#include "bitmapfontcharacter.h"

class BitmapFontCharacterList : public QAbstractListModel
{
    Q_OBJECT

public:
    typedef QList<BitmapFontCharacter> Characters;

    explicit BitmapFontCharacterList(QObject *parent = nullptr);

    void update(const BitmapFontCharacters& characters);
    QChar get(const QModelIndex& index) const;

    // Header:
    int columnCount(const QModelIndex&) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    Characters m_characters;
};

#endif // BITMAPFONTCHARACTERLIST_H
