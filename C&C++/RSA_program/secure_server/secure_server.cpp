//////////////////////////////////////////////////////////////
// TCP SECURE SERVER GCC (IPV6 ready)
//
//
// References:
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms738520(v=vs.85).aspx
//             http://long.ccaba.upc.edu/long/045Guidelines/eva/ipv6.html#daytimeServer6
//
//////////////////////////////////////////////////////////////

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-extra-args"
#define USE_IPV6                                                               \
  false // if set to false, IPv4 addressing scheme will be used; you need to set
        // this to true to
// enable IPv6 later on.  The assignment will be marked using IPv6!

#if defined __unix__ || defined __APPLE__
#include <arpa/inet.h>
#include <cmath>
#include <errno.h>
#include <iostream>
#include <netdb.h> //used by getnameinfo()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#elif defined __WIN32__
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h> //required by getaddrinfo() and special constants
#define WSVERS                                                                 \
  MAKEWORD(                                                                    \
      2,                                                                       \
      2) /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
// The high-order byte specifies the minor version number;
// the low-order byte specifies the major version number.
WSADATA wsadata; // Create a WSADATA object called wsadata.
#endif

#define DEFAULT_PORT "1234"

#define BUFFER_SIZE 500
#define RBUFFER_SIZE 256

using namespace std;
/////////////////////////////////////////////////////////////////////

void printBuffer(const char *header, char *buffer) {
  cout << "------" << header << "------" << endl;
  for (unsigned int i = 0; i < strlen(buffer); i++) {
    if (buffer[i] == '\r') {
      cout << "buffer[" << i << "]=\\r" << endl;
    } else if (buffer[i] == '\n') {
      cout << "buffer[" << i << "]=\\n" << endl;
    } else {
      cout << "buffer[" << i << "]=" << buffer[i] << endl;
    }
  }
  cout << "---" << endl;
}
#include <boost/multiprecision/cpp_int.hpp>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace boost::multiprecision;
cpp_int mod_exp(cpp_int base, cpp_int exp, cpp_int modulus) {
  cpp_int result = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * base) % modulus;
    }
    base = (base * base) % modulus;
    exp /= 2;
  }
  return result;
}

cpp_int multiMod(cpp_int m, cpp_int e, cpp_int n) { return mod_exp(m, e, n); }
void extended_gcd(cpp_int a, cpp_int b, cpp_int *gcd, cpp_int *x, cpp_int *y) {
  if (b == 0) {
    *gcd = a;
    *x = 1;
    *y = 0;
  } else {
    extended_gcd(b, a % b, gcd, y, x);
    *y -= (a / b) * (*x);
  }
}

cpp_int get_d(cpp_int p, cpp_int q, cpp_int e) {
  cpp_int l = (p - 1) * (q - 1);
  cpp_int x = 1;
  while ((x * l + 1) % e) {
    x++;
  }
  return (x * l + 1) / e;
}

cpp_int encrypt(cpp_int plaintext, cpp_int e, cpp_int n) {
  return multiMod(plaintext, e, n);
}
cpp_int decrypt(cpp_int ciphertext, cpp_int d, cpp_int n) {
  return multiMod(ciphertext, d, n);
}
/////////////////////////////////////////////////////////////////////

//*******************************************************************
// MAIN
//*******************************************************************
int main(int argc, char *argv[]) {
  cpp_int p = 2381;
  cpp_int q = 2843;
  cpp_int e_ca = 1046527;

  cpp_int n_ca = p * q;
  cpp_int d_ca = get_d(p, q, e_ca);

  std::cout << "Public key (e,n): (" << e_ca << ", " << n_ca << ")\n";
  std::cout << "Private key (d,n): (" << d_ca << ", " << n_ca << ")\n";
  //********************************************************************
  // INITIALIZATION of the SOCKET library
  //********************************************************************

  struct sockaddr_storage clientAddress; // IPV6

  char clientHost[NI_MAXHOST];
  char clientService[NI_MAXSERV];

  char send_buffer[BUFFER_SIZE], receive_buffer[RBUFFER_SIZE];
  int n, bytes, addrlen;
  char portNum[NI_MAXSERV];
  // char username[80];
  // char passwd[80];

  // memset(&localaddr,0,sizeof(localaddr));

#if defined __unix__ || defined __APPLE__
  int s, ns;

#elif defined _WIN32

  SOCKET s, ns;

  //********************************************************************
  // WSSTARTUP
  /*	All processes (applications or DLLs) that call Winsock functions must
          initialize the use of the Windows Sockets DLL before making other
     Winsock functions calls. This also makes certain that Winsock is supported
     on the system.
  */
  //********************************************************************
  int err;

  err = WSAStartup(WSVERS, &wsadata);
  if (err != 0) {
    WSACleanup();
    /* Tell the user that we could not find a usable */
    /* Winsock DLL.                                  */
    printf("WSAStartup failed with error: %d\n", err);
    exit(1);
  }

  //********************************************************************
  /* Confirm that the WinSock DLL supports 2.2.        */
  /* Note that if the DLL supports versions greater    */
  /* than 2.2 in addition to 2.2, it will still return */
  /* 2.2 in wVersion since that is the version we      */
  /* requested.                                        */
  //********************************************************************

  if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 2) {
    /* Tell the user that we could not find a usable */
    /* WinSock DLL.                                  */
    printf("Could not find a usable version of Winsock.dll\n");
    WSACleanup();
    exit(1);
  } else {
    printf("\n\n<<<TCP SERVER>>>\n");
    printf("\nThe Winsock 2.2 dll was initialised.\n");
  }

#endif

  //********************************************************************
  // set the socket address structure.
  //
  //********************************************************************
  struct addrinfo *result = NULL;
  struct addrinfo hints;
  int iResult;

  //********************************************************************
  // STEP#0 - Specify server address information and socket properties
  //********************************************************************

  // ZeroMemory(&hints, sizeof (hints)); //alternatively, for Windows only
  memset(&hints, 0, sizeof(struct addrinfo));

  if (USE_IPV6) {
    hints.ai_family = AF_INET6;
  } else { // IPV4
    hints.ai_family = AF_INET;
  }

  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags =
      AI_PASSIVE; // For wildcard IP address
                  // setting the AI_PASSIVE flag indicates the caller intends to
                  // use the returned socket address structure in a call to the
                  // bind function.

  // Resolve the local address and port to be used by the server
  if (argc == 2) {
    iResult = getaddrinfo(
        NULL, argv[1], &hints,
        &result); // converts human-readable text strings representing hostnames
                  // or IP addresses into a dynamically allocated linked list of
                  // struct addrinfo structures IPV4 & IPV6-compliant
    sprintf(portNum, "%s", argv[1]);
    printf("\nargv[1] = %s\n", argv[1]);
  } else {
    iResult = getaddrinfo(
        NULL, DEFAULT_PORT, &hints,
        &result); // converts human-readable text strings representing hostnames
                  // or IP addresses into a dynamically allocated linked list of
                  // struct addrinfo structures IPV4 & IPV6-compliant
    sprintf(portNum, "%s", DEFAULT_PORT);
    printf("\nUsing DEFAULT_PORT = %s\n", portNum);
  }

#if defined __unix__ || defined __APPLE__

  if (iResult != 0) {
    printf("getaddrinfo failed: %d\n", iResult);

    return 1;
  }
#elif defined _WIN32

  if (iResult != 0) {
    printf("getaddrinfo failed: %d\n", iResult);

    WSACleanup();
    return 1;
  }
#endif

  //********************************************************************
  // STEP#1 - Create welcome SOCKET
  //********************************************************************

#if defined __unix__ || defined __APPLE__
  s = -1;
#elif defined _WIN32
  s = INVALID_SOCKET; // socket for listening
#endif
  // Create a SOCKET for the server to listen for client connections

  s = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

#if defined __unix__ || defined __APPLE__

  if (s < 0) {
    printf("Error at socket()");
    freeaddrinfo(result);
    exit(1); // return 1;
  }

#elif defined _WIN32

  // check for errors in socket allocation
  if (s == INVALID_SOCKET) {
    printf("Error at socket(): %d\n", WSAGetLastError());
    freeaddrinfo(result);
    WSACleanup();
    exit(1); // return 1;
  }
#endif
  //********************************************************************

  //********************************************************************
  // STEP#2 - BIND the welcome socket
  //********************************************************************

  // bind the TCP welcome socket to the local address of the machine and port
  // number
  iResult = bind(s, result->ai_addr, (int)result->ai_addrlen);

#if defined __unix__ || defined __APPLE__
  if (iResult != 0) {
    printf("bind failed with error");
    freeaddrinfo(result);

    close(s);

    return 1;
  }

#elif defined _WIN32

  if (iResult == SOCKET_ERROR) {
    printf("bind failed with error: %d\n", WSAGetLastError());
    freeaddrinfo(result);

    closesocket(s);
    WSACleanup();
    return 1;
  }
#endif

  freeaddrinfo(result); // free the memory allocated by the getaddrinfo
                        // function for the server's address, as it is
                        // no longer needed
//********************************************************************

/*
   if (bind(s,(struct sockaddr *)(&localaddr),sizeof(localaddr)) ==
   SOCKET_ERROR) { printf("Bind failed!\n");
   }
*/

//********************************************************************
// STEP#3 - LISTEN on welcome socket for any incoming connection
//********************************************************************
#if defined __unix__ || defined __APPLE__
  if (listen(s, SOMAXCONN) < 0) {
    printf("Listen failed with error\n");
    close(s);

    exit(1);
  }

#elif defined _WIN32
  if (listen(s, SOMAXCONN) == SOCKET_ERROR) {
    printf("Listen failed with error: %d\n", WSAGetLastError());
    closesocket(s);
    WSACleanup();
    exit(1);
  }
#endif

  //*******************************************************************
  // INFINITE LOOP
  //********************************************************************
  while (1) { // main loop
    printf("\n<<<SERVER>>> is listening at PORT: %s\n", portNum);
    addrlen = sizeof(clientAddress); // IPv4 & IPv6-compliant

//********************************************************************
// NEW SOCKET newsocket = accept
//********************************************************************
#if defined __unix__ || defined __APPLE__
    ns = -1;
#elif defined _WIN32
    ns = INVALID_SOCKET;
#endif

    // Accept a client socket
    // ns = accept(s, NULL, NULL);

    //********************************************************************
    // STEP#4 - Accept a client connection.
    //	accept() blocks the iteration, and causes the program to wait.
    //	Once an incoming client is detected, it returns a new socket ns
    // exclusively for the client.
    // It also extracts the client's IP address and Port number and stores
    // it in a structure.
    //********************************************************************

#if defined __unix__ || defined __APPLE__
    ns = accept(s, (struct sockaddr *)(&clientAddress),
                (socklen_t *)&addrlen); // IPV4 & IPV6-compliant

    if (ns < 0) {
      printf("accept failed\n");
      close(s);

      return 1;
    }
#elif defined _WIN32
    ns = accept(s, (struct sockaddr *)(&clientAddress),
                &addrlen); // IPV4 & IPV6-compliant
    if (ns == INVALID_SOCKET) {
      printf("accept failed: %d\n", WSAGetLastError());
      closesocket(s);
      WSACleanup();
      return 1;
    }
#endif
    printf("\nA <<<CLIENT>>> has been accepted.\n");

    memset(clientHost, 0, sizeof(clientHost));
    memset(clientService, 0, sizeof(clientService));
    getnameinfo((struct sockaddr *)&clientAddress, addrlen, clientHost,
                sizeof(clientHost), clientService, sizeof(clientService),
                NI_NUMERICHOST);

    printf("\nConnected to <<<Client>>> with IP address:%s, at Port:%s\n",
           clientHost, clientService);

    //********************************************************************
    // Communicate with the Client
    //********************************************************************
    printf("\n--------------------------------------------\n");
    printf("the <<<SERVER>>> is waiting to receive messages.\n");
    const int MAX_BUFFER_SIZE = 1024;
    char send_buffer[MAX_BUFFER_SIZE];
    cpp_int ciphertext_e = encrypt(e_ca, e_ca, n_ca);
    string t = ciphertext_e.str();
    memcpy(send_buffer, t.c_str(), MAX_BUFFER_SIZE - 1);
    send_buffer[MAX_BUFFER_SIZE - 1] = '\0'; // 确保发送的数据以 '\0' 结尾
    int bytes_sent = send(ns, send_buffer, MAX_BUFFER_SIZE - 1, 0);
    if (bytes_sent == -1) {
      cerr << "Error sending data: " << strerror(errno) << endl;
      return -1;
    }
    printf("MSG SENT -->: \"%s\"\n", send_buffer);

    while (1) {
      // 接收数据
      memset(receive_buffer, 0, sizeof(receive_buffer));
      n = 0;
      // TODO 接受数据
      recv(ns, receive_buffer, sizeof(receive_buffer), 0);
      string ciphertext_str = string(receive_buffer);
      istringstream iss(ciphertext_str);
      cpp_int set;
      if (!(iss >> set)) {
        continue;
      };

      cpp_int plaintext = decrypt(set, d_ca, n_ca);
      cout << "receive_buffer: " << receive_buffer << endl;
      cout << "Decrypted plaintext: " << plaintext << endl;
    }
  }
}
#pragma clang diagnostic pop