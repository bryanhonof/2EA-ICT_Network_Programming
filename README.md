2EA-ICT_Network_Programming:
----------------------------
This is the top level of the 2EA-ICT_Network_Programming source directory.

The goal for this project was to learn about networkprogramming or socket programming with the standard
Berkeley or UNIX sockets.

The tasks were:
* Setup a Raspberry Pi as a server with a UNIX/BSD OS that has SSH capabilities
* Make a program that acts like a Mail Box (flags up for mail)
* The program has to make use of the standard Berkley sockets and has to listern on a TCP port to 
  recieve messages
* When the server recieves a messages it has to write it to a log file
* The log file can be JSON or XML ecnoded
* Time synchronization with NTP client
* FTP to remove the log file or edit it
* Lighttpd server to display the log file via the web
* Recieve multiple messages
* Server can handle more than 1 client at the same time
* LED has to turn on when a message has been recieved and off when the button is pressed

Requirements:
-------------
| Component                   | Amount            |
| --------------------------- |:-----------------:|
| Raspberry Pi 3 or variant   | 1                 |
| LED                         | 1                 |
| Button                      | 1                 |
| randomly selected resistor  | 1                 |
| Jumper Wire                 | as much as needed |


Source Roadmap:
---------------
```
GPIO/           Code for the GPIO (LED & button).

server-client/  Code for the server & client.

ledStat         File that holds either a 1 or a 0. Depending on the state of
                this file the LED will be on or off.
```
