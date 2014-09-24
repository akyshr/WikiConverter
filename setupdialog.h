#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>
#include <QDir>

namespace Ui {
class SetupDialog;
}

#define SETTING_FILE (QDir::homePath()+"/.config/WikiConverter.ini")

class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetupDialog(QWidget *parent = 0);
    ~SetupDialog();

private:
    Ui::SetupDialog *ui;
    bool setupWidgets();
    bool signalSlotConnections();

private slots:
    virtual void accept();

    void clickPandocPathSelectButton();
};

#endif // SETUPDIALOG_H
