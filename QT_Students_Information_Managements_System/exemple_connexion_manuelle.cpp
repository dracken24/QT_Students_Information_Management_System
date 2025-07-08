// Exemple de connexion manuelle (alternative à la convention automatique)

void MainWindow::setupConnections()
{
    // Connexion manuelle au lieu de la convention automatique
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::handleAddButton);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::handleUpdateButton);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::handleSelectButton);
    
    // Connexions avec l'API
    connect(m_apiClient, &ApiClient::studentsReceived, this, &MainWindow::onStudentsReceived);
    // ... autres connexions
}

// Slots avec noms personnalisés
void MainWindow::handleAddButton()
{
    // Même logique que on_pushButton_clicked()
    Student student = getStudentFromForm();
    m_apiClient->addStudent(student);
}

void MainWindow::handleUpdateButton()
{
    // Même logique que on_pushButton_2_clicked()
    Student student = getStudentFromForm();
    m_apiClient->updateStudent(student);
}

void MainWindow::handleSelectButton()
{
    // Même logique que on_pushButton_3_clicked()
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0) {
        int studentId = ui->tableWidget->item(currentRow, 0)->text().toInt();
        m_apiClient->getStudent(studentId);
    }
} 