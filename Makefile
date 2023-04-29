projectrsa:
	rm build/*
	gcc -c src/robots.c -o build/robots.o

	gcc -c src/technician.c -o build/technician.o

	gcc -c src/expert.c -o build/expert.o

	gcc -c src/client_rsa.c -o build/client_rsa.o
	gcc -c src/server_rsa.c -o build/server_rsa.o

	gcc build/client_rsa.o -o build/client_rsa
	gcc build/server_rsa.o -o build/server_rsa

projectrsa_client:
	gcc -c src/client_rsa.c -o build/client_rsa.o
	gcc build/client_rsa.o -o build/client_rsa
	./build/client_rsa

projectrsa_serv:
	gcc -c src/server_rsa.c -o build/server_rsa.o
	gcc build/server_rsa.o -o build/server_rsa
	./build/server_rsa
	
clean: 
	rm build/*