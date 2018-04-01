#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    update_Menu();
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(update_Menu()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Open_triggered()
{
    //функция getOpenFileName() виджета QFileDialog возвращает имя файла
    QString fileName=QFileDialog::getOpenFileName(
    this,
    tr("Open Image"),
    "..",
    tr("Text Files (*.txt)"));
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
    QMessageBox::warning(this, tr("MDI"),
    tr("Cannot read file %1:\n%2.")
    .arg(fileName)
    .arg(file.errorString()));
    return;
    }
    QTextEdit * edit = new QTextEdit;
    QTextStream in(&file);
    edit->setWindowTitle(fileName);
    edit->setPlainText(in.readAll());
    ui->mdiArea->addSubWindow(edit);
    //вывод виджета edit
    edit->show();
}
void MainWindow::update_Menu()
{
if(ui->mdiArea->subWindowList().count()==0)
  {
  ui->menu_Window->setEnabled(false);
  ui->mainToolBar->hide();
 }
else
  {
  ui->menu_Window->setEnabled(true);
  ui->mainToolBar->show();
  }
}

