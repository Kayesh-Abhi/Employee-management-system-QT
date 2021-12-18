#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pictureR("C:/Users/Administer/Desktop/POS_test01/close.png");
    QPixmap pictureG("C:/Users/Administer/Desktop/POS_test01/correct.png");
    //ui->lbl_pic->setPixmap(pictureL);

    mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/Administer/Desktop/POS_test01/empdb.db");

    if(!mydb.open())
    {
        ui->label->setText("Not Connected");
        ui->label_5->setPixmap(pictureR);
    }
        else
    {
        ui->label->setText("DB Connected");
        ui->label_5->setPixmap(pictureG);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString username,password;

    username=ui->lineEdit_uname->text();
    password=ui->lineEdit_pword->text();

    if(!mydb.isOpen())
    {
        qDebug()<<"Failed to open the database.";
        return;
    }

    QSqlQuery query;

    if(query.exec("select * from employee where username='"+username+"' and password='"+password+"'"))
    {
        int count=0;
        while(query.next())
        {
            count++;
        }
        if(count==1){
            ui->label_4->setText("*username & password is correct");
        }
        //if(count>1){
          //  ui->label->setText("Duplicate username & password");
        //}
        if(count<1){
            ui->label_4->setText("<html><p style='color:red;'>* incorrect username or password</p></html>");
        }
    }

}

