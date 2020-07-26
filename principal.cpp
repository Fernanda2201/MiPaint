#include "principal.h"
#include "ui_principal.h"

#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>
#include <QInputDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

#define DEFAULT_ANCHO 3


Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    // Instanciando la imagen (creando)
    mImagen= new QImage(this->size(),QImage::Format_ARGB32_Premultiplied);
    //Rellenar la imagen de color blanco
    mImagen->fill(Qt::white);
    // Instanciar el Painter a partir de la imagen
    mPainter = new QPainter(mImagen);
    mPainter->setRenderHint(QPainter::Antialiasing);
    // Inicializar otras variables
    mPuedeDibujar = false;
    mColor = Qt::black;
    mAncho = DEFAULT_ANCHO;
    mNumLineas =0;
    ui->actionLibre->setChecked(true);


}

Principal::~Principal()
{
    delete ui;
    delete mPainter;
    delete mImagen;
}

void Principal::paintEvent(QPaintEvent *event)
{
    //Crear el painter de la ventana principal
    QPainter painter(this);
    //Dibujar la imagen
    painter.drawImage(0,0, *mImagen);   //*mImage contenido del puntero
    //Aceptar el evento
    event->accept();
}

void Principal::mousePressEvent(QMouseEvent *event)
{
    mPuedeDibujar = true;
    mInicial=event->pos();
    event->accept();
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{

    if( ui->actionLibre->isChecked()){
        //Validar si se puede dibujar
        if(!mPuedeDibujar ){
            event->accept();
            return;
        }
        //Capturar el punto donde se suelta el mouse
        mFinal = event->pos();
        // Crear y establecer un pincel
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        // Dibujar una linea
        mPainter->setPen(pincel);
        mPainter->drawLine(mInicial,mFinal);
        //Aceptar el evento
        event->accept();

        //Mostrar el numero de lineas
        ui->statusbar->showMessage("Numero de lineas: "+ QString::number(++mNumLineas));
        //Actualizar interfaz
        update();
        // actualiza punto inicial
        mInicial=mFinal;

    }
}

void Principal::mouseReleaseEvent(QMouseEvent *event)
{
    mPuedeDibujar = false;
    if(ui->actionLineas->isChecked()){

        //Capturar el punto donde se suelta el mouse
        mFinal = event->pos();
        // Crear y establecer un pincel
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        // Dibujar una linea
        mPainter->setPen(pincel);
        mPainter->drawLine(mInicial,mFinal);
        mInicial=mFinal;
        event->accept();
        ui->actionLibre->setChecked(false);
        ui->actionRectangulos->setChecked(false);
        ui->actionCirculos->setChecked(false);
        update();
    }else if(ui->actionRectangulos->isChecked()){
        //Capturar el punto donde se suelta el mouse
        mFinal = event->pos();
        //Declarar los puntos del rectangulo
        QRect puntos(mInicial,mFinal);
        // Crear y establecer un pincel
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        //Establecer el pincel al painter
        mPainter->setPen(pincel);
        // Dibujar un rectangulo
        mPainter->drawRect(puntos);
        //Aceptar el eveneto
        event->accept();
        //Actualizar la interfaz
        ui->actionLibre->setChecked(false);
        ui->actionLineas->setChecked(false);
        ui->actionCirculos->setChecked(false);
        update();
        //Actualiza el punto inicial
        mInicial=mFinal;
    }else if(ui->actionCirculos->isChecked()){
        //Capturar el punto donde se suelta el mouse
        mFinal = event->pos();
        //Declarar los puntos del rectangulo
        QRect puntos(mInicial,mFinal);
        // Crear y establecer un pincel
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        //Establecer el pincel al painter
        mPainter->setPen(pincel);
        // Dibujar un circulo
        mPainter->drawEllipse(puntos);
        //Aceptar el eveneto
        event->accept();
        //Actualizar la interfaz
        update();
        //Actualiza el punto inicial
        mInicial=mFinal;
    }

}


void Principal::on_actionAncho_triggered()
{
    mAncho=QInputDialog::getInt(this, "Ancho del pincel",
                                "Ingrese el ancho del pincel de dibujo",
                                mAncho,
                                1,100);
}

void Principal::on_actionSalir_triggered()
{
    this->close();
}

void Principal::on_actionColor_triggered()
{
    mColor=QColorDialog::getColor(mColor,
                                  this,
                                  "Color del pincel");
}

void Principal::on_actionNuevo_triggered()
{
    mImagen->fill(Qt::white);
    mNumLineas = 0;
    update();
}

void Principal::on_actionGuardar_triggered()
{
    QString nombreArchivo= QFileDialog::getSaveFileName(this,
                                                        "Guardar imagen",
                                                        QString(),"Imagenes (*.png");
    if(!nombreArchivo.isEmpty()){
        if(mImagen->save(nombreArchivo))
            QMessageBox::information(this,
                                     "Guaradar imagen",
                                     "Archivoalamecnado en: "+ nombreArchivo);
        else
            QMessageBox::warning(this,
                                 "Guardar imagen",
                                 "No se puedo alamecenar la imagen.");
    }
}


