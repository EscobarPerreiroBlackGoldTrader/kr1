#include "mainwindow.h"
#include "ui_mainwindow.h"


BSTtree<int,QString> f1(BSTtree<int,QString> tree);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    demo();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::demo(){

    BSTtree<int,QString> derevo;
    BSTtree<int,QString> bereza;

//    int sz = derevo.GetTreeSize();
//    QString data = derevo.GetData(1);

//    bool sucess = false;
//    if(derevo.addNode("Замечтательно",11)){
//        ui->textEdit->setText(derevo.GetData(11,sucess));
//    }

    derevo.addNode("яблоко",2);
    derevo.addNode("тыблоко",3);
    derevo.addNode("онблоко",-1);
    derevo.addNode("онаблоко",99);


    bereza.addNode("разлисток",15);
    bereza.addNode("двалисток",1);
    bereza.addNode("трилисток",25);
    bereza.addNode("чипырелисток",12);



    //derevo = f1(bereza);
    derevo.Join(bereza);
    //derevo.delNode(-100);

    bool Present;

//derevo.ClearTree(derevo.getRoot());

    int ppp;

    ppp = 8;

    if(ppp){
        ui->textEdit->insertPlainText(QString::number(derevo.GetTreeSize()));
        QString str = derevo.GetData(1,Present);
        if(Present){
            ui->textEdit->insertPlainText(str);
        }
    }
    ui->textEdit->insertPlainText("\n");

    int **pArrKeys = derevo.GetWalking();

    for(int i = 0;i < derevo.GetTreeSize();++i){

        //ui->textEdit->setText(QString::number((*pArrKeys[i])));
        ui->textEdit->insertPlainText(QString::number((*pArrKeys[i])) + " : ");
//        ui->textEdit->insertPlainText(" : ");
    }
    const int size(derevo.GetTreeSize());
    delete pArrKeys[size];

    ui->textEdit->insertPlainText("\n\n");



    derevo.ShowTree(ui->textEdit,derevo.getRoot()); // ?????

    /*
    //-----------------------------------------------------------------------------
    int **pArrKeys = derevo.GetWalking();

    for(int i = 0;i <= derevo.GetTreeSize();++i){

        //ui->textEdit->setText(QString::number((*pArrKeys[i])));
        ui->textEdit->insertPlainText(QString::number((*pArrKeys[i])));
    }
    const int size(derevo.GetTreeSize());
    delete pArrKeys[size];

    derevo.delNode(-1);

    pArrKeys = derevo.GetWalking();

    ui->textEdit->insertPlainText("\n");

    for(int i = 0;i <= derevo.GetTreeSize();++i){

        //ui->textEdit->setText(QString::number((*pArrKeys[i])));
        ui->textEdit->insertPlainText(QString::number((*pArrKeys[i])));
    }

    //derevo.Join(&bereza);
    //-----------------------------------------------------------------------------
    */


}

BSTtree<int,QString> f1(BSTtree<int,QString> tree){

    tree.addNode("дополнительный узел", 545);

    return tree;
}

