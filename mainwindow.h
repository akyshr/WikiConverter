#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void setupWidgets();
    void signalSlotConnections();
    bool writeFile(const QString &filename, const QString &contents);
    bool readFile(const QString &filename, QString &contents);
    bool runCmd(QStringList cmds, QString &output);
private slots:
    void convertClicked();
    void execSetupDialog();
};

#endif // MAINWINDOW_H
