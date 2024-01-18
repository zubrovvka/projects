#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QColor>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, "Выберите файл", "/home", "Images (*.png *.bmp *.jpg)");

    if (!fileName.isEmpty())
    {
        QPixmap pixmap;
        if (pixmap.load(fileName))
        {
            //изменение размера изображения для отображения
            double heightRatio = pixmap.height()/ui->pictureLabel->height();
            double widthRatio = pixmap.width()/ui->pictureLabel->width();
            if (heightRatio >= widthRatio && heightRatio >= 1)
                pixmap = pixmap.scaledToHeight(ui->pictureLabel->height());
            if (heightRatio < widthRatio && widthRatio >= 1)
                pixmap = pixmap.scaledToWidth(ui->pictureLabel->width());
            if (heightRatio < 1 && widthRatio < 1)
            {
                if (widthRatio < heightRatio)
                    pixmap = pixmap.scaledToWidth(ui->pictureLabel->width());
                else
                    pixmap = pixmap.scaledToHeight(ui->pictureLabel->height());
            }
            ui->pictureLabel->setPixmap(pixmap);

            QImage image;
            image.load(fileName);
            palette.clear();
            QList<QLabel*> labelList{ui->color1, ui->color2, ui->color3, ui->color4, ui->color5, ui->color6,
                        ui->textColor1, ui->textColor2, ui->textColor3, ui->textColor4, ui->textColor5, ui->textColor6};
            for (int i = 0; i < labelList.size(); ++i)
                labelList[i]->clear();
            showPalette(image);
        }
        else
        {
            QMessageBox::critical(this, "Ошибка!", "Не удалось загрузить изображение");
        }
    }
}

double getDistanceBetweenColors(const QColor& color1, const QColor& color2)
{
    return sqrt(0.299*pow(color1.red()-color2.red(), 2) +
                0.114*pow(color1.blue()-color2.blue(), 2) +
                0.587*pow(color1.green()-color2.green(), 2));
}

void MainWindow::showPalette(QImage image)
{
    //сжатие изображения для ускорения работы
    if (image.width() > 1280)
        image = image.scaledToWidth(1280);
    if (image.height() > 720)
        image = image.scaledToHeight(720);
    const int kCountTopColors = 6;

    QMap<QString, int> colorMap; //будет хранить имя цвета в hex и число пикселей этого цвета
    for (int x = 0; x < image.width(); ++x)
    {
        for (int y = 0; y < image.height(); ++y)
        {
            QString colorName = image.pixelColor(x,y).name();
            if (colorMap.end() == colorMap.find(colorName))
            {
                colorMap.insert(colorName, 1);
            }
            else
            {
                ++colorMap[colorName];
            }
        }
    }
    QList<QLabel*> colorLabelList{ui->color1, ui->color2, ui->color3, ui->color4, ui->color5, ui->color6};
    QList<QLabel*> textLabelList{ui->textColor1, ui->textColor2, ui->textColor3, ui->textColor4, ui->textColor5, ui->textColor6};
    QList values = colorMap.values();
    int m = *std::max_element(values.begin(), values.end());
    QList keys = colorMap.keys(m);
    const double kminDistanceBetweenDiffColors = 35;

    for (int i = 0; i < kCountTopColors; ++i)
    {
        bool noMoreColors = false;
        QString colorName = keys[0];
        QColor color = QColor::fromString(colorName);
        if (!palette.isEmpty())
        {
            bool itIsSimilar = false; //переменная показывает был ли уже отображен цвет близкий к нынешнему
            for (int j = 0; j < palette.size(); ++j)
            {
                if (getDistanceBetweenColors(color, palette[j]) < kminDistanceBetweenDiffColors)
                {
                    keys.removeFirst();
                    if (keys.isEmpty())
                    {
                        values.removeAll(m);
                        if (values.isEmpty())
                        {
                            noMoreColors = true;
                        }
                        else
                        {
                            m = *std::max_element(values.begin(), values.end());
                            keys = colorMap.keys(m);
                        }
                    }
                    itIsSimilar = true;
                    break;
                }
            }
            if (noMoreColors)
            {
                break;
            }
            if (itIsSimilar)
            {
                --i;
                continue;
            }
        }
        color.setAlpha(255);
        palette.append(color);
        QPixmap pixmap(colorLabelList[i]->width(), colorLabelList[i]->height());
        pixmap.fill(color);
        colorLabelList[i]->setPixmap(pixmap);
        textLabelList[i]->setText(colorName);
        keys.removeFirst();
        if (keys.isEmpty())
        {
            values.removeAll(m);
            if (values.isEmpty())
            {
                break;
            }
            m = *std::max_element(values.begin(), values.end());
            keys = colorMap.keys(m);
        }
    }
}

void MainWindow::on_exportButton_clicked()
{
    if (!palette.isEmpty())
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Cохраните файл",
                                   "/home/untitled.png",
                                   "Images (*.png)");
        int kBlockWidth = 50;
        int kBlockHeight = 25;
        QImage image(kBlockWidth, kBlockHeight*palette.size(), QImage::Format_RGB32);
        for (int x = 0; x < kBlockWidth; ++x)
        {
            for (int i = 0; i < palette.size(); ++i)
            {
                for (int y = 0; y < kBlockHeight; ++y)
                {
                    image.setPixelColor(x, i * kBlockHeight + y, palette[i]);
                }
            }
        }
        if(!image.save(fileName))
        {
            QMessageBox::critical(this, "Ошибка!", "Не удалось сохранить палитру");
        }
    }
}

