//#include <libltdl/lt_system.h>

#ifdef __unix__

using namespace std;
const int buffer_len = 16;

int main() {
    //sock vars
    char client_msg_buffer[buffer_len];
    sockaddr_in tcp_client_addr;
    socklen_t tcp_client_addr_len = sizeof(tcp_client_addr);
    int tcp_client_sock, status;
    char client_ip[INET_ADDRSTRLEN];


    //game vars
    string nom;


    //creation socket
    tcp_client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_client_sock == -1) {
        perror("erreur creation socket : ");
        exit(1);
    }

    // initialisaton sock addr
    memset(&tcp_client_addr, 0, tcp_client_addr_len);
    tcp_client_addr.sin_family = AF_INET;
    tcp_client_addr.sin_port = htons(35000); // ask the OS to assign the port
    tcp_client_addr.sin_addr.s_addr = INADDR_ANY;


    int yes = 1;
    status = setsockopt(tcp_client_sock, SOL_SOCKET, SO_REUSEADDR, &yes,
                        sizeof(int));
    //connecting to server
    status = connect(tcp_client_sock, (sockaddr * ) & tcp_client_addr, tcp_client_addr_len);
    if (status == -1) {
        perror("erreur connect : ");
        exit(1);
    }
    cout << "saisir nom : ";//cin>>nom;
    nom = "eric:lfldsmjfkdjfkslmkfjlsjflsfjlk";
    status = send(tcp_client_sock, &nom, nom.size(), 0);
    if (status == -1) {
        perror("erreur send :");
    }
    else {
        cout << "send ok" << endl;
    }

    status = recv(tcp_client_sock, client_msg_buffer, buffer_len, 0);
    if (status == -1) {
        perror("erreur recv :");
        exit(1);
    }
    cout << "buffer size :" << sizeof(client_msg_buffer) << endl;
    nom.clear();
    for (char i : client_msg_buffer) {
        nom = +i;
    }
    cout << nom << "nom size : " << sizeof(nom) << endl;
}

#elif __WINDOWS__

#include <WS2tcpip.h> //inet_ntop,INET_ADDRSTRLEN functions

using namespace std;
const int buffer_len = 16;

int main(){
    //sock vars
    char client_msg_buffer[buffer_len];
    sockaddr_in tcp_client_addr;
    socklen_t tcp_client_addr_len = sizeof(tcp_client_addr);
    int tcp_client_sock, status;
    char client_ip[INET_ADDRSTRLEN];


    //game vars
    string nom;


    //creation socket
    tcp_client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_client_sock == -1) {
        perror("erreur creation socket : ");
        exit(1);
    }

    // initialisaton sock addr
    memset(&tcp_client_addr, 0, tcp_client_addr_len);
    tcp_client_addr.sin_family = AF_INET;
    tcp_client_addr.sin_port = htons(35000); // ask the OS to assign the port
    tcp_client_addr.sin_addr.s_addr = INADDR_ANY;


    int yes = 1;
    status = setsockopt(tcp_client_sock, SOL_SOCKET, SO_REUSEADDR, &yes,
            sizeof(int));
    //connecting to server
    status = connect(tcp_client_sock,(sockaddr*)&tcp_client_addr,tcp_client_addr_len);
    if(status == -1 ){
        perror("erreur connect : ");
        exit(1);
    }
    cout << "saisir nom : ";//cin>>nom;
    nom = "eric:lfldsmjfkdjfkslmkfjlsjflsfjlk";
    status = send(tcp_client_sock,&nom,nom.size(),0);
    if(status == -1){
        perror("erreur send :");
    }
    else{
        cout << "send ok"<<endl;
    }

    status = recv(tcp_client_sock,client_msg_buffer,buffer_len,0);
    if (status == -1){
        perror("erreur recv :");
        exit(1);
    }
    cout << "buffer size :"<<sizeof(client_msg_buffer)<<endl;
    nom.clear();
    for(char i : client_msg_buffer){
        nom =+ i ;
    }
    cout << nom << "nom size : "<< sizeof (nom)<<endl;
}

#endif