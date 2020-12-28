/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef EDITOR_H
#define EDITOR_H

#include <qwt_global.h>

#include <qobject.h>
#include <qpointer.h>
#include <qpoint.h>

class QwtPlot;
class QwtPlotShapeItem;
class QwtWidgetOverlay;

class QPainter;
class QRegion;

class Editor: public QObject
{
    Q_OBJECT

public:
    enum Mode
    {
        NoMask,
        Mask,
        AlphaMask,
        AlphaMaskRedraw,
        AlphaMaskCopyMask
    };

    Editor( QwtPlot * );
    virtual ~Editor();

    const QwtPlot *plot() const;
    QwtPlot *plot();

    virtual void setEnabled( bool on );
    bool isEnabled() const;

    void drawOverlay( QPainter * ) const;
    QRegion maskHint() const;

    virtual bool eventFilter( QObject *, QEvent *) QWT_OVERRIDE;

    void setMode( Mode mode );
    Mode mode() const;

private:
    bool pressed( const QPoint & );
    bool moved( const QPoint & );
    void released( const QPoint & );

    QwtPlotShapeItem* itemAt( const QPoint& ) const;
    void raiseItem( QwtPlotShapeItem * );

    QRegion maskHint( QwtPlotShapeItem * ) const;
    void setItemVisible( QwtPlotShapeItem *item, bool on );

    bool d_isEnabled;
    QPointer<QwtWidgetOverlay> d_overlay;

    // Mouse positions
    QPointF d_currentPos;
    QwtPlotShapeItem* d_editedItem;

    Mode d_mode;
};

#endif
