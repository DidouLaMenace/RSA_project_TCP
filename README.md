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
```

### Compiler l'application

```bash
# En utilisant le Makefile
make clean
make projectrsa

# En utilisant le compilateur gcc
rm build/*
gcc -c src/robots.c -o build/robots.o
gcc -c src/technician.c -o build/technician.o
gcc -c src/expert.c -o build/expert.o
gcc -c src/client_rsa.c -o build/client_rsa.o
gcc -c src/server_rsa.c -o build/server_rsa.o
gcc build/client_rsa.o -o build/client_rsa
gcc build/server_rsa.o -o build/server_rsa
```

### Exécution

#### Exécuter le serveur

```bash
./build/server_rsa
```
#### Exécuter le client

Le fichier *client_rsa.c* doit être exécuté avec un argument "client,technician,expert".

Pour connecter un client on effectue la commande suivante :
```bash
./build/client_rsa client
```

Pour connecter un technician on effectue la commande suivante :
```bash
./build/client_rsa technician
```

Pour connecter un expert on effectue la commande suivante :
```bash
./build/client_rsa expert
```

Le technicien et l'expert attendent jusqu'à réception d'une requête.

## Fonctionnement

### Message envoyé au robot

* Une fois le client connecté au serveur, il peut écrire sa demande.
* La demande sera d'abord envoyé au robot. 
* Si le robot reconnait un mot clé, il enverra la réponse prédéfini pour le type de réponse.

### Message envoyé au technicien
* Si aucun mot clé n'est reconnu par le robot, le message est envoyé à un technicien.
* Lorsque le technicien reçoit le message il peut y répondre. 
* Le message sera retourné au client qui pourra ainsi lire la réponse.

### Message envoyé à un expert
* Si aucun mot clé n'est reconnu par le robot, le message est envoyé à un technicien.
* Si le technicien n'est pas en mesure de répondre à la requête du client il peut utiliser la commande **NULL** en guise de réponse.
* Lorsque le serveur lira la réponse **NULL** du technicien, le serveur enverra la requête à un expert.
* L'expert reçoit le message et peut donc y répondre.

### Quitter le serveur

Pour quitter le serveur, les techniciens et les experts peuvent utiliser la commande **EXIT**.

### Vidéo de test

Nous vous invitons à lire les vidéos suivantes, montrant les exemples d'utilisation de l'application de chat.




## Détails de l'implémentation

### Le client

Si il y a une demande trop importante des clients (c'est à dire s'il y a plus de requête que de techniciens et d'experts réunis), nous avons mis en place un système d'attente. La requête du client sera mis dans une pile en attendant qu'un technicien ou un expert se libère.

### Une application de chat sur 3 niveaux

Le serveur TCP se base sur 3 niveaux :
* Lorsque le client envoie une requête au serveur, on teste le robot pour savoir s'il peut proposer une réponse. Si le robot est dans l'incapacité de répondre, la requête est envoyé à un technicien.
* Le technicien examine la requête. Si le technicien ne peut pas répondre, alors la requête est envoyé à un expert.
* L'expert examine la requête. Si l'expert est dans l'incapacité de répondre, un message est envoyé au client indiquant que personne n'a pu accéder à sa requête.

Un message peut contenir 2000 caractères maximum. Ce nombre peut être modifié selon les utilisations.

### Niveau 1 : Robots automatiques

Dans le fichier *robot.c*, la fonction *strstr* nous permet d'identifier des mots clés dans la requête du client.
En fonction des mots clés, le robot pourra proposer ou non une réponse approprié.
Si aucune réponse appropriée n'est trouvé, la requête est envoyé à un technicien.

### Niveau 2 : Techniciens

Les techniciens sont réprésentés par une structure de donnée. 
Ils ont pour argument :
* le socket 
* l'adresse IP
* le numéro de port
* leur état (status) égale à 1 si le technicien en question est occupé et 0 sinon.

L'ensemble des techniciens est représenté par une liste chaînée.
Le nombre maximal de techniciens est fixé à 10. On peut modifier ce nombre selon les utilisations.

Lorsque le technicien se connecte au serveur, il attend jusqu'à réception d'une requête.
A la réception de celle-ci, le technicien peut répondre à la requête.
Si le technicien est dans l'incapacité de répondre, il peut utiliser la commande **NULL** qui permet d'envoyer la requête à un expert.

Lorsque le technicien ne souhaite plus attendre de requête, il peut utiliser la commande **EXIT** qui interrompera sa connection avec le serveur.

**NULL** peut seulement s'utiliser lorsque le technicien reçoit une requête. C'est à dire lorsque *"Enter your response* est affiché sur le terminal.
**EXIT** doit être utiliser quand le technicien n'est pas en train de recevoir une requête.

Par ailleurs, si un technicien écrit dans le terminal sans avoir reçu de requête cela ne provoque pas de bug.

### Niveau 3 : Experts

Les experts sont réprésentés par une structure de donnée. 
Ils ont pour argument :
* le socket 
* l'adresse IP
* le numéro de port
* leur état (status) égale à 1 si le technicien en question est occupé et 0 sinon.

L'ensemble des experts est représenté par une liste chaînée.
Le nombre maximal d'experts est fixé à 10. On peut modifier ce nombre selon les utilisations.

Lorsque l'expert se connecte au serveur, il attend jusqu'à réception d'une requête.
A la réception de celle-ci, l'expert peut répondre à la requête.
Si l'expert est dans l'incapacité de répondre, il peut utiliser la commande **NULL** qui permet d'envoyer un message d'erreur au client.

Lorsque l'expert ne souhaite plus attendre de requête, il peut utiliser la commande **EXIT** qui interrompera sa connection avec le serveur.

**NULL** peut seulement s'utiliser lorsque l'expert reçoit une requête. C'est à dire lorsque *"Enter your response* est affiché sur le terminal.
**EXIT** doit être utiliser quand le technicien n'est pas en train de recevoir une requête.

Par ailleurs, si un expert écrit dans le terminal sans avoir reçu de requête cela ne provoque pas de bug.

## Piste d'amélioration

* Nous n'avons pas réussi à prendre en compte le fait qu'un technicien ou un expert puisse utiliser Ctrl+C ou Ctrl+Z pour quitter le serveur. L'utilisation de ces raccourcis provoque des bugs dans le code.

* Nous avons également constater un bug lorsque trop de techniciens sont connectés. En effet comme voulu, si le nombre maximum de technicien est atteint, plus aucun technicien ne peut se connecter, même si d'autre technicien se déconnecte entre temps. Ce qui pose un problème. Cependant nous pouvons considérer que les 10 mêmes techniciens sont connectés en permanance avec le serveur. On observe le même problème pour les experts. Nous avons identifié le problème mais nous n'avons pas pu mettre en place une solution.

* Il aurait été utile de fermer tous les sockets connectés au server lorsqu'on ferme le serveur.


