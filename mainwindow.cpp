#include <QDir>
#include <QFileDialog>
#include <QFileSystemModel>

#include <iostream>

#include "mainwindow.hpp"
#include "newmenu.hpp"
#include "savevariables.hpp"
#include "importmenu.hpp"
#include "newproject.hpp"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	m_currentTab = 0;
}

MainWindow::~MainWindow() {
	if (ui->fileList->model())
		delete ui->fileList->model();
	delete ui;
}

void MainWindow::newMenu() {
	NewMenu menu(this, "");
	menu.exec();
	QString nw = menu.newWhat();
	if (nw == "Project") {
		NewProject np(this);
		np.exec();
		QString p = np.projectDir();
		if (p != "") {
			openProject(p);
		}
	}
}

void MainWindow::openProject() {
	QString p = QFileDialog::getExistingDirectory(this, tr("Open Project Directory..."), QDir::homePath());
	if (p != "") {
		openProject(p);
	}
}

void MainWindow::openProject(QString path) {
	if (!path.endsWith("/"))
		path += "/";
	m_projectDir = path;
	setWindowTitle("Wombat Editor - " + path.mid(0, path.length() - 1));

	if (ui->fileList->model())
		delete ui->fileList->model();

	QFileSystemModel *model = new QFileSystemModel();
	ui->fileList->setModel(model);
	ui->fileList->setHeaderHidden(true);
	for (int i = 1; i < 4; i++) {
		ui->fileList->hideColumn(i);
	}
	QStringList l;
	l << "*.json" << "*.bmp" << "*.png" << "*.jpg";
	model->setNameFilters(l);
	model->setNameFilterDisables(false);
	ui->fileList->setRootIndex(model->setRootPath(path));
	ui->actionImport->setEnabled(true);
}

void MainWindow::openFile(QModelIndex index) {
	QString path = ((QFileSystemModel*) ui->fileList->model())->fileInfo(index).canonicalFilePath();
	if (m_projectDir + "Misc/SaveVariables.json" == path) {
		//open save variables tab
		if (!m_openTabs[path]) {
			SaveVariables *widget = new SaveVariables(path, ui->tabWidget);
			ui->tabWidget->addTab(widget, "SaveVariables.json");
			m_openTabs[path] = widget;
			m_currentTab = widget;
		}
	}
}

void MainWindow::import() {
	ImportMenu menu(this);
	menu.exec();
	QString nw = menu.importWhat();

	if (nw == "Image") {
		NewProject np(this);
		np.exec();
		openProject(np.projectDir());
	}
}

void MainWindow::saveFile() {
	FileTab *t = m_currentTab;
	if (t)
		t->saveFile();
}
