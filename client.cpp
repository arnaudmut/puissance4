////#include <libltdl/lt_system.h>
//
//#ifdef __unix__
//
//using namespace std;
//const int buffer_len = 16;
//
//int main() {
//    //sock vars
//    char client_msg_buffer[buffer_len];
//    sockaddr_in tcp_client_addr;
//    socklen_t tcp_client_addr_len = sizeof(tcp_client_addr);
//    int tcp_client_sock, status;
//    char client_ip[INET_ADDRSTRLEN];
//
//
//    //game vars
//    string nom;
//
//
//    //creation socket
//    tcp_client_sock = socket(AF_INET, SOCK_STREAM, 0);
//    if (tcp_client_sock == -1) {
//        perror("erreur creation socket : ");
//        exit(1);
//    }
//
//    // initialisaton sock addr
//    memset(&tcp_client_addr, 0, tcp_client_addr_len);
//    tcp_client_addr.sin_family = AF_INET;
//    tcp_client_addr.sin_port = htons(35000); // ask the OS to assign the port
//    tcp_client_addr.sin_addr.s_addr = INADDR_ANY;
//
//
//    int yes = 1;
//    status = setsockopt(tcp_client_sock, SOL_SOCKET, SO_REUSEADDR, &yes,
//                        sizeof(int));
//    //connecting to server
//    status = connect(tcp_client_sock, (sockaddr * ) & tcp_client_addr, tcp_client_addr_len);
//    if (status == -1) {
//        perror("erreur connect : ");
//        exit(1);
//    }
//    cout << "saisir nom : ";//cin>>nom;
//    nom = "eric:lfldsmjfkdjfkslmkfjlsjflsfjlk";
//    status = send(tcp_client_sock, &nom, nom.size(), 0);
//    if (status == -1) {
//        perror("erreur send :");
//    }
//    else {
//        cout << "send ok" << endl;
//    }
//
//    status = recv(tcp_client_sock, client_msg_buffer, buffer_len, 0);
//    if (status == -1) {
//        perror("erreur recv :");
//        exit(1);
//    }
//    cout << "buffer size :" << sizeof(client_msg_buffer) << endl;
//    nom.clear();
//    for (char i : client_msg_buffer) {
//        nom = +i;
//    }
//    cout << nom << "nom size : " << sizeof(nom) << endl;
//}
//
//#elif __WINDOWS__
//
//#include <WS2tcpip.h> //inet_ntop,INET_ADDRSTRLEN functions
//
//using namespace std;
//const int buffer_len = 16;
//
//int main(){
//    //sock vars
//    char client_msg_buffer[buffer_len];
//    sockaddr_in tcp_client_addr;
//    socklen_t tcp_client_addr_len = sizeof(tcp_client_addr);
//    int tcp_client_sock, status;
//    char client_ip[INET_ADDRSTRLEN];
//
//
//    //game vars
//    string nom;
//
//
//    //creation socket
//    tcp_client_sock = socket(AF_INET, SOCK_STREAM, 0);
//    if (tcp_client_sock == -1) {
//        perror("erreur creation socket : ");
//        exit(1);
//    }
//
//    // initialisaton sock addr
//    memset(&tcp_client_addr, 0, tcp_client_addr_len);
//    tcp_client_addr.sin_family = AF_INET;
//    tcp_client_addr.sin_port = htons(35000); // ask the OS to assign the port
//    tcp_client_addr.sin_addr.s_addr = INADDR_ANY;
//
//
//    int yes = 1;
//    status = setsockopt(tcp_client_sock, SOL_SOCKET, SO_REUSEADDR, &yes,
//            sizeof(int));
//    //connecting to server
//    status = connect(tcp_client_sock,(sockaddr*)&tcp_client_addr,tcp_client_addr_len);
//    if(status == -1 ){
//        perror("erreur connect : ");
//        exit(1);
//    }
//    cout << "saisir nom : ";//cin>>nom;
//    nom = "eric:lfldsmjfkdjfkslmkfjlsjflsfjlk";
//    status = send(tcp_client_sock,&nom,nom.size(),0);
//    if(status == -1){
//        perror("erreur send :");
//    }
//    else{
//        cout << "send ok"<<endl;
//    }
//
//    status = recv(tcp_client_sock,client_msg_buffer,buffer_len,0);
//    if (status == -1){
//        perror("erreur recv :");
//        exit(1);
//    }
//    cout << "buffer size :"<<sizeof(client_msg_buffer)<<endl;
//    nom.clear();
//    for(char i : client_msg_buffer){
//        nom =+ i ;
//    }
//    cout << nom << "nom size : "<< sizeof (nom)<<endl;
//}
//
//#endif

/*
   client.cpp

   Test client for the tcpsockets classes.

   ------------------------------------------

   Copyright � 2013 [Vic Hargrave - http://vichargrave.com]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

using namespace std;

int main(int argc, char** argv)
{
//    if (argc != 3) {
//        printf("usage: %s <port> <ip>\n", argv[0]);
//        exit(1);
//    }

    int len;
    string message;
    char line[256];
    TCPConnector* connector = new TCPConnector();
    TCPStream* stream = connector->connect();
    if (stream) {
        message = "Is there life on Mars?";
        stream->send(message.c_str(), message.size());
        printf("sent - %s\n", message.c_str());
        len = stream->receive(line, sizeof(line));
        line[len] = 0;
        printf("received - %s\n", line);
        delete stream;
    }

    stream = connector->connect();
    if (stream) {
        message = "Why is there air?";
        stream->send(message.c_str(), message.size());
        printf("sent - %s\n", message.c_str());
        len = stream->receive(line, sizeof(line));
        line[len] = 0;
        printf("received - %s\n", line);
        delete stream;
    }
    exit(0);
}