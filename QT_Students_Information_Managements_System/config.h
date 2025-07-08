#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

namespace Config
{
    // URL de base de l'API .NET
    const QString API_BASE_URL = "http://localhost:5000/api/Students";
    
    // Timeout pour les requêtes réseau (en millisecondes)
    const int NETWORK_TIMEOUT = 10000;
    
    // Configuration des messages d'erreur
    const QString ERROR_CONNECTION_REFUSED = "Connexion refusée. Vérifiez que l'API .NET est en cours d'exécution.";
    const QString ERROR_HOST_NOT_FOUND = "Hôte non trouvé. Vérifiez l'URL de l'API.";
    const QString ERROR_TIMEOUT = "Délai d'attente dépassé.";
    const QString ERROR_UNKNOWN = "Erreur réseau inconnue.";
}

#endif // CONFIG_H 