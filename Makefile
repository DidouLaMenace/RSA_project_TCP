projectRSA:
	rm build/*
	gcc -c src/robots.c -o build/robots.o
	gcc -c src/technicians.c -o build/technicians.o
	gcc -c src/experts.c -o build/experts.o
	gcc -c src/projectRSA_tech.c -o build/projectRSA_tech.o
	gcc -c src/projectRSA_client.c -o build/projectRSA_client.o
	gcc -c src/projectRSA_serv.c -o build/projectRSA_serv.o
	gcc build/projectRSA_client.o -o build/projectRSA_client
	gcc build/projectRSA_serv.o -o build/projectRSA_serv
	gcc build/projectRSA_tech.o -o build/projectRSA_tech

projectRSA_client:
	gcc -c src/projectRSA_client.c -o build/projectRSA_client.o
	gcc build/projectRSA_client.o -o build/projectRSA_client
	./build/projectRSA_client

projectRSA_serv:
	gcc -c src/projectRSA_serv.c -o build/projectRSA_serv.o
	gcc build/projectRSA_serv.o -o build/projectRSA_serv
	./build/projectRSA_serv
	
clean: 
	rm build/*