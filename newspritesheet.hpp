#ifndef NEWSPRITESHEET_HPP
#define NEWSPRITESHEET_HPP

#include "editorcore/newfilemenu.hpp"

namespace Ui {
class NewSpriteSheet;
}

class NewSpriteSheet: public wombat::editor::NewFileMenu {
	Q_OBJECT
		
	private:
		Ui::NewSpriteSheet *ui;
		QString m_projectPath;
		QString m_path;

	public:
		explicit NewSpriteSheet(QString projectPath, QWidget *parent = 0);
		~NewSpriteSheet();

		/**
		 * @brief Gets path of created file.
		 * @return path of created file
		 */
		QString path();

	public slots:
		void accept();
};

#endif // NEWSPRITESHEET_HPP
