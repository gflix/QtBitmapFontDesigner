#ifndef BITMAPFONTMETRICS_H
#define BITMAPFONTMETRICS_H


struct BitmapFontMetrics
{
    explicit BitmapFontMetrics(
        int ascenders = 8,
        int descenders = 3);

    int ascenders;
    int descenders;
};

#endif // BITMAPFONTMETRICS_H
