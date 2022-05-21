# Client-server-Chat-linux
Course project for [bsuir 4 semester](https://github.com/raik199x/BSUIR-labs)

Simple chat made on sockets (not QTcpSocket) that works on client->server methodology.
Server written on bare C and client-side written on Qt + c\c++

It works only on localhost and uses 3002 port for connections, but client side contains all needs for transfer to static ips.

[paper work](https://mega.nz/folder/VfxllTwA#GR8gfJiDL-XTsHNyAjKoig)

---

Installation:

in folder Installation you'll find binary for server, is doesn't need to be installed, just run it.

File ".run" should be runned as executable file, the program will exctract files for clien app, you'll find "*.sh" file that will run program.

---

Server has 3 levels of logging:

    LOG - simple message that something happened on server

    Warning - something suspicious or not standard happened on server

    Critical - something really bad happened on server and you need to decided what to do


Server works in multithread mode, main thread listening for simple requests such as registration, recovery and login but if client
logs successfully server makes new thread for that client so he can chat with everybody without interrupting work of the server.

Server doesn't have any logs (#NoLogPolicy) except of login credentials and doesn't have an ui. Also there is no encryption implemented, so use it only in
 education propose.

---

Client is a simple ui for chatting and performing requests. There is no cool-looking animations and others but still, this is an ui that can be used =).

---

Program support only english language, the reason is Qt doesn't support cyrillic and i didn't fix this issue,
but still, code contains all needs for translation to other languages

---

Features:

    * You can chat (:D)
    * No limit for active connections
    * Register nickname + Recover if needed

How can be improved?

    * File transfer
    * Multiple languages
    * Encryption
    * transfer from localhost
    * adding database instead of files
    * ui upgrade

---

Preview:

Chat by itself
![Screenshot_20220513_191318](https://user-images.githubusercontent.com/70070040/168325400-3ba0b088-90c9-43b6-ae41-eb01a1a6e61c.png)

Tested on very old laptop
![image](https://user-images.githubusercontent.com/70070040/168326984-e8646410-1aba-43cb-99f2-319457f1518f.png)

server

![Screenshot_20220513_192929](https://user-images.githubusercontent.com/70070040/168327272-47e91b80-6a2c-4839-94fa-d32b74ddf66a.png)


---

Chat is a huge theme where you always find place to work, that was really interesting work and i hope you also like it (or even improve).

Contacts:

telegram: @raik199x

mail: raik199x@mail.ru
