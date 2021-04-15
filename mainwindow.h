#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resizeEvent(QResizeEvent *);
    void resizeTables();
private slots:
      void setModel(QSqlTableModel*);
      void showMessage(QString);
      void on_pushButton_clicked();

signals:
    void renewTable();
    void sendQuery();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
