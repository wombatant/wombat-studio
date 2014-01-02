#ifndef NEWFILEMENU_HPP
#define NEWFILEMENU_HPP

#include <QDialog>
#include <QString>
#include "newfilemenuparams.hpp"

namespace wombat {
namespace editor {

class NewFileMenu: public QDialog {
	public:
		NewFileMenu(NewFileMenuParams);
		NewFileMenu(QWidget *parent);
		virtual QString path() = 0;
};

}
}

#endif
