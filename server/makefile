all:
	gcc server.c functions.c RegisterLogic/RegisterRequest.c RecoveryLogic/RecoveryRequest.c -o server -pthread
debug:
	gcc server.c functions.c RegisterLogic/RegisterRequest.c RecoveryLogic/RecoveryRequest.c -o server -pthread -g
clear:
	rm -rf server