#ifndef EDITORCORE_MODELIOMANAGER_HPP
#define EDITORCORE_MODELIOMANAGER_HPP

#include <QMap>
#include <QString>
#include <functional>
#include "models/editormodels.hpp"

namespace editor {

class ModelIoManager {
	private:
		QMap<QString, QString> m_models;
		QMap<QString, QVector<std::function<void(QString)>>> m_updateListeners;

	public:
		QString read(QString path);
		int write(QString path, QString value);

	private:
		void updateListeners(QString path, QString value);
};

}

#endif
