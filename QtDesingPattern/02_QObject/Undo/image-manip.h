#pragma once

#include <QUndoCommand>
#include <QImage>

class AdjustColors : public QUndoCommand
{
public:
    AdjustColors(QImage& img, double radj, double gadj, double badj)
        : m_Image(img), m_Saved(img.size(), img.format()), m_RedAdj(radj),
        m_GreenAdj(gadj), m_BlueAdj(badj)
    {
        setText("adjust colors");
    }
    virtual void undo() override;
    virtual void redo() override;

private:
    QImage& m_Image;
    QImage m_Saved;
    double m_RedAdj, m_GreenAdj, m_BlueAdj;
    void adjust(double radj, double gadj, double badj);
};


class MirrorPixels : public QUndoCommand
{
public:
    MirrorPixels(QImage& img, bool horiz)
        : m_Image(img), m_Saved(img.size(), img.format()),
        m_Horizontal(horiz)
    {
        setText(QString("mirror pixels around %1 line")
                .arg(horiz ? "horizontal" : "vertical"));
    }
    virtual void undo() override;
    virtual void redo() override;

private:
    QImage& m_Image;
    QImage m_Saved;
    bool m_Horizontal;
    void reflect();
};
