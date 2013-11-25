#pragma once
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <list>
#include "PH.h"
#include "Process.h"
/**
  * @file GProcess.h
  * @brief header for the GProcess class
  * @author PAPPL_2013
  *
  */

class GProcess;
typedef boost::shared_ptr<GProcess> GProcessPtr;
class Process;
typedef boost::shared_ptr<Process> ProcessPtr;


/**
  * @class GProcess
  * @brief contains style and layout info to draw a process
  *
  */
class GProcess {

	public:

	static const int sizeDefault;

        /**
          * @brief constructor
          *
          * @param ProcessPtr the related Process object
          * @param double centerX position of the center of the ellipse in the x axis
          * @param double centerY position of the center of the ellipse in the y axis
          */
	GProcess(ProcessPtr p,double centerX, double centerY);

		~GProcess();

        /**
          * @brief gets the display
          *
          * @return QGraphicsItem the graphical item representing the Process
          */
	QGraphicsItem* getDisplayItem (void);

        /**
          * @brief gets the ellipse
          *
          */
        QGraphicsEllipseItem* getEllipseItem();

        /**
          * @brief gets the rect item that represents the margin of this GProcess
          *
          */
        QGraphicsRectItem* getMarginRect();


        /**
          * @brief updates the related center's coordinates with a point
          *
          * @param int x the horizontal coordinate of the node
          * @param int y the vertical coordinate of the node
          *
          */
        void setCoordsForImport(int x, int y);


        /**
          * @brief get the center of the ellipse representing the process
          *
          * @return GPoint the center of the ellipse
          *
          */
	QPointF* getCenterPoint();

        /**
          * @brief get the size of the ellipse representing the process
          *
          * @return GSize the size of the ellipse
          *
          */
	QSizeF* getSizeEllipse();

        /**
          * @brief gets the related Process
          *
          */

        ProcessPtr* getProcess();

        QGraphicsTextItem* getText();


	
	protected:

        /**
          * @brief the graphical item representing the Process
          *
          */
		QGraphicsItem* display;

       /**
          * @brief position of the center of the ellipse representing the process
          *
          */
	QPointF* center;

       /**
          * @brief size of the ellipse representing the process
          *
          */
	QSizeF* size;

        /**
          * @brief the graphical item representing the ellipse of the Process
          *
          */
		QGraphicsEllipseItem* ellipse;

        /**
          * @brief the graphical item representing the text of the Process
          *
          */
        QGraphicsTextItem* text;

        /**
          * @brief the related Process
          *
          */
		ProcessPtr process;

        /**
          * @brief the margin around this process, must exclude any other process' margin (cf. graphviz attribute "pos" in GVSubGraph)
          *
          */
        QGraphicsRectItem* marginRect;

        /**
          * @brief arbitrarily-chosen key for "margin item" data
          *
          */
        static const int marginZone;

        /**
          * @brief arbitrarily-chosen key for sort name data
          *
          */
        static const int sortName;

};
