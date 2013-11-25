#include <iostream>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QSizeF>
#include <QTextDocument>
#include <Qt>
#include "GProcess.h"
#include <math.h>


const int GProcess::marginZone  = 10;
const int GProcess::sortName    = 11;
const int GProcess::sizeDefault = 100;

GProcess::GProcess(ProcessPtr p,double centerX, double centerY) : process(p){

    display = new QGraphicsItemGroup();


    // init size of the ellipse and the position of the center
    size = new QSizeF(sizeDefault,sizeDefault);
    center = new QPointF(centerX,centerY);

    // ellipse
    ellipse = new QGraphicsEllipseItem (center->x()-sizeDefault/2, center->y()-sizeDefault/2,
                                        size->width(), size->height(), display);
	ellipse->setPen(QPen(QColor(0,0,0)));
	ellipse->setBrush(QBrush(QColor(255,255,255)));


    int margin(GSort::marginDefault);

    marginRect = new QGraphicsRectItem(
                centerX - margin/2,
                centerY - margin/2,
                2*margin,
                2*margin,
                display);
                
    marginRect->setBrush(Qt::NoBrush);
    marginRect->setPen(Qt::NoPen);
    marginRect->setData(marginZone, true);
    marginRect->setData(sortName, process->getSort()->getName().c_str());
    
    // text
    text = new QGraphicsTextItem (QString("%1").arg(process->getNumber()), ellipse);
    text->setDefaultTextColor(QColor(7,54,66));
    text->setPos(centerX, centerY);

    // position the text
	QSizeF textSize = text->document()->size();
	text->setPos(text->x() - textSize.width()/2, text->y() - textSize.height()/2);
}


GProcess::~GProcess() {
    delete text;
    delete ellipse;
    delete center;
    delete size;
    delete display;
}


// getters

QGraphicsItem* GProcess::getDisplayItem (void) { return display; }

QGraphicsEllipseItem* GProcess::getEllipseItem(){ return ellipse; }

QGraphicsRectItem* GProcess::getMarginRect() { return this->marginRect; }

QPointF* GProcess::getCenterPoint() {return this->center;}

QSizeF* GProcess::getSizeEllipse() {return this->size;}

QGraphicsTextItem* GProcess::getText() {return this->text;}


void GProcess::setCoordsForImport(int x, int y) {
    center->setX(x);
    center->setY(y);
}

ProcessPtr* GProcess::getProcess() { return &(this->process); }
