# Client-server-Chat-linux
Course project for bsuir 4 semester

Simple chat made on sockets (not QTcpSocket) that works on client->server methodology.
Server written on bare C and client-side written on Qt+c\c++

It works only on localhost and uses 3002 port for connections, but for client side contains all needs for transfer to static ips etc.

---

Installation:

in folder Installation you'll find binary for server, is doesn't need to be installed, just run it.

File ".run" should be runned as executable file, the program will exctract files for clien app, you'll find "*.sh" file that will run program

Also if you need you can check cheksum.

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

How can be improved?

    * File transfer
    * Multiple languages
    * Encryption
    * transfer from localhost
    * adding database instead of files
    * ui upgrade

---

Chat is a huge theme where you always find place to work, that was really interesting work and i hope you also like it (or even improve).

Contacts:

telegram: @raik199x

mail: raik199x@mail.ru
