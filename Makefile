projectRSA:
	gcc -c src/projectRSA_client.c -o build/projectRSA_client.o
	gcc -c src/projectRSA_serv.c -o build/projectRSA_serv.o
	gcc build/projectRSA_client.o -o build/projectRSA_client
	gcc build/projectRSA_serv.o -o build/projectRSA_serv

projectRSA_client:
	gcc -c src/projectRSA_client.c -o build/projectRSA_client.o
	gcc build/projectRSA_client.o -o build/projectRSA_client
	./build/projectRSA_client 127.0.0.1 8080

projectRSA_serv:
	gcc -c src/projectRSA_serv.c -o build/projectRSA_serv.o
	gcc build/projectRSA_serv.o -o build/projectRSA_serv
	./build/projectRSA_serv 127.0.0.1 8080

clean: 
	rm build/*