#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openBtn_pressed()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open", "Open an Mp3 file ...", "Audio Files (*.mp3)");

    if(!QFile(filename).exists() || filename.trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Caution", "Select something that actually exists!");
        return;
    }

    ID3Tag *tag;

    if ((tag = ID3Tag_New()) != NULL)
    {
        ID3Frame *frame;

        (void) ID3Tag_Link(tag, filename.toLatin1());
        if ((frame = ID3Tag_FindFrameWithID(tag, ID3FID_TITLE)) != NULL)
        {
            ID3Field *field;
            if ((field = ID3Frame_GetField(frame, ID3FN_TEXT)) != NULL)
            {
                char title[1024];
                (void) ID3Field_GetASCII(field, title, 1024);
                QMessageBox::information(this, "Title", "Title: " + QString(title));
            }
            else
            {
                QMessageBox::critical(this, "Error", "Didn't get the field!");
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "Didn't get the frame!");
        }

        if ((frame = ID3Tag_FindFrameWithID(tag, ID3FID_LEADARTIST)) != NULL)
        {
            ID3Field *field;
            if ((field = ID3Frame_GetField(frame, ID3FN_TEXT)) != NULL)
            {
                char artist[1024];
                (void) ID3Field_GetASCII(field, artist, 1024);
                QMessageBox::information(this, "Artist","Artist: " + QString(artist));
            }
            else
            {
                QMessageBox::critical(this, "Error", "Didn't get the field!");
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "Didn't get the frame!");
        }

        if ((frame = ID3Tag_FindFrameWithID(tag, ID3FID_ALBUM)) != NULL)
        {
            ID3Field *field;
            if ((field = ID3Frame_GetField(frame, ID3FN_TEXT)) != NULL)
            {
                char album[1024];
                (void) ID3Field_GetASCII(field, album, 1024);
                QMessageBox::information(this, "Album","Album: " + QString(album));
            }
            else
            {
                QMessageBox::critical(this, "Error", "Didn't get the field!");
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "Didn't get the frame!");
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "Didn't get the tag!");
    }


}
