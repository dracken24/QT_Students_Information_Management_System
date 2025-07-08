#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>

class Student {
public:
    int id;
    QString firstName;
    QString lastName;
    QString city;
    QString state;
    QString email;
    
    QJsonObject toJson() const;
    static Student fromJson(const QJsonObject& json);
};

class ApiClient : public QObject
{
    Q_OBJECT

public:
    explicit ApiClient(QObject *parent = nullptr);
    ~ApiClient();

    // Méthodes pour interagir avec l'API
    void getStudents();
    void getStudent(int id);
    void addStudent(const Student &student);
    void updateStudent(const Student &student);
    void deleteStudent(int id);

signals:
    void studentsReceived(const QList<Student> &students);
    void studentReceived(const Student &student);
    void studentAdded(const Student &student);
    void studentUpdated();
    void studentDeleted();
    void errorOccurred(const QString &error);

private slots:
    void handleGetStudentsReply();
    void handleGetStudentReply();
    void handleAddStudentReply();
    void handleUpdateStudentReply();
    void handleDeleteStudentReply();
    void handleNetworkError(QNetworkReply::NetworkError error);

private:
    QNetworkAccessManager *m_networkManager;
    QString m_baseUrl;
    
    QNetworkReply* sendRequest(const QString &endpoint, const QString &method, const QJsonDocument &data = QJsonDocument());
};

#endif // APICLIENT_H 