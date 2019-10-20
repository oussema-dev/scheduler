#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string.h>


using namespace std;


//un processus est caractérisé par son numéro sa date d'arrivée et sa durée d'exécution
struct processus{
    int num,dateArr,duree;
};


//ordonnancement selon la politique FIFO
void fifo(processus tableau[],int longueur){
     int i, compt, marqueur;
     processus memory;
     for(i=1;i<longueur;i++){
        memory=tableau[i];
        compt=i-1;
        do{
            marqueur=false;
            if (tableau[compt].dateArr>memory.dateArr){
                tableau[compt+1]=tableau[compt];
                compt--;
                marqueur=true;
            }
            if (compt<0)
                marqueur=false;
        }
        while(marqueur);
        tableau[compt+1]=memory;
     }
}


//ordonnancement selon la politique SJF
void sjf(processus tableau[], int longueur){
    int i, inversion;processus aux;
    fifo(tableau,longueur);
    do{
        inversion=0;
        for(i=0;i<longueur-1;i++){
            if(tableau[i].dateArr==tableau[i+1].dateArr){
                if (tableau[i].duree>tableau[i+1].duree){
                    aux=tableau[i];
                    tableau[i]=tableau[i+1];
                    tableau[i+1]=aux;
                    inversion=1;
                }
            }
        }
    }while(inversion);
}


//Remplissage aléatoire du tableau de processus
void remplir(processus tableau[], int longueur){
    for(int i=0;i < longueur;i++){
        tableau[i].num = i;
        tableau[i].dateArr = (rand() % 10);
        tableau[i].duree =  rand() % (21 - 10) + 10;
    }
}


//initialisation de l'interface graphique
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->nbprocess->setRange(0, 10);
    ui->quantum->setRange(3, 10);
    ui->fifo->setChecked(true);  //La politique FIFO est la politique d'ordonnancement par défaut
}


MainWindow::~MainWindow(){
    delete ui;
}


//le code qui s'éxécute chaque foix le bouton "Lancer l'ordonnancement" est actionné
void MainWindow::on_btn_clicked(){

    int nbprocess = ui->nbprocess->value();
    int quantum = ui->quantum->value();


    //initialisation des deux tableaux
    for(int r=0;r<10;r++){
        ui->tableWidget->setItem(r, 0, new QTableWidgetItem(" "));
        ui->tableWidget->setItem(r, 1, new QTableWidgetItem(" "));
        ui->tableWidget->setItem(r, 2, new QTableWidgetItem(""));
    }
    for(int r=0;r<40;r++){
        ui->result->setItem(r, 0, new QTableWidgetItem(" "));
        ui->result->setItem(r, 1, new QTableWidgetItem(" "));
        ui->result->setItem(r, 2, new QTableWidgetItem(" "));
    }


    //classe qui permet de passer les valeurs dans les tableaux sous la forme "entier"
    class TableItem : public QTableWidgetItem{
    public:
        TableItem(int num):QTableWidgetItem(QString::number(num)){}
    };


    processus tab[nbprocess];


    if(nbprocess == 0){
        ui->msg->setText("Entrer le nombre de processus!");
    }
    else{
        ui->msg->setText("");

        remplir(tab,nbprocess);


        //affichage du tableau initial
        for(int r=0;r<nbprocess;r++){
            ui->tableWidget->setItem(r, 0, new TableItem(tab[r].num));
            ui->tableWidget->setItem(r, 1, new TableItem(tab[r].dateArr));
            ui->tableWidget->setItem(r, 2, new TableItem(tab[r].duree));
        }


        //ordonnancement selon la politique séléctionnée
        if(ui->fifo->isChecked()){
            fifo(tab,nbprocess);
        }
        if(ui->sjf->isChecked()){
            sjf(tab,nbprocess);
        }

        for(int r=0;r<nbprocess;r++){
            ui->result->setItem(r, 0, new TableItem(tab[r].num));
            ui->result->setItem(r, 1, new TableItem(tab[r].dateArr));
            ui->result->setItem(r, 2, new TableItem(tab[r].duree));
        }

        if(ui->rr->isChecked()){

            int verif,temps;
            vector<processus> aux;
            fifo(tab,nbprocess);
            temps=tab[0].dateArr;
            do{
                verif=0;
                for(int i=0;i<nbprocess;i++){
                    if(tab[i].duree > 0){
                        aux.push_back(tab[i]);
                        if(aux[aux.size()-1].duree >= quantum){
                            aux[aux.size()-1].duree -= quantum;
                            aux[aux.size()-1].dateArr =temps;
                            tab[i].duree -= quantum;
                            temps += quantum;
                        }else{
                            temps += aux[aux.size()-1].duree -quantum ;
                            aux[aux.size()-1].dateArr =temps;
                            tab[i].duree = 0;
                        }
                        verif=1;
                    }
                }
            }while(!(verif==0));


            for(int r=0;r<aux.size();r++){
                ui->result->setItem(r, 0, new TableItem(aux[r].num));
                ui->result->setItem(r, 1, new TableItem(aux[r].dateArr));
                ui->result->setItem(r, 2, new TableItem(aux[r].duree));
            }
        }
    }
}
