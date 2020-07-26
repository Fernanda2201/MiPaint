#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();


protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void on_actionAncho_triggered();

    void on_actionSalir_triggered();

    void on_actionColor_triggered();

    void on_actionNuevo_triggered();

    void on_actionGuardar_triggered();





private:
    Ui::Principal *ui;

    QImage *mImagen;        //Imagen donde se va a dibujar

    QPainter *mPainter;     //Painter de la imagen

    QPoint mInicial;        //Punto inicial para dibujar la linea

    QPoint mFinal;          //Punto final para dibujar la linea;

    bool mPuedeDibujar;     //Dtermina si debe o no debe dibujar

    int mAncho;             //Define el ancho del pincel

    QColor mColor;          //Define el color con el que se dibuja

    int mNumLineas;

    bool mEstaClickeado;    //Define que boton utilizando




};
#endif // PRINCIPAL_H
