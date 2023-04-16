projectRSA:
	gcc -c projectRSA_client.c projectRSA_serv.c
	gcc -o projectRSA_client projectRSA_client.o
	gcc -o projectRSA_serv projectRSA_serv.o

projectRSA_client:
	gcc -c projectRSA_client.c
	gcc -o projectRSA_client projectRSA_client.o
	./projectRSA_client 127.0.0.1 8080

projectRSA_serv:
	gcc -c projectRSA_serv.c
	gcc -o projectRSA_serv projectRSA_serv.o
	./projectRSA_serv