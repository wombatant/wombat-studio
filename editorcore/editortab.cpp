#include "editortab.hpp"

namespace wombat {
namespace editor {

EditorTab::EditorTab(EditorTabParams args): QWidget(args.parent) {
	m_undoStack = new QUndoStack(args.parent);
	m_lastCommand = m_lastSavedCommand = 0;
	m_path = args.filePath;
	m_models = args.models;
}

EditorTab::~EditorTab() {
	delete m_undoStack;
}

void EditorTab::addListener(EditorTabListener *l) {
	m_listeners.push_back(l);
}

void EditorTab::removeListener(EditorTabListener *l) {
	for (int i = 0; i < m_listeners.size(); i++) {
		if (m_listeners[i] == l) {
			m_listeners.erase(m_listeners.begin() + i);
			break;
		}
	}
}

bool EditorTab::currentStateSaved() {
	return m_lastSavedCommand == m_lastCommand;
}

QString EditorTab::title() {
	return m_title;
}

void EditorTab::title(QString title) {
	m_title = title;
}

void EditorTab::notifyFileChange(QUndoCommand *uc) {
	if (uc) {
		m_undoStack->push(uc);
		m_lastCommand = m_undoStack->index();
	}
	for (int i = 0; i < m_listeners.size(); i++) {
		m_listeners[i]->fileChanged();
	}
}

void EditorTab::modelIoManager(ModelIoManager *models) {
	m_models = models;
}

ModelIoManager *EditorTab::modelIoManager() {
	return m_models;
}

void EditorTab::notifyFileSave() {
	for (int i = 0; i < m_listeners.size(); i++) {
		m_listeners[i]->fileSaved();
	}
	m_lastSavedCommand = m_lastCommand;
}

void EditorTab::undo() {
	if (m_undoStack->canUndo()) {
		m_undoStack->undo();
		m_lastCommand = m_undoStack->index();

		if (currentStateSaved()) {
			notifyFileSave();
		} else {
			notifyFileChange();
		}
	}
}

void EditorTab::redo() {
	if (m_undoStack->canRedo()) {
		m_undoStack->redo();
		m_lastCommand = m_undoStack->index();

		if (currentStateSaved()) {
			notifyFileSave();
		} else {
			notifyFileChange();
		}
	}
}

bool EditorTab::canUndo() {
	return m_undoStack->canUndo();
}

bool EditorTab::canRedo() {
	return m_undoStack->canRedo();
}

QString EditorTab::path() {
	return m_path;
}

void EditorTab::closeTab() {
}

}
}
