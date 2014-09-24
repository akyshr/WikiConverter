#include "setupdialog.h"
#include "ui_setupdialog.h"
#include <QSettings>
#include <QDir>
#include <QFileDialog>
#include <QDebug>


SetupDialog::SetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupDialog)
{
    ui->setupUi(this);
    setupWidgets();
    signalSlotConnections();
}

SetupDialog::~SetupDialog()
{
    delete ui;
}

bool SetupDialog::setupWidgets()
{
    qDebug() << SETTING_FILE;
    QSettings settings(SETTING_FILE);
    QString pandocPath = settings.value("PandocPath").toString();
    ui->pandocPathLineEdit->setText(pandocPath);
    return true;
}

bool SetupDialog::signalSlotConnections()
{
    connect(ui->pandocPathSelectButton, SIGNAL(clicked()), this, SLOT(clickPandocPathSelectButton()));
    return true;
}

void SetupDialog::accept()
{
    qDebug() << "accept";
    QSettings settings(SETTING_FILE);
    QString pandocPath = ui->pandocPathLineEdit->text();
    qDebug() << pandocPath;
    if (QFileInfo(pandocPath).isExecutable()){
        settings.setValue("PandocPath", ui->pandocPathLineEdit->text());
    }
    QDialog::accept();
}

void SetupDialog::clickPandocPathSelectButton()
{
    qDebug() << __PRETTY_FUNCTION__;
    QString pandocPath = ui->pandocPathLineEdit->text();
    pandocPath = QFileDialog::getOpenFileName(this, tr("select pandoc executable"),
                                              pandocPath,
                                              tr("pandoc executable (*)"));

    ui->pandocPathLineEdit->setText(pandocPath);
    qDebug() << pandocPath;

}

