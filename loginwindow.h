#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QtSql/QSqlDatabase>

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void intentarLogin();

private:
    void conectarBD();

    QLineEdit *txtMatricula;
    QLineEdit *txtContrasena;
    QPushButton *btnIngresar;
    QLabel *lblEstadoBD;
    QLabel *lblResultado;
    
    QSqlDatabase db;
};

#endif // LOGINWINDOW_H

