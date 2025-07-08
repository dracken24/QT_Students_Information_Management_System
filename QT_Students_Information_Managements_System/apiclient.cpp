#include "apiclient.h"
#include "config.h"
#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QDebug>
#include <iostream>

// Implémentation de la classe Student
QJsonObject Student::toJson() const
{
    QJsonObject obj;
    obj["id"] = id;
    obj["firstName"] = firstName;
    obj["lastName"] = lastName;
    obj["city"] = city;
    obj["state"] = state;
    obj["email"] = email;
    return obj;
}

Student Student::fromJson(const QJsonObject& json)
{
    Student student;

    student.id = json["id"].toInt();
    student.firstName = json["firstName"].toString();
    student.lastName = json["lastName"].toString();
    student.city = json["city"].toString();
    student.state = json["state"].toString();
    student.email = json["email"].toString();

    return student;
}

// Implémentation de la classe ApiClient
ApiClient::ApiClient(QObject *parent) :
QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
    , m_baseUrl(Config::API_BASE_URL)
{
    connect(m_networkManager, &QNetworkAccessManager::finished, this, [this](QNetworkReply *reply)
    {
        // Gestion automatique des erreurs réseau
        if (reply->error() != QNetworkReply::NoError)
        {
            handleNetworkError(reply->error());
        }
    });
}

ApiClient::~ApiClient()
{
}

void ApiClient::getStudents()
{
    QNetworkReply *reply = sendRequest("", "GET");
    if (reply)
    {
        connect(reply, &QNetworkReply::finished, this, &ApiClient::handleGetStudentsReply);
    }
}

void ApiClient::getStudent(int id)
{
    QNetworkReply *reply = sendRequest(QString("/%1").arg(id), "GET");
    if (reply) {
        connect(reply, &QNetworkReply::finished, this, &ApiClient::handleGetStudentReply);
    }
}

void ApiClient::addStudent(const Student &student)
{
    QJsonDocument doc(student.toJson());
    std::cout << "Add student: " << doc.toJson().toStdString() << std::endl;
    QNetworkReply *reply = sendRequest("", "POST", doc);
    if (reply)
    {
        connect(reply, &QNetworkReply::finished, this, &ApiClient::handleAddStudentReply);
    }
}

void ApiClient::updateStudent(const Student &student)
{
    QJsonDocument doc(student.toJson());
    QNetworkReply *reply = sendRequest(QString("/%1").arg(student.id), "PUT", doc);
    if (reply) {
        connect(reply, &QNetworkReply::finished, this, &ApiClient::handleUpdateStudentReply);
    }
}

void ApiClient::deleteStudent(int id)
{
    QNetworkReply *reply = sendRequest(QString("/%1").arg(id), "DELETE");
    if (reply)
    {
        connect(reply, &QNetworkReply::finished, this, &ApiClient::handleDeleteStudentReply);
    }
}

QNetworkReply* ApiClient::sendRequest(const QString &endpoint, const QString &method, const QJsonDocument &data)
{
    QUrl url(m_baseUrl + endpoint);
    QNetworkRequest request(url);
    
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    std::cout << "Sending request to: " << url.toString().toStdString() << std::endl;
    std::cout << "Method: " << method.toStdString() << std::endl;
    
    QNetworkReply *reply = nullptr;
    
    if (method == "GET")
    {
        reply = m_networkManager->get(request);
    } else if (method == "POST")
    {
        reply = m_networkManager->post(request, data.toJson());
    } else if (method == "PUT")
    {
        reply = m_networkManager->put(request, data.toJson());
    } else if (method == "DELETE")
    {
        reply = m_networkManager->deleteResource(request);
    }
    
    if (reply)
    {
        connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError error)
        {
            std::cout << "Network error: " << error << " - " << reply->errorString().toStdString() << std::endl;
        });
    }
    
    return reply;
}

void ApiClient::handleGetStudentsReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;
    
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray array = doc.array();
        
        QList<Student> students;
        for (const QJsonValue &value : array) {
            students.append(Student::fromJson(value.toObject()));
        }
        
        emit studentsReceived(students);
    } else {
        emit errorOccurred(reply->errorString());
    }
    
    reply->deleteLater();
}

void ApiClient::handleGetStudentReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;
    
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        Student student = Student::fromJson(doc.object());
        emit studentReceived(student);
    } else {
        emit errorOccurred(reply->errorString());
    }
    
    reply->deleteLater();
}

void ApiClient::handleAddStudentReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;
    
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        Student student = Student::fromJson(doc.object());
        emit studentAdded(student);
    } else {
        emit errorOccurred(reply->errorString());
    }
    
    reply->deleteLater();
}

void ApiClient::handleUpdateStudentReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;
    
    if (reply->error() == QNetworkReply::NoError) {
        emit studentUpdated();
    } else {
        emit errorOccurred(reply->errorString());
    }
    
    reply->deleteLater();
}

void ApiClient::handleDeleteStudentReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;
    
    if (reply->error() == QNetworkReply::NoError) {
        emit studentDeleted();
    } else {
        emit errorOccurred(reply->errorString());
    }
    
    reply->deleteLater();
}

void ApiClient::handleNetworkError(QNetworkReply::NetworkError error)
{
    QString errorString;
    switch (error) {
        case QNetworkReply::ConnectionRefusedError:
            errorString = Config::ERROR_CONNECTION_REFUSED;
            break;
        case QNetworkReply::HostNotFoundError:
            errorString = Config::ERROR_HOST_NOT_FOUND;
            break;
        case QNetworkReply::TimeoutError:
            errorString = Config::ERROR_TIMEOUT;
            break;
        case QNetworkReply::SslHandshakeFailedError:
            errorString = "Erreur SSL. Vérifiez que l'API utilise HTTP et non HTTPS.";
            break;
        case QNetworkReply::ProtocolUnknownError:
            errorString = "Protocole inconnu. Vérifiez l'URL de l'API.";
            break;
        default:
            errorString = QString("Erreur réseau: %1").arg(error);
            break;
    }
    
    emit errorOccurred(errorString);
} 