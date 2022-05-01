all:
	gcc ../server/server.c ../server/functions.c ../server/RegisterLogic/RegisterRequest.c ../server/RecoveryLogic/RecoveryRequest.c -o server -pthread
	gcc ../MakeTestRequest/TestRequest.c -o MakeRequest
	g++ ../client/client.cpp -o tempclient
debug:
	gcc ../server/server.c ../server/functions.c ../server/RegisterLogic/RegisterRequest.c ../server/RecoveryLogic/RecoveryRequest.c -o server -pthread -g
server:
	gcc ../server/server.c ../server/functions.c ../server/RegisterLogic/RegisterRequest.c ../server/RecoveryLogic/RecoveryRequest.c -o server -pthread
testrequest:
	gcc ../MakeTestRequest/TestRequest.c -o MakeRequest
tempclient:
	g++ ../client/client.cpp -o tempclient
clear:
	rm -rf server MakeRequest tempclient