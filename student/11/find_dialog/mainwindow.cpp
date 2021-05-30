#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "fstream"
#include "QtDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->fileLineEdit, &QLineEdit::editingFinished, this, &MainWindow::searching);

    connect(ui->keyLineEdit, &QLineEdit::editingFinished, this, &MainWindow::searching);

    connect(ui->findPushButton, &QPushButton::click, this, &MainWindow::searching);

    connect(ui->matchCheckBox, &QCheckBox::clicked, this, &MainWindow::searching);

    connect(ui->closePushButton, &QPushButton::click, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::searching()
{
    if (ui->findFromFile->text().size() == 0)
    {
        return;
    }

    // qDebug() << ui->fileLineEdit->text();
    std::ifstream file;

    file.open(ui->fileLineEdit->text().toStdString());

    if (file.is_open())
    {
        if (ui->keyLineEdit->text().length() == 0)
        {
            ui->textBrowser->setText("File found");
            ui->textBrowser->show();
        }
        else
        {
            std::string finding_word = ui->keyLineEdit->text().toStdString();

            if (!ui->matchCheckBox->isChecked())
            {
                for (auto it_char = finding_word.begin();
                     it_char != finding_word.end(); ++it_char)
                {
                    if (*it_char != std::tolower(*it_char))
                    {
                        *it_char = std::tolower(*it_char);
                    }
                }
            }

            std::string line = "";
            std::getline(file, line);

            while (line != "")
            {
                if (!ui->matchCheckBox->isChecked())
                {
                    for (auto it_char = line.begin();
                         it_char != line.end(); ++it_char)
                    {
                        if (*it_char != std::tolower(*it_char))
                        {
                            *it_char = std::tolower(*it_char);
                        }
                    }
                }

                if (line.find(finding_word) != std::string::npos)
                {
                    ui->textBrowser->setText("Word found");
                    ui->textBrowser->show();

                    break;
                }

                std::getline(file, line);
            }

            if (line == "")
            {
                ui->textBrowser->setText("Word not found");
                ui->textBrowser->show();
            }
        }

        file.close();
    }
    else
    {
        ui->textBrowser->setText("File not found");
        ui->textBrowser->show();
    }

}
