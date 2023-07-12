#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionFechar_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionSobre_triggered()
{
    QMessageBox::information(this,"Sobre","KduNote é um bloco de notas criado por Carlos Eduardo Silva Santos a partir de um codigo no github");
}

void MainWindow::on_actionOpen_triggered()
{
    LocalArquivo = "";
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open file"),
        "C://",
        "Any File (*.*)"
        );
    if(fileName.isEmpty() == false){
        QFileInfo fileInfo(fileName);
        QWidget::setWindowTitle(fileInfo.baseName()+" - KduNote");
        LocalArquivo = fileName;

        QFile arquivo(fileName);
        if(arquivo.open(QFile::ReadOnly | QFile::Text)){
            QTextStream entrada(&arquivo);
            QString texto = entrada.readAll();
            ui->textEdit->setText(texto);
            arquivo.close();
        }
        else{
            QMessageBox::warning(this,"Erro arquivo", "Arquivo não foi encontrado ou não pode ser aberto");
        }

    }
    else{
        QMessageBox::information(this,"Falha ao abrir arquivo","Arquivo não foi aberto corretamente, houve uma tente novamente");
    }

}


void MainWindow::on_actionNovo_triggered()
{
    QWidget::setWindowTitle("Novo Arquivo - KduNote");
    LocalArquivo = "NULL";
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}


void MainWindow::on_actionSalvar_triggered()
{
    if(LocalArquivo != NULL){
        QFile arquivo(LocalArquivo);
        if(arquivo.open(QIODevice::WriteOnly)){
            QTextStream stream(&arquivo);
            stream << ui->textEdit->toPlainText();
            arquivo.close();
        }
        else{
            QMessageBox::warning(this,"Erro ao salvar","Erro ao salvar arquivo, tente novamente!");
        }
    }
    else{
        QString nameFile = QFileDialog::getSaveFileName(this,"Salvar arquivo","C://","Todos os arquivos (*.*)");
        LocalArquivo = nameFile;
        QFile arquivo(LocalArquivo);
        if(arquivo.open(QIODevice::WriteOnly)){
            QTextStream stream(&arquivo);
            stream << ui->textEdit->toPlainText();
            arquivo.flush();
            arquivo.close();
            QFileInfo fileInfo(LocalArquivo);
            QWidget::setWindowTitle(fileInfo.baseName()+" - KduNote");
        }
        else{
            QMessageBox::warning(this,"Erro ao salvar","Erro ao salvar arquivo, tente novamente!");
        }

    }
}

void MainWindow::on_actionSalvar_como_2_triggered()
{
    QString nameFile = QFileDialog::getSaveFileName(this,"Salvar arquivo","C://","Todos os arquivos (*.*)");
    LocalArquivo = nameFile;
    QFile arquivo(LocalArquivo);
    if(arquivo.open(QIODevice::WriteOnly)){
        QTextStream stream(&arquivo);
        stream << ui->textEdit->toPlainText();
        arquivo.flush();
        arquivo.close();
        QFileInfo fileInfo(LocalArquivo);
        QWidget::setWindowTitle(fileInfo.baseName()+" - KduNote");
    }
    else{
        QMessageBox::warning(this,"Erro ao salvar","Erro ao salvar arquivo, tente novamente!");
    }
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRefazer_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionCopiar_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionRecortar_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionColar_triggered()
{
    ui->textEdit->paste();
}

