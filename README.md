# Projet : Conception d'une application tchat d'assistance multi-niveaux

## Mission

L'objectif de ce projet est de développer une application de tchat multi-niveaux en utilisant un couple client-serveur TCP.

Nous développerons cette application à l'aide du langage C.

L'application doit permettre une communication sur trois niveaux :
* **Niveau 1** : Communication avec un robot automatique. Il doit pouvoir traiter des requêtes simples reconnaissable avec des mots clés.
* **Niveau 2** : Communication avec un technicien si le niveau 1 n'a pas suffit à trouver une solution.
* **Niveau 3** : Communication avec un expert du domaine si le niveau 2 a échoué à trouver une solution

Le niveaux de techniciens et d'experts est variable. On considère que ceux-ci sont localisés sur des sites différents et sont contactés en parallèle.

## Démarrer l'application 
### Récupérer le dépôt sur git

```
git clone https://gitlab.telecomnancy.univ-lorraine.fr/Dylan.Fournier/projectrsa.git

cd projectRSA

code .
```

### Compiler l'application

```bash
# En utilisant le Makefile
make projectRSA

# En utilisant le compilateur gcc
rm build/*
gcc -c src/projectRSA_client.c -o build/projectRSA_client.o
gcc -c src/projectRSA_serv.c -o build/projectRSA_serv.o
gcc build/projectRSA_client.o -o build/projectRSA_client
gcc build/projectRSA_serv.o -o build/projectRSA_serv
```

### Compiler le serveur

```bash
# En utilisant le Makefile
make projectRSA_serv

# En utilisant le compilateur gcc
gcc -c src/projectRSA_serv.c -o build/projectRSA_serv.o
gcc build/projectRSA_serv.o -o build/projectRSA_serv
```

### Compiler le client

```bash
# En utilisant le Makefile
make projectRSA_client

# En utilisant le compilateur gcc
gcc -c src/projectRSA_client.c -o build/projectRSA_client.o
gcc build/projectRSA_client.o -o build/projectRSA_client
```

### Exécuter le serveur

```bash
./build/projectRSA_serv
```
### Exécuter le client

```bash
./build/projectRSA_client
```

## Les différents niveaux

### Niveau 1 : Robots automatiques

### Niveau 2 : Techniciens

### Niveau 3 : Experts


