#include <QApplication>
#include <QPushButton> 
#include <QComboBox>
#include <QLabel>
#include <QColorDialog>
#include <QGridLayout>
#include <QCheckBox>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include "paint.h"
#include "canvas.h"
#include "xmlloader.h"
#include "csvloader.h"
#include "jsonloader.h"
#include "xmlwriter.h"
#include "csvwriter.h"
#include "jsonwriter.h"
#include "node.h"

/** c'tor */
Paint::Paint(QWidget *parent)
	: QWidget(parent)
{
    // instantiate Canvas and widgets
	viewport = new Canvas();

	btnClearCanvas = new QPushButton("&Clear Canvas");

    startColor = Qt::lightGray;
    viewport->setObjColor(startColor);

    cobWidgetModes = new QComboBox();
    cobWidgetModes->addItem(tr("None"),      Canvas::NONE);
    cobWidgetModes->addItem(tr("Button"),    Canvas::BUTTON);
    cobWidgetModes->addItem(tr("Container"), Canvas::CONTAINER);

    lblWidgetModes = new QLabel("Widget Mode:");
    lblWidgetModes->setBuddy(cobWidgetModes);

    btnChangeCol = new QPushButton("&Set Color");
    btnChangeCol->setEnabled(true);
    cbIMode = new QCheckBox("&Design Mode");
    cbIMode->setChecked(true);
    cbIMode->setEnabled(true);

    // create layout and add gui elements to it
    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(viewport,       0, 0, 1, 3);
    mainLayout->addWidget(btnClearCanvas, 1, 0);
    mainLayout->addWidget(lblWidgetModes, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(cobWidgetModes, 1, 2);
    mainLayout->addWidget(cbIMode,        2, 1, Qt::AlignRight);
    mainLayout->addWidget(btnChangeCol,   2, 2);

	// add layout to this widget instance
	setLayout(mainLayout);
	
    // connect button click event to clear canvas handler
    connect(btnClearCanvas, SIGNAL(clicked()),
            this, SLOT(clearBtnPressed()));
    // connect button click event to color chooser handler
    connect(btnChangeCol, SIGNAL(clicked()),
            this, SLOT(colorBtnPressed()));
    // connect list view to primitive changed event handler
    connect(cobWidgetModes, SIGNAL(activated(int)),
            this, SLOT(widgetModeChanged(int)));
    // connect checkbox to toggle interaction handler
    connect(cbIMode, SIGNAL(toggled(bool)),
            this, SLOT(interactModeChanged(bool)));

    QAction *load = new QAction("Laden");
    QAction *save = new QAction("Speichern");
    QAction *quit = new QAction("Beenden");

    QMenu *menu = new QMenu("Datei");
    menu->addAction(load);
    menu->addAction(save);
    menu->addAction(quit);

    QMenuBar *bar = new QMenuBar();
    bar->addMenu(menu);

    connect(load, &QAction::triggered, this, [=]() {
        QString filename = QFileDialog::getOpenFileName(this, "Datei laden", "", "XML Dateien (*.xml);;Alle Dateien (*)");

        if (!filename.isEmpty()) {
            XMLLoader loader;
            if (loader.load(filename.toStdString())) {
                const Node* node = loader.getRoot();
                if (node) {
                    viewport->loadFromNodeTree(node);
                    viewport->update();
                    qDebug() << "GUI erfolgreich geladen.";
                }
            } else {
                qDebug() << "Fehler beim Laden der Datei.";
            }
        } else {
            qDebug() << "Laden abgebrochen.";
        }
    });
    connect(save, &QAction::triggered, this, [=]() {
        QString filename = QFileDialog::getSaveFileName(this, "Speichern unter", "", "XML Dateien (*.xml);;Alle Dateien (*)");

        if (!filename.isEmpty()) {
            Node* tree = viewport->buildNodeTree();
            if (tree) {
                XMLWriter writer;
                writer.write(filename.toStdString(), tree);
                delete tree;
                qDebug() << "GUI gespeichert als: " << filename;
            } else {
                qDebug() << "Kein GUI zum Speichern vorhanden.";
            }
        } else {
            qDebug() << "Speichern abgebrochen.";
        }
    });
    connect(quit, &QAction::triggered, this, [=](){
        qApp->quit();
    });
}

/** d'tor */
Paint::~Paint()
{
}

/** method for handling button clicked event */
void Paint::clearBtnPressed()
{
    qDebug() << "Clear image called";
	viewport->clearCanvas();
	// force redraw
    viewport->update();
}

void Paint::colorBtnPressed()
{
    QColor color(QColorDialog::getColor(startColor, this));
    if (color.isValid()) {
        qDebug() << "Color Choosen : " << color.name();
        viewport->setObjColor(color);
        update();
    }
}

void Paint::widgetModeChanged(int index)
{
    int mode = cobWidgetModes->itemData(index >= 0 ? index : 0).toInt();
    viewport->setWidgetMode(mode);
    qDebug() << "Widget Mode changed to " << mode;
    update();
}

void Paint::interactModeChanged(bool mode)
{
    viewport->setInteractionMode(mode);
    qDebug() << "Design Mode changed to " << mode;
    update();
}
