#ifndef CHARACTEREDITOR_H
#define CHARACTEREDITOR_H

#include <QWidget>
#include "bitmapfontcharacter.h"
#include "bitmapfontmetrics.h"

class CharacterEditor : public QWidget
{
    Q_OBJECT
public:
    explicit CharacterEditor(QWidget *parent = nullptr);

    void setBitmapFontCharacter(const BitmapFontCharacter& character);
    void setBitmapFontMetrics(const BitmapFontMetrics& metrics);

    const BitmapFontCharacter& getBitmapFontCharacter(void) const;

    void addCharacterColumn(void);
    void removeCharacterColumn(void);

signals:
    void characterUpdated(void);

protected:
    BitmapFontCharacter m_character;
    BitmapFontMetrics m_metrics;

    static QColor ledEdge;
    static QColor ledOff;
    static QColor ledOn;

    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    int getTotalHeight(void) const;
    int getTotalWidth(void) const;
    int getBlockEdgeLength(void) const;
};

#endif // CHARACTEREDITOR_H
