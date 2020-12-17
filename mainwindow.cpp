#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(nullptr));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_convertButton_clicked()
{
    auto text = ui->inputTextEdit->toPlainText();
    QString output;
    for (int i = 0; i < text.size(); ++i)
    {
        auto itIsNecessaryToPasteNewFuckingEmoji =
                (i < text.size() - 1) &&
                (!text[i].isPunct() && !text[i + 1].isPunct());
        output.append(text[i]);
        if (itIsNecessaryToPasteNewFuckingEmoji)
            output.append(getRandomEmoji());
    }
    ui->outputTextEdit->setPlainText(output);
}

QString MainWindow::getRandomEmoji()
{
    const int minEmojiCode = 0x1F600;
    const int maxEmojiCode = 0x1F64F;   // just basic range, from wikipedia
    auto randomCode = minEmojiCode + rand() % (maxEmojiCode - minEmojiCode + 1);
    QString s;
    if (QChar::requiresSurrogates(randomCode))
    {
        s.append(QChar::highSurrogate(randomCode));
        s.append(QChar::lowSurrogate(randomCode));
    }
    else
        s.append(QChar(randomCode));
    return s;
}