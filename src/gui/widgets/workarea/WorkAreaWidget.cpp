#include "WorkAreaWidget.h"
#include "MainWindow.h"
#include "WorkAreaTabWidget.h"
#include "QueryWidget.h"
#include "domain/MongoCollection.h"
#include "AppRegistry.h"
#include "GuiRegistry.h"
#include "Dispatcher.h"

using namespace Robomongo;

/*
** Constructs work area
*/
WorkAreaWidget::WorkAreaWidget(MainWindow * mainWindow)	:
    QWidget(),
    _dispatcher(&AppRegistry::instance().dispatcher())
{
	_mainWindow = mainWindow;
    _tabWidget = new WorkAreaTabWidget(this);
	_tabWidget->setMovable(true);

	QHBoxLayout * hlayout = new QHBoxLayout;
	hlayout->setMargin(0);
	hlayout->addWidget(_tabWidget);
	setLayout(hlayout);

    _dispatcher->subscribe(this, OpeningShellEvent::EventType);
}

WorkAreaWidget::~WorkAreaWidget()
{
    int a = 56;
}

bool WorkAreaWidget::event(QEvent *event)
{
    R_HANDLE(event)
    R_EVENT(OpeningShellEvent)
    else return QObject::event(event);
}

void WorkAreaWidget::handle(const OpeningShellEvent *event)
{
//    QLabel * queryWidget = new QLabel("Hello");
    QueryWidget * queryWidget = new QueryWidget(event->shell, this);
    _tabWidget->addTab(queryWidget, "Robotab" /* viewModel->title()*/);
    _tabWidget->setCurrentIndex(_tabWidget->count() - 1);

    _tabWidget->setTabIcon(_tabWidget->count() - 1, GuiRegistry::instance().collectionIcon());
}
