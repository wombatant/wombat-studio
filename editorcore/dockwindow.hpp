#ifndef EDITORCORE_DOCKWINDOW_HPP
#define EDITORCORE_DOCKWINDOW_HPP

#include <QDockWidget>
#include "commonobject.hpp"
#include "dockwindowparams.hpp"

namespace editor {

class DockWindow: public QDockWidget, public CommonObject {
	private:
		Qt::DockWidgetArea m_area;

	public:
		DockWindow(DockWindowParams);

		Qt::DockWidgetArea dockWidgetArea();

		void dockWidgetArea(Qt::DockWidgetArea);
};

}

#endif
