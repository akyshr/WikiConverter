#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QProcess>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupWidgets();
    signalSlotConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupWidgets()
{
    QStringList fromFormatList;
    fromFormatList << "textile";
    fromFormatList << "html";
    fromFormatList << "docbook";
//    fromFormatList << "haddock";
//    fromFormatList << "json";
    fromFormatList << "latex";
    fromFormatList << "markdown";
    fromFormatList << "markdown_github";
//    fromFormatList << "markdown_mmd";
//    fromFormatList << "markdown_phpextra";
//    fromFormatList << "markdown_strict";
    fromFormatList << "mediawiki";
//    fromFormatList << "native";
//    fromFormatList << "opml";
//    fromFormatList << "rst";
    fromFormatList << "textile";
    ui->fromComboBox->addItems(fromFormatList);
    QStringList toFormatList;
    toFormatList << "mediawiki";
    toFormatList << "textile";
    /*
    toFormatList << "asciidoc";
    toFormatList << "beamer";
    toFormatList << "context";
    toFormatList << "docbook";
    toFormatList << "docx";
    toFormatList << "dzslides";
    toFormatList << "epub";
    toFormatList << "epub3";
    toFormatList << "fb2";
    */
    toFormatList << "html";
    toFormatList << "html5";
    toFormatList << "json";
    toFormatList << "latex";
    toFormatList << "man";
    toFormatList << "markdown";
    toFormatList << "markdown_github";
    //    toFormatList << "markdown_mmd";
    //    toFormatList << "markdown_phpextra";
    //    toFormatList << "markdown_strict";
    toFormatList << "mediawiki";
    //    toFormatList << "native";
    //    toFormatList << "odt";
    //    toFormatList << "opendocument";
    /*
    toFormatList << "opml";
    toFormatList << "org";
    toFormatList << "pdf";
    toFormatList << "plain";
    toFormatList << "revealjs";
    toFormatList << "rst";
    toFormatList << "rtf";
    toFormatList << "s5";
    toFormatList << "slideous";
    toFormatList << "slidy";
    toFormatList << "texinfo";
    toFormatList << "textile";
    */
    ui->toComboBox->addItems(toFormatList);
}

void MainWindow::signalSlotConnections()
{
    connect(ui->actionQuit, SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->convertButton, SIGNAL(clicked()), this, SLOT(convertClicked()));
}

void MainWindow::convertClicked()
{
    QString fromString;
    fromString = ui->fromTextEdit->toPlainText();
    QString toString;
    QString fromFile = "src.txt";
    QString toFile = "dest.txt";
    writeFile(fromFile, fromString);
    QStringList cmds;
    cmds << "/usr/bin/pandoc";
    cmds << "-f" << ui->fromComboBox->currentText();
    cmds << "-t" << ui->toComboBox->currentText();
    cmds << fromFile;
    cmds << "-o" << toFile;
    QString output;
    runCmd(cmds, output);
    readFile(toFile,toString);
    ui->toTextEdit->setText(toString);
}

bool MainWindow::writeFile(const QString &filename, const QString &contents)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return false;
    }
    QTextStream out(&file);
    out << contents;
    file.close();

    return true;
}

bool MainWindow::readFile(const QString &filename, QString &contents)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return false;
    }

    QTextStream in(&file);
    contents = in.readAll();
    file.close();
    return true;
}

bool MainWindow::runCmd(QStringList cmds, QString &output)
{
    QProcess process(this);
    QString program = cmds.takeFirst();
    process.start(program, cmds);
    if (!process.waitForStarted()){
         return false;
    }

    if (!process.waitForFinished()){
        return false;
    }
    output = process.readAll();
    return true;
}
