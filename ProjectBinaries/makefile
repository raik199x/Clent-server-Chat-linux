all:
	gcc ../server/server.c \
	../server/functions.c \
	../server/RegisterLogic/RegisterRequest.c \
	../server/RecoveryLogic/RecoveryRequest.c \
	../server/ValidateData/ValidateData.c \
	../server/Slots.c \
	-o server -pthread
	gcc ../MakeTestRequest/TestRequest.c -o MakeRequest
	g++ ../client/client.cpp -o tempclient
debug:
	gcc ../server/server.c \
	../server/functions.c \
	../server/RegisterLogic/RegisterRequest.c \
	../server/RecoveryLogic/RecoveryRequest.c \
	../server/ValidateData/ValidateData.c \
	../server/Slots.c \
	-o server -pthread -g
	gcc ../MakeTestRequest/TestRequest.c -o MakeRequest -g
	g++ ../client/client.cpp -o tempclient -g
clear:
	rm -rf server MakeRequest tempclient