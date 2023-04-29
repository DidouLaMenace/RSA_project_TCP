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

#### Compiler le serveur

```bash
# En utilisant le Makefile
make projectrsa_serv

# En utilisant le compilateur gcc
gcc -c src/server_rsa.c -o build/server_rsa.o
gcc build/server_rsa.o -o build/server_rsa
```

#### Compiler le client

```bash
# En utilisant le Makefile
make projectrsa_client

# En utilisant le compilateur gcc
gcc -c src/client_rsa.c -o build/client_rsa.o
gcc build/client_rsa.o -o build/client_rsa
```

### Exécution

#### Exécuter le serveur

```bash
./build/server_rsa
```
#### Exécuter le client

Le fichier *client_rsa.c* contrôle les trois entités suivantes : Client, Technicien et Expert.

Si un client souhaite se connecter au serveur, il lui suffit d'écrire la commande :
```bash
./build/client_rsa client
```
Le client peut ensuite écrire sa requête.


#### Exécuter le technicien
Si un technicien prend ses fonctions et souhaite se connecter au serveur, il peut utiliser :
```bash
./build/client_rsa technician
```
Le technicien peut ensuite attendre jusqu'à réception d'une requête.

#### Exécuter l'expert
Si un expert souhaite également prendre ses fonctions il peut utiliser : 
```bash
./build/client_rsa expert
```
L'expert peut ensuite attendre jusqu'à réception d'une requête.


## Les différents niveaux

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


## Exemple d'utilisation

**Mise en place du programme**
Dans un terminal, tapez les commandes suivantes : 
```
git clone https://gitlab.telecomnancy.univ-lorraine.fr/Dylan.Fournier/projectrsa.git

cd projectRSA

make projectrsa
```

**On démarre le serveur**
Ouvrez un terminal et tapez la commande suivante :

```bash
./build/server_rsa
```

**Les techniciens et les experts se connectent au serveur**
Ouvrez un terminal et tapez la commande suivante pour un technicien:

```bash
./build/client_rsa technician
```

Ouvrez un terminal et tapez la commande suivante pour un expert:

```bash
./build/client_rsa expert
```

Réitérez ces commandes en fonction du nombre de techniciens et d'experts que vous avez besoin.

**Le client se connecte au serveur**

Ouvrez un terminal et tapez la commande suivante :

```bash
./build/client_rsa client
```

Le client peut maintenant écrire sa requête et l'envoyer avec la touche *Entrée*. Vous pouvez désormais regarder les shell des techniciens et des experts pour savoir où a été reçu le message du client et pour y répondre.


