#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // set fixed size
    setFixedSize(125, 100);

    // create main (vertical) layoutout
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // create horizontal layout
    QHBoxLayout *hLayout = new QHBoxLayout;

    // create fahrehnheit label
    QLabel *fahrenheitLabel = new QLabel("ºF", this);

    // create fahrenheit entry
    fahrenheitEntry = new QLineEdit(this);

    // create submit button
    QPushButton *submitBtn = new QPushButton("Submit", this);

    hLayout->addWidget(fahrenheitEntry);
    hLayout->addWidget(fahrenheitLabel);

    // prevents fahrenheitEntry from receiving letters or symbols
    QDoubleValidator *validator = new QDoubleValidator(-1e9, 1e9, 2, fahrenheitEntry);
    validator->setNotation(QDoubleValidator::StandardNotation);
    fahrenheitEntry->setValidator(validator);
    validator->setLocale(QLocale::c());

    mainLayout->addLayout(hLayout);
    mainLayout->addWidget(submitBtn);

    // add the main layout to the container
    QWidget *container = new QWidget();
    container->setLayout(mainLayout);
    setCentralWidget(container);

    // prevents the button from working if fahrenheitEntry is empty
    connect(fahrenheitEntry, &QLineEdit::textChanged, this, [submitBtn](const QString &text) {
        submitBtn->setEnabled(!text.trimmed().isEmpty());
    });
    submitBtn->setEnabled(false);

    connect(submitBtn, &QPushButton::clicked, this, &MainWindow::submitBtnClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::submitBtnClick(){
    f2c f2c(fahrenheitEntry->text().toFloat());
    QDialog popup(this);
    popup.setWindowTitle("f2c");
    popup.setFixedSize(100, 90);

    QVBoxLayout *layout = new QVBoxLayout(&popup);

    QHBoxLayout *hLayout = new QHBoxLayout;

    hLayout->addWidget(new QLabel(QString::number(f2c.getC(), 'g', 2)+" ºC"), Qt::AlignHCenter);

    layout->addLayout(hLayout);

    QPushButton *okBtn = new QPushButton("OK", this);
    layout->addWidget(okBtn);

    connect(okBtn, &QPushButton::clicked, [&popup]() {
        popup.close();
    });

    popup.exec();
}
