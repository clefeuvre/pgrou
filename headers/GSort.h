#pragma once
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QColor>
#include <QSize>
#include <QPoint>
#include <vector>
#include "Sort.h"
#include "GVNode.h"
#include "GProcess.h"

/**
  * @file GSort.h
  * @brief header for the GSort class
  * @author PAPPL_2012
  *
  */

class GSort;
typedef boost::shared_ptr<GSort> GSortPtr;
class GSimpleProcess;
typedef boost::shared_ptr<GProcess> GProcessPtr;

/**
  * @class GSort
  * @brief contains style and layout info to draw a Sort
  *
  */
class GSort : public QGraphicsRectItem {

	public:

	static const int marginDefault;

    static const int defaultDistance;

        /**
          * @brief constructor
          *
          * @param SortPtr the related Sort object
          * @param GVNode the node of the skeleton graph containing layout info
          * @param qreal width of the Sort
          * @param qreal height of the Sort
          */
        GSort(SortPtr p, GVNode n, qreal width, qreal height);

		~GSort();


        /**
          * @brief get the rect item
          *
          */
        QGraphicsRectItem* getRect();

        /**
          * @brief the color used by the Actions that have this Sort as source
          *
          */
	QColor* color;

        /**
          * @brief Handles mouse press event (handles drag start)
          *
          * @param QGraphicsSceneMouseEvent the event to be handled
          */
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

        /**
          * @brief Handles mouse move event (handles drag)
          *
          * @param QGraphicsSceneMouseEvent the event to be handled
          */
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

        /**
          * @brief Handles mouse release event (handles drop)
          *
          * @param QGraphicsSceneMouseEvent the event to be handled
          */
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

        /**
          * @brief Handles context menu event (typically on right click)
          *
          * @param QGraphicsSceneContextMenuEvent the event to be handled
          */
        void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

        /**
          * @brief gets the related Sort object
          *
          * @return SortPtr a pointer to the related Sort object
          */
        SortPtr getSort();

        /**
          * @brief gets the related Node object
          *
          * @return GVnode a pointer to the related Sort object
          */
        GVNode getNode();

        /**
          * @brief gets the text of the sort
          *
          */
        QGraphicsTextItem* getText();

        /**
          * @brief updates the position of this GSort after drag&drop
          *
          */
        void updatePosition();

        /**
          * @brief hides this GSort setting opacity to 0
          */
        void hide();

        /**
          * @brief show the GSort setting full opacity
          */
        void show();

        /**
          * @brief indicates whether or not this GSort is made visible (test based on opacity, cf. hide() and show())
          */
        bool isVisible();

        /**
          * @brief gets the point used to record mouse press event position
          *
          */
        QPoint geteventPressPoint();

        /**
          * @brief get the center of the ellipse representing the process
          *
          * @return GPoint the center of the ellipse
          *
          */
        QPoint* getLeftTopCornerPoint();

        /**
          * @brief get the size of the ellipse representing the process
          *
          * @return GSize the size of the ellipse
          *
          */
        QSize* getSizeRect();

        void changeOrientation();


		
	protected:

        /**
          * @brief position of the left top corner of the rectangle representing the sort
          *
          */
	QPoint* leftTopCorner;

        /**
          * @brief size of the rectangle representing the sort
          *
          */
	QSize* sizeRect;

        /**
          * @brief the graphical item representing the rectangle of the Sort
          *
          */
        QGraphicsRectItem* _rect;

        /**
          * @brief the graphical item representing the text of the Sort
          *
          */
	QGraphicsTextItem* text;

        /**
          * @brief the related Sort
          *
          */
	SortPtr sort;

        /**
          * @brief list of GProcessPtr contained by the sort
          *
          */
	vector<GProcessPtr> gProcesses;

        /**
          * @brief the related of the skeletonGraph
          *
          */
	GVNode node;		
		
        /**
          * @brief the palette of colors that may be used as color member
          *
          */
        static std::vector<QColor> palette;

        /**
          * @brief palette management index
          *
          */
	static int paletteIndex;

        /**
          * @brief gets a new color in the palette
          *
          * @return QColor* the color retrieved in the palette
          */
	static QColor* makeColor(void);

        /**
          * @brief the point used to record this GSort's coordinates when user clicks it (ie. starts drag&drop)
          *
          */
        QPoint initPosPoint;

        /**
          * @brief the point used to record mouse press event position
          *
          */
        QPoint eventPressPoint;

        /**
          * @brief the space between this GSort's top side and the top GProcess
          *
          */
        qreal paddingTop;

        /**
          * @brief if the sort is vertical or not
          *
          */
        bool vertical;

};
