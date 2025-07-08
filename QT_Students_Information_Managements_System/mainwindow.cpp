#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_apiClient(new ApiClient(this))
{
    ui->setupUi(this);
    setupConnections();
    loadStudents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    // Connexions avec l'API
    connect(m_apiClient, &ApiClient::studentsReceived, this, &MainWindow::onStudentsReceived);
    connect(m_apiClient, &ApiClient::studentReceived, this, &MainWindow::onStudentReceived);
    connect(m_apiClient, &ApiClient::studentAdded, this, &MainWindow::onStudentAdded);
    connect(m_apiClient, &ApiClient::studentUpdated, this, &MainWindow::onStudentUpdated);
    connect(m_apiClient, &ApiClient::studentDeleted, this, &MainWindow::onStudentDeleted);
    connect(m_apiClient, &ApiClient::errorOccurred, this, &MainWindow::onErrorOccurred);
    
    // Configuration du tableau
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::loadStudents()
{
    m_apiClient->getStudents();
}

void MainWindow::clearForm()
{
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
    ui->textEdit_4->clear();
    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox_2->setCurrentIndex(-1);
}

void MainWindow::populateForm(const Student &student)
{
    ui->textEdit->setPlainText(QString::number(student.id));
    ui->textEdit_2->setPlainText(student.firstName);
    ui->textEdit_3->setPlainText(student.lastName);
    ui->textEdit_4->setPlainText(student.email);
    
    // Trouver et sélectionner les valeurs dans les combobox
    int cityIndex = ui->comboBox_2->findText(student.city);
    if (cityIndex >= 0) ui->comboBox_2->setCurrentIndex(cityIndex);
    
    int stateIndex = ui->comboBox->findText(student.state);
    if (stateIndex >= 0) ui->comboBox->setCurrentIndex(stateIndex);
}

Student MainWindow::getStudentFromForm()
{
    Student student;
    student.id = ui->textEdit->toPlainText().toInt();
    student.firstName = ui->textEdit_2->toPlainText();
    student.lastName = ui->textEdit_3->toPlainText();
    student.email = ui->textEdit_4->toPlainText();
    student.city = ui->comboBox_2->currentText();
    student.state = ui->comboBox->currentText();
    return student;
}

void MainWindow::showMessage(const QString &title, const QString &message)
{
    QMessageBox::information(this, title, message);
}

// Slots pour les boutons "on_nomDuButton_clicked"
void MainWindow::on_pushButton_clicked() // Add
{
    Student student = getStudentFromForm();
    std::cout << "Add clicked: " << student.firstName.toStdString() << std::endl;

    if (student.firstName.isEmpty() || student.lastName.isEmpty())
    {
        showMessage("Erreur", "Le prénom et le nom sont obligatoires.");
        return;
    }
    
    m_apiClient->addStudent(student);
}

void MainWindow::on_pushButton_2_clicked() // Update
{
    Student student = getStudentFromForm();

    if (student.id <= 0)
    {
        showMessage("Erreur", "Veuillez sélectionner un étudiant à modifier.");
        return;
    }
    
    m_apiClient->updateStudent(student);
}

void MainWindow::on_pushButton_3_clicked() // Select
{
    int currentRow = ui->tableWidget->currentRow();

    if (currentRow >= 0)
    {
        int studentId = ui->tableWidget->item(currentRow, 0)->text().toInt();
        m_apiClient->getStudent(studentId);
    }
    else
    {
        showMessage("Erreur", "Veuillez sélectionner un étudiant dans le tableau.");
    }
}

void MainWindow::on_pushButton_4_clicked() // Search
{
    // Pour l'instant, on recharge tous les étudiants
    // Vous pouvez implémenter une recherche plus sophistiquée ici
    loadStudents();
}

void MainWindow::on_pushButton_5_clicked() // Clear
{
    clearForm();
}

void MainWindow::on_pushButton_6_clicked() // Delete
{
    int currentRow = ui->tableWidget->currentRow();

    if (currentRow >= 0)
    {
        int studentId = ui->tableWidget->item(currentRow, 0)->text().toInt();
        
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", 
            "Êtes-vous sûr de vouloir supprimer cet étudiant ?",
            QMessageBox::Yes | QMessageBox::No);
            
        if (reply == QMessageBox::Yes)
        {
            m_apiClient->deleteStudent(studentId);
        }
    }
    else
    {
        showMessage("Erreur", "Veuillez sélectionner un étudiant à supprimer.");
    }
}

// Slots pour les réponses de l'API
void MainWindow::onStudentsReceived(const QList<Student> &students)
{
    ui->tableWidget->setRowCount(students.size());
    
    for (int i = 0; i < students.size(); ++i)
    {
        const Student &student = students[i];
        
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(student.id)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(student.firstName));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(student.lastName));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(student.city));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(student.state));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(student.email));
    }
}

void MainWindow::onStudentReceived(const Student &student)
{
    populateForm(student);
}

void MainWindow::onStudentAdded(const Student &student)
{
    showMessage("Succès", "Étudiant ajouté avec succès !");
    clearForm();
    loadStudents(); // Recharger la liste
}

void MainWindow::onStudentUpdated()
{
    showMessage("Succès", "Étudiant modifié avec succès !");
    loadStudents(); // Recharger la liste
}

void MainWindow::onStudentDeleted()
{
    showMessage("Succès", "Étudiant supprimé avec succès !");
    loadStudents(); // Recharger la liste
}

void MainWindow::onErrorOccurred(const QString &error)
{
    std::cout << "Error: " << error.toStdString() << std::endl;
    showMessage("Erreur", error);
}
