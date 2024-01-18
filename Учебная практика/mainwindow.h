#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //слот загружающий изображение
    void on_loadButton_clicked();

    //слот сохраняющий палитру изображения
    void on_exportButton_clicked();

private:
    QList<QColor> palette;
    Ui::MainWindow *ui;

    //находит палитру, сохраняет ее в поле класса и отображает в окне
    void showPalette(QImage image);
};
#endif //MAINWINDOW_H
