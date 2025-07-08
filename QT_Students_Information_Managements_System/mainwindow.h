#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QMessageBox>
#include "apiclient.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_pushButton_clicked();      // Add
        void on_pushButton_2_clicked();    // Update
        void on_pushButton_3_clicked();    // Select
        void on_pushButton_4_clicked();    // Search
        void on_pushButton_5_clicked();    // Clear
        void on_pushButton_6_clicked();    // Delete
        
        // Slots pour les réponses de l'API
        void onStudentsReceived(const QList<Student> &students);
        void onStudentReceived(const Student &student);
        void onStudentAdded(const Student &student);
        void onStudentUpdated();
        void onStudentDeleted();
        void onErrorOccurred(const QString &error);

    private:
        Ui::MainWindow *ui;
        ApiClient *m_apiClient;
        
        void setupConnections();
        void loadStudents();
        void clearForm();
        void populateForm(const Student &student);
        Student getStudentFromForm();
        void showMessage(const QString &title, const QString &message);
};

#endif // MAINWINDOW_H
