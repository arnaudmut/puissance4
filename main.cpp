#include <iostream>
//#include "puissance.hpp" // for eclipse
#include "Puissance4.h"
//#include <libltdl/lt_system.h>


#ifdef __unix__
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>  //getpeername,inet_ntop functions
#include "TCPStream.h"
#include "TCPAcceptor.h"

using namespace std;
ssize_t buffer_len = 128;

struct Joueur {
    string nom;
    char pion;
} joueur[2];

bool player_join_net(TCPStream *client_sd, char pion){
    if (client_sd != NULL) {
        char message_client[buffer_len];
        ssize_t status;
        while ((buffer_len = client_sd->receive(message_client, sizeof(buffer_len))) > 0) {
            message_client[buffer_len] = 0;
            printf("received - %s\n", message_client);
            joueur->nom = message_client;
            joueur->pion = pion;
            status = client_sd->send(&pion, buffer_len);
        }
        delete client_sd;
        return status != -1;
    }
    else exit(1);
}
bool player_join(int &tcp_client_sock, char pion) {
    vector<char> client_msg_buffer(buffer_len);
    vector<char> server_msg_buffer(buffer_len);
    int i = 0;
    // vider le buffer de msg clients
    //memset(&client_msg_buffer,0,client_msg_buffer.size());
    ssize_t status = 0;
    string nom;
    do {
        status = recv(tcp_client_sock, client_msg_buffer.data(),
                      client_msg_buffer.size(), 0);
        // checking for errors
        if (status == -1) {
            perror("erreur recv : ");
            return false;
        }
        else if (status == 0) {
            cout << "status 0" << endl;
        }
        else {
            nom.append(client_msg_buffer.begin(), client_msg_buffer.end());
        }
        /* enlever les bytes non necessaire au string recu
        * param[in] string str : message client a "nettoyer"
        * return string s : cleaned msg
        */

    } while (status == client_msg_buffer.size());
    string s;
    for (auto car : nom) {
        if (isprint(car)) {
            s += car;
        }
    }
    cout << "s : " << s << endl;

    // nom et affectation pion joueur
    //memcpy(&joueur[i].nom,&client_msg_buffer,buffer_len);
    joueur[i].pion = pion;
    joueur[i].nom = nom;
    cout << "joueur no " << i + 1 << joueur[i].nom << endl;
    cout << "pion :" << pion << endl;
    i++;
    cout << "nom size : " << nom.size() << endl;

    server_msg_buffer.clear();
    server_msg_buffer.push_back(pion);
    status = send(tcp_client_sock, &pion, server_msg_buffer.size(), 0);
    //checking for errors
    if (status == -1) {
        perror("erreur send : ");
        exit(1);
    }
    else {
        cout << server_msg_buffer.data() << endl;
        return true;
    }
}

int main() {
    //game vars
    Puissance4 jeu;
    srand((unsigned int)(time(0)));
    vector<vector<char> > grille = jeu.get_grille();
    int xPos;
    jeu.afficher_grille();
    srand((unsigned int)(time(0)));
    cout << grille.size()<<endl;
    cout<<grille[0].size()<<endl;
    cout<< jeu.get_grille_size()<<endl;


    //sock vars
    sockaddr_in tcp_server_addr;
    sockaddr_in tcp_client_addr;
    socklen_t tcp_server_addr_len = sizeof(tcp_server_addr);
    socklen_t tcp_client_addr_len = sizeof(tcp_client_addr);
    int tcp_server_sock, status;
    char server_ip[INET_ADDRSTRLEN];
    //creation socket
    tcp_server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_server_sock == -1) {
        perror("erreur creation socket : ");
        exit(1);
    }
        // initialisaton sock addr
        memset(&tcp_server_addr, 0, tcp_server_addr_len);
        tcp_server_addr.sin_family = AF_INET;
        tcp_server_addr.sin_port = htons(35000); // ask the OS to assign the port
        tcp_server_addr.sin_addr.s_addr = INADDR_ANY;

        int optVal = 1;
        setsockopt(tcp_server_sock, SOL_SOCKET, SO_REUSEADDR, &optVal,
                   sizeof(int));
        //binding
        status = bind(tcp_server_sock, (sockaddr *) &tcp_server_addr,
                      tcp_server_addr_len);
        if (status == -1) {
            perror("erreur bind :");
            exit(1);
        }
        // listening les clients qui se connectent
        listen(tcp_server_sock, 1);
        // info server sock cree
        inet_ntop(AF_INET, &tcp_server_addr.sin_addr, server_ip, sizeof(server_ip));
        if (server_ip == NULL) {
            perror("info sock non recu :");
            exit(1);
        }
        else {
            cout << "adresse : " << server_ip;
            cout << " port :" << ntohs(tcp_server_addr.sin_port) << endl;
        }

        int tcp_client_sock[2];
        tcp_client_sock[0] = -1;
        tcp_client_sock[1] = -1;
        TCPStream *client_sd = NULL;
        TCPAcceptor *sock_acceptant = NULL;
        sock_acceptant = new TCPAcceptor();
        if (sock_acceptant->start()== 0){
        auto i = 1;
            while (i < 2 ){

            client_sd= sock_acceptant->accept();
                auto  status = player_join_net(client_sd,jeu.get_pion(i));
            i++;
                cout << "player join status : " + status<<endl;
            }
        }

        //accepter les deux joueurs
        for (int i = 0; i < 2; i++) {
            while (tcp_client_sock[i] == -1) {
                    //if accept fails
                    if (tcp_client_sock[i] == -1) {
                        cout << "joueur " << i + 1 << "non accepte. ";
                        perror("erreur : ");

                    }
                    else if (!player_join(tcp_client_sock[i], jeu.get_pion(i))) {
                        tcp_client_sock[i] = -1;
                        cout << "message recu incorrect ! " << endl;
                        exit(1);
                    }
                }
            }
            // got two players
            //game handleling sous progr
            if (close(tcp_server_sock) == -1) {
                perror("erreur fermeture server socket : ");
                exit(1);
            }

            for (int i = 0; i < 2; i++) {
                cout << "nom du joueur no " << i + 1 << " : " << endl;
                getline(cin, joueur[i].nom);
                joueur[i].pion = jeu.get_pion(i);
            }
            for (int i = 0; i < 2; i++) {
                cout << joueur[i].nom << " : " << joueur[i].pion << endl;
            }
            int k = 0;
            int j = rand() % 2;
            // first to play
            cout << joueur[j].nom << " commence le jeu " << endl;
            do {
                cout << "mettre pion :" << endl;
                cin >> xPos;

                while (!jeu.placer_pion(xPos, joueur[j].pion)) {
                    cout << "colonn pleine ou < 0 ou >6 : ";
                    cin >> xPos;
                }
                cout << "winner : " << jeu.winner(xPos) << endl;
                jeu.afficher_grille();
                k++;
                //gestion tour
                j == 0 ? j++ : j--;
            } while (k < 40);// while no winner

            return 0;
        }

#elif defined(_WIN32_WINNT) || defined(__WINDOWS__)

#include <WS2tcpip.h> //inet_ntop,INET_ADDRSTRLEN functions

using namespace std;
const int buffer_len = 16;

struct Joueur {
    string nom;
    char pion;
} joueur[2];

bool player_join(SOCKET &tcp_client_sock, char pion) {
    vector<char> client_msg_buffer(buffer_len);
    vector<char> server_msg_buffer(buffer_len);
    int i = 0;
    // vider le buffer de msg clients
    //memset(&client_msg_buffer,0,client_msg_buffer.size());
    int status = 0;
    string nom;
        status = recv( tcp_client_sock, client_msg_buffer.data(),
                client_msg_buffer.size(), 0);
        // checking for errors
        if (status == -1) {
            perror("erreur recv : ");
            return false;
        }
        else if (status == 0) {
            cout << "status 0" << endl;
        }
        else {
            nom.append(client_msg_buffer.begin(), client_msg_buffer.end());
        }
        /* enlever les bytes non necessaire au string recu
        * param[in] string str : message client a "nettoyer"
        * return string s : cleaned msg
        */

    string s;
    for (auto i : nom) {
        if (isalnum(i)) {
            s += i;
        }
    }
    cout << "s : " << s << endl;

    // nom et affectation pion joueur
    //memcpy(&joueur[i].nom,&client_msg_buffer,buffer_len);
    joueur[i].pion = pion;
    joueur[i].nom = nom;
    cout << "joueur no " << i + 1 << joueur[i].nom << endl;
    cout << "pion :" << pion << endl;
    i++;
    cout << "nom size : " << nom.size() << endl;

    server_msg_buffer.clear();
    server_msg_buffer.push_back(pion);
    status = send(tcp_client_sock, &pion, server_msg_buffer.size(), 0);
    //checking for errors
    if (status == -1) {
        perror("erreur send : ");
        exit(1);
    }
    else {
        cout << server_msg_buffer.data() << endl;
        return true;
    }
}

int main() {
    //game vars
    Puissance4 jeux;
    jeux.init_jeux();
    srand(int(time(0)));
    vector<vector<char> > grille = jeux.GetPlateau();
    int xPos;
    jeux.afficher_plateau();
    srand(int(time(0)));

    //sock vars
    WSADATA WSAData;
    SOCKET tcp_server_sock;
    SOCKADDR_IN tcp_server_addr;
    SOCKADDR_IN tcp_client_addr;
    WSAStartup(MAKEWORD(2, 0), &WSAData);
    int tcp_server_addr_len = sizeof(tcp_server_addr);
    int tcp_client_addr_len = sizeof(tcp_client_addr);
    int status;
    //creation socket
    tcp_server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_server_sock == SOCKET_ERROR) {
        perror("erreur creation socket : ");
        exit(1);
    }
    // initialisaton sock addr
    memset(&tcp_server_addr, 0, tcp_server_addr_len);
    tcp_server_addr.sin_family = AF_INET;
    tcp_server_addr.sin_port = htons(35000);
    tcp_server_addr.sin_addr.s_addr = INADDR_ANY;
    //Allows other sockets to bind() to this port, unless there is an active listening socket bound to the port already.
    //This enables you to get around those "Address already in use" error messages when you try to restart your server after a crash.
    int optVal = 1;
    setsockopt(tcp_server_sock, SOL_SOCKET, SO_REUSEADDR, (char *) &optVal,sizeof(int));
    //binding
    status = bind(tcp_server_sock, (sockaddr *) &tcp_server_addr,
            tcp_server_addr_len);
    if (status == -1) {
        perror("erreur bind :");
        exit(1);
    }
    // listening les clients qui se connectent
    listen(tcp_server_sock, 1);
    // info server sock cree
    if (getsockname(tcp_server_sock, (sockaddr*)&tcp_server_addr, &tcp_server_addr_len)) {
        perror("info sock non recu :");
        exit(1);
    }
    else {

        cout << "adresse : " << inet_ntoa(tcp_server_addr.sin_addr);
        cout << " port :" << ntohs(tcp_server_addr.sin_port) << endl;

    }

    int tcp_client_sock[2];
    tcp_client_sock[0] = -1;
    tcp_client_sock[1] = -1;
    //accepter les deux joueurs
    for (int i = 0; i < 2; i++) {
        while (tcp_client_sock[i] == -1) {
            tcp_client_sock[i] = accept(tcp_server_sock,
                    (sockaddr *) &tcp_client_addr, &tcp_client_addr_len);

            //if accept fails
            if (tcp_client_sock[i] == -1) {
                cout << "joueur " << i + 1 << "non accepte. ";
                perror("erreur : ");

            }
            else if (!player_join(tcp_client_sock[i], jeux.getPion(i))) {
                tcp_client_sock[i] = -1;
                cout << "message recu incorrect ! " << endl;
                exit(1);
            }
        }
    }
    // got two players
    //game handleling sous progr
    if (closesocket(tcp_server_sock) == -1) {
        perror("erreur fermeture server socket : ");
        exit(1);
    }

    for (int i = 0; i < 2; i++) {
        cout << "nom du joueur no " << i + 1 << " : " << endl;
        getline(cin, joueur[i].nom);
        joueur[i].pion = jeux.get_pion(i);
    }
    for (int i = 0; i < 2; i++) {
        cout << joueur[i].nom << " : " << joueur[i].pion << endl;
    }
    int k = 0;
    int j = rand() % 2;
    // first to play
    cout << joueur[j].nom << " commence le jeu " << endl;
    do {
        cout << "mettre pion :" << endl;
        cin >> xPos;

        while (!jeux.placer_pion(xPos, joueur[j].pion)) {
            cout << "colonn pleine ou < 0 ou >6 : ";
            cin >> xPos;
        }
        cout << "winner : " << jeux.winner(xPos) << endl;
        jeux.afficher_grille();
        k++;
        //gestion tour
        j == 0 ? j++ : j--;
    } while (k < 40); // while no winner
    return 0;
}
#endif

int main(int argc, char **argv) {
            TCPStream *stream = NULL;
            TCPAcceptor *acceptor = NULL;
            acceptor = new TCPAcceptor();

            if (acceptor->start() == 0) {
                while (1) {
                    stream = acceptor->accept();
                    if (stream != NULL) {
                        ssize_t len;
                        char line[256];
                        while ((len = stream->receive(line, sizeof(line))) > 0) {
                            line[len] = 0;
                            printf("received - %s\n", line);
                            stream->send(line, len);
                        }
                        stream->send(line, len);
                        delete stream;
                    }
                }
            }
            exit(0);
        }