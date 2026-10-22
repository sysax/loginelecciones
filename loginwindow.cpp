#include "loginwindow.h"
#include <QVBoxLayout>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Sistema de Elecciones - Login");
    resize(350, 250);

    // Crear elementos de la interfaz
    txtMatricula = new QLineEdit(this);
    txtMatricula->setPlaceholderText("Matrícula de Estudiante");

    txtContrasena = new QLineEdit(this);
    txtContrasena->setPlaceholderText("Contraseña");
    txtContrasena->setEchoMode(QLineEdit::Password);

    btnIngresar = new QPushButton("Verificar e Ingresar", this);
    
    lblEstadoBD = new QLabel("Verificando conexión...", this);
    lblEstadoBD->setAlignment(Qt::AlignCenter);

    lblResultado = new QLabel("", this);
    lblResultado->setAlignment(Qt::AlignCenter);

    // Diseño de la ventana (Vertical)
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("<h3>Inicio de Sesión Estudiantil</h3>", this));
    layout->addWidget(txtMatricula);
    layout->addWidget(txtContrasena);
    layout->addWidget(btnIngresar);
    layout->addWidget(lblResultado);
    layout->addWidget(lblEstadoBD);

    // Conectar eventos
    connect(btnIngresar, &QPushButton::clicked, this, &LoginWindow::intentarLogin);

    // Intentar conectar a la base de datos al abrir la app
    conectarBD();
}

LoginWindow::~LoginWindow() {}

void LoginWindow::conectarBD() {
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost"); // En Linux Mint apunta a tu localhost donde corre Docker
    db.setPort(5433);
    db.setDatabaseName("prueba_elecciones");
    db.setUserName("mi_usuario");         // REEMPLAZA CON TU USUARIO DE DOCKER
    db.setPassword("mi_password_secreto");     // REEMPLAZA CON TU CONTRASEÑA DE DOCKER

    if (db.open()) {
        lblEstadoBD->setText("🟢 DB Conectada");
        lblEstadoBD->setStyleSheet("color: green; font-weight: bold;");
    } else {
        lblEstadoBD->setText("🔴 DB Error: " + db.lastError().text());
        lblEstadoBD->setStyleSheet("color: red; font-weight: bold;");
    }
}

void LoginWindow::intentarLogin() {
    QString matricula = txtMatricula->text();
    QString contrasena = txtContrasena->text();

    if (!db.isOpen()) {
        lblResultado->setText("❌ Error: No hay conexión con la base de datos.");
        lblResultado->setStyleSheet("color: orange;");
        return;
    }

    // Consulta segura utilizando placeholders para evitar Inyección SQL
    QSqlQuery query;
    query.prepare("SELECT * FROM usuarios WHERE matricula = :mat AND contrasena = :pass");
    query.bindValue(":mat", matricula);
    query.bindValue(":pass", contrasena);

    if (query.exec() && query.next()) {
        lblResultado->setText("🎉 SUCCESS: Datos correctos. ¡Bienvenido!");
        lblResultado->setStyleSheet("color: green; font-size: 14px; font-weight: bold;");
    } else {
        lblResultado->setText("❌ ERROR: Matrícula o contraseña incorrectas.");
        lblResultado->setStyleSheet("color: red; font-size: 14px; font-weight: bold;");
    }
}

