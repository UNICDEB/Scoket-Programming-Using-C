# Scoket-Programming-Using-C
Socket Programming

In this socket programming we can connect maximum 5 clients and minimum 2 clients, and they transfer message from each other.

At first compile the server program and then run the server program.
   when, write  "./server 2" then two(2) clients are connected with the server and message transfer between each other, as well as message transfer from client
(client1,client2) to server is also done.

     when, write  "./server"(Because it is the default server, so we can write only "./server") then three(3) clients are connected with the server 
and message transfer between each other, as well as message transfer from client (client1,client2,client3) to server is also done.

      when, write  "./server 4" then four(4) clients are connected with the server 
and message transfer between each other, as well as message transfer from client (client1,client2,client3,client4) to server is also done.

        when, write  "./server 5" then five(5) clients are connected with the server 
and message transfer between each other, as well as message transfer from client (client1,client2,client3,client4,client5) to server is also done.

     Then , compile the client program first and then run clients program.
         list command :-   syntex :  "list" Listing the clients name.
         
         message send :-  systex: " put "message" destination_clients_name " then hit enter button.
                                   " put "message" server"  then hit the enter button.
         message received :-  syntex :  " get "message" from sender_client_name "(when sender client send the message then receiver client automatically 
                                                                                   receive the message from sender end) then hit enter button.
         Exit command :-  syntex : " :exit" exit the connection(this code is written in all clients end).
                                     

 AVAILABLE FOLDER AND FILE DETAILS :- 

       DEBABRATA DOLOI.pdf file :- Documentation .
       SCREENSHOT folder :- All screenshots are available(server-2(with 2 clients), default server(with 3 client) , server-4(with 4 clients), 
                            server-5(with 5 clients) .
       SOURCE CODE folder :- Hare server.c and client.c raw files are available.
