# Liaison Frontend Qt - Backend .NET API

## Vue d'ensemble

Ce projet utilise une architecture client-serveur où :

- **Frontend** : Application Qt (C++) avec interface graphique
- **Backend** : API REST .NET Core avec base de données MySQL

## Architecture

### Frontend Qt

- `mainwindow.cpp/h` : Interface principale avec formulaire et tableau
- `apiclient.cpp/h` : Classe pour communiquer avec l'API REST
- `config.h` : Configuration centralisée (URLs, timeouts, etc.)

### Backend .NET

- `StudentsController.cs` : Contrôleur API avec endpoints CRUD
- `Student.cs` : Modèle de données
- `AppDbContext.cs` : Contexte Entity Framework

## Communication

### Protocole

- **HTTP/HTTPS** : Communication entre Qt et .NET
- **JSON** : Format d'échange de données
- **REST** : Architecture API

### Endpoints utilisés

```
GET    /api/Students          - Récupérer tous les étudiants
GET    /api/Students/{id}     - Récupérer un étudiant
POST   /api/Students          - Ajouter un étudiant
PUT    /api/Students/{id}     - Modifier un étudiant
DELETE /api/Students/{id}     - Supprimer un étudiant
```

## Configuration

### URL de l'API

Modifiez `config.h` pour changer l'URL de l'API :

```cpp
const QString API_BASE_URL = "http://localhost:5000/api/Students";
```

### Ports par défaut

- **API .NET** : `http://localhost:5000`
- **Swagger UI** : `http://localhost:5000/swagger`

## Démarrage

### 1. Démarrer l'API .NET

```bash
cd connexion/MonProjetAPI
dotnet run
```

### 2. Démarrer l'application Qt

```bash
# Compiler
cmake --build build

# Exécuter
./build/QT_Students_Information_Managements_System
```

## Fonctionnalités

### Interface Qt

- **Add** : Ajouter un nouvel étudiant
- **Update** : Modifier un étudiant sélectionné
- **Select** : Charger un étudiant dans le formulaire
- **Search** : Rechercher des étudiants
- **Clear** : Vider le formulaire
- **Delete** : Supprimer un étudiant

### Gestion des erreurs

- Connexion refusée (API non démarrée)
- Hôte non trouvé (URL incorrecte)
- Timeout (délai d'attente dépassé)
- Erreurs de validation

## Sécurité

### HTTPS

L'API utilise HTTPS par défaut. Pour le développement, vous pouvez :

1. Accepter les certificats auto-signés
2. Utiliser HTTP en développement (non recommandé en production)

### Validation

- Validation côté client (Qt)
- Validation côté serveur (.NET)
- Messages d'erreur localisés

## Développement

### Ajouter de nouveaux champs

1. Modifier `Student.cs` (backend)
2. Modifier `Student` dans `apiclient.h` (frontend)
3. Mettre à jour l'interface Qt
4. Ajouter la migration Entity Framework

### Ajouter de nouvelles fonctionnalités

1. Créer l'endpoint dans `StudentsController.cs`
2. Ajouter la méthode dans `ApiClient`
3. Connecter l'interface Qt

## Dépannage

### Erreurs courantes

1. **"Connexion refusée"** : Vérifiez que l'API .NET est démarrée
2. **"Hôte non trouvé"** : Vérifiez l'URL dans `config.h`
3. **"Erreur SSL"** : Vérifiez que l'URL utilise HTTP et non HTTPS
4. **Erreurs de compilation** : Vérifiez les dépendances Qt Network

### Logs

- Qt : Utilisez `qDebug()` pour les logs
- .NET : Logs dans la console ou fichier

## Performance

### Optimisations

- Requêtes asynchrones
- Mise en cache des données
- Pagination pour de grandes listes
- Compression HTTP

### Monitoring

- Temps de réponse des requêtes
- Utilisation mémoire
- Erreurs réseau
