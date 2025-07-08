La base de donne est MySQL
SELECT * FROM studentsdb.students;

1:lancer le projet
dotnet run

2: Appeler la database
curl http://localhost:5000/api/Students

on browser:
http://localhost:5000/swagger/index.html


Comment c'est connecter:

'Listener dans .h'

private slots:
    void on_pushButton_clicked();      // Add

on_ : Préfixe obligatoire
pushButton : Nom de l'objet dans le fichier .ui
clicked : Nom du signal du bouton


