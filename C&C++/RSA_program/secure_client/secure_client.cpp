//////////////////////////////////////////////////////////////////////////////////////////////
// TCP CrossPlatform CLIENT v.1.0 (towards IPV6 ready)
// compiles using GCC
//
//
// References:
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms738520(v=vs.85).aspx
//             http://long.ccaba.upc.edu/long/045Guidelines/eva/ipv6.html#daytimeServer6
//             Andre Barczak's tcp client codes
//
// Author: Napoleon Reyes, Ph.D.
//         Massey University, Albany
//
//////////////////////////////////////////////////////////////////////////////////////////////

#define USE_IPV6 false
#define DEFAULT_PORT "1234"

#if defined __unix__ || defined __APPLE__
#include <arpa/inet.h>
#include <cmath>
#include <cstdio>
#include <errno.h>
#include <iostream>
#include <netdb.h> //used by getnameinfo()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#elif defined _WIN32
#include <cstdio>
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

//////////////////////////////////////////////////////////////////////////////////////////////

enum CommandName { USER, PASS, SHUTDOWN };

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
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>
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
int main(int argc, char *argv[]) {

  cpp_int p = 2381;
  cpp_int q = 2843;
  cpp_int e_ca = 1046527;

  cpp_int n_ca = p * q;
  cpp_int d_ca = get_d(p, q, e_ca);
  //*******************************************************************
  // Initialization
  // What are the important data structures?
  //*******************************************************************

  char portNum[12];

#if defined __unix__ || defined __APPLE__
  int s;
#elif defined _WIN32
  SOCKET s;
#endif

#define BUFFER_SIZE 200

  char send_buffer[BUFFER_SIZE], receive_buffer[BUFFER_SIZE];
  int n, bytes;

  char serverHost[NI_MAXHOST];
  char serverService[NI_MAXSERV];

  // memset(&sin, 0, sizeof(sin));

#if defined __unix__ || defined __APPLE__
  // nothing to do here

#elif defined _WIN32
  //********************************************************************
  // WSSTARTUP
  //********************************************************************

  //********************************************************************
  // WSSTARTUP
  /*  All processes (applications or DLLs) that call Winsock functions must
    initialize the use of the Windows Sockets DLL before making other Winsock
    functions calls.
    This also makes certain that Winsock is supported on the system.
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

  if (USE_IPV6) {

    printf("\n=== IPv6 ===");
  } else { // IPV4

    printf("\n=== IPv4 ===");
  }

  //********************************************************************
  /* Confirm that the WinSock DLL supports 2.2.        */
  /* Note that if the DLL supports versions greater    */
  /* than 2.2 in addition to 2.2, it will still return */
  /* 2.2 in wVersion since that is the version we      */
  /* requested.                                        */
  //********************************************************************
  printf("\n\n<<<TCP (CROSS-PLATFORM, IPv6-ready) CLIENT, by nhreyes>>>\n");

  if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 2) {
    /* Tell the user that we could not find a usable */
    /* WinSock DLL.                                  */
    printf("Could not find a usable version of Winsock.dll\n");
    WSACleanup();
    exit(1);
  } else {

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

  // ZeroMemory(&hints, sizeof (hints)); //alternatively, for Windows only
  memset(&hints, 0, sizeof(struct addrinfo));

  if (USE_IPV6) {
  } else { // IPV4
    hints.ai_family = AF_INET;
    printf("\n=== IPv4 ===");
  }

  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  // if there are 3 parameters passed to the argv[] array.
  if (argc == 3) {
    // sin.sin_port = htons((u_short)atoi(argv[2])); //get Remote Port number
    sprintf(portNum, "%s", argv[2]);
    printf("\nUsing port: %s \n", portNum);
    iResult = getaddrinfo(argv[1], portNum, &hints, &result);
  } else {
    // sin.sin_port = htons(1234); //use default port number
    printf("USAGE: Client IP-address [port]\n"); // missing IP address
    sprintf(portNum, "%s", DEFAULT_PORT);
    printf("Default portNum = %s\n", portNum);
    printf("Using default settings, IP:127.0.0.1, Port:1234\n");
    iResult = getaddrinfo("127.0.0.1", portNum, &hints, &result);
  }

  if (iResult != 0) {
    printf("getaddrinfo failed: %d\n", iResult);
#if defined _WIN32
    WSACleanup();
#endif
    return 1;
  }

  //*******************************************************************
  // CREATE CLIENT'S SOCKET
  //*******************************************************************

#if defined __unix__ || defined __APPLE__
  s = -1;
#elif defined _WIN32
  s = INVALID_SOCKET;
#endif

  // s = socket(PF_INET, SOCK_STREAM, 0);
  s = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

#if defined __unix__ || defined __APPLE__
  if (s < 0) {
    printf("socket failed\n");
    freeaddrinfo(result);
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

  if (connect(s, result->ai_addr, result->ai_addrlen) != 0) {
    printf("\nconnect failed\n");
    freeaddrinfo(result);
#if defined _WIN32
    WSACleanup();
#endif
    exit(1);
  } else {
    //~ printf("connected to server.\n");
    //~ struct sockaddr_in sa;
    //~ char ipstr[INET_ADDRSTRLEN];

    // store this IP address in sa:
    // inet_pton(AF_INET, result->ai_addr, &(sa.sin_addr));

    //-----------------------------------
    //~ void *addr;
    char ipver[80];

    // Get the pointer to the address itself, different fields in IPv4 and IPv6
    if (result->ai_family == AF_INET) {
      // IPv4
      //~ struct sockaddr_in *ipv4 = (struct sockaddr_in *)result->ai_addr;
      //~ addr = &(ipv4->sin_addr);
      strcpy(ipver, "IPv4");
    } else if (result->ai_family == AF_INET6) {
      // IPv6
      //~ struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)result->ai_addr;
      //~ addr = &(ipv6->sin6_addr);
      strcpy(ipver, "IPv6");
    }

    // printf("\nConnected to <<<SERVER>>> with IP address: %s, %s at port:
    // %s\n", argv[1], ipver,portNum);

    //--------------------------------------------------------------------------------
    // getnameinfo() can be used to extract the IP address of the SERVER, in
    // case a hostname was
    //              supplied by the user instead.

#if defined __unix__ || defined __APPLE__
    int returnValue;
#elif defined _WIN32
    DWORD returnValue;
#endif
    const int MAX_BUFFER_SIZE = 1024;
    char receive_buffer[MAX_BUFFER_SIZE];
    memset(serverHost, 0, sizeof(serverHost));

    memset(receive_buffer, 0, sizeof(receive_buffer));
    memset(serverService, 0, sizeof(serverService));

    returnValue = getnameinfo((struct sockaddr *)result->ai_addr,
                              /*addrlen*/ result->ai_addrlen, serverHost,
                              sizeof(serverHost), serverService,
                              sizeof(serverService), NI_NUMERICHOST);

    if (returnValue != 0) {

#if defined __unix__ || defined __APPLE__
      printf("\nError detected: getnameinfo() failed with error\n");
#elif defined _WIN32
      printf("\nError detected: getnameinfo() failed with error#%d\n",
             WSAGetLastError());
#endif
      exit(1);

    } else {
      printf("\nConnected to <<<SERVER>>> extracted IP address: %s, %s at "
             "port: %s\n",
             serverHost, ipver,
             /* serverService */ portNum); // serverService is nfa
    }
    //--------------------------------------------------------------------------------

    // 接收数据
    int bytes_received = recv(s, receive_buffer, MAX_BUFFER_SIZE, 0);
    if (bytes_received < 0) {
      // 接收数据出错
      cerr << "Error receiving data: " << strerror(errno) << endl;
      return -1;
    }

    // 解析接收到的数据
    receive_buffer[bytes_received] = '\0';
    string ciphertext_str = string(receive_buffer);
    istringstream iss(ciphertext_str);
    cpp_int ciphertext_e;
    iss >> ciphertext_e;

    // 解密数据
    cpp_int plaintext_e = decrypt(ciphertext_e, d_ca, n_ca);

    // 输出解密后的明文
    cout << "Received ciphertext: " << ciphertext_e << endl;
    cout << "Decrypted plaintext: " << plaintext_e << endl;
  }

  //*******************************************************************
  // Get input while user don't type "."
  //*******************************************************************
  printf("\n--------------------------------------------\n");
  printf("you may now start sending commands to the <<<SERVER>>>\n");
  memset(&send_buffer, 0, BUFFER_SIZE);

  while (1) {
    int nonce = rand() % 1000;
    const int MAX_BUFFER_SIZE = 1024;
    cpp_int nonce_e = encrypt(nonce, e_ca, n_ca);
    string t = nonce_e.str();
    strcpy(send_buffer, t.c_str());
    send_buffer[t.size()] = '\0'; // 确保发送的数据以 '\0' 结尾
    int bytes_sent = send(s, send_buffer, MAX_BUFFER_SIZE - 1, 0);
    if (bytes_sent == -1) {
      cerr << "Error sending data: " << strerror(errno) << endl;
      return -1;
    }
    cout << "receive_buffer: " << nonce << endl;
    cout << "encrypted plaintext: " << nonce_e << endl;
    memset(&send_buffer, 0, BUFFER_SIZE);

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  }

#if defined __unix__ || defined __APPLE__
  if (bytes == -1) {
    printf("send failed\n");
    exit(1);
  }
#elif defined _WIN32
  if (bytes == SOCKET_ERROR) {
    printf("send failed\n");
    WSACleanup();
    exit(1);
  }
#endif
//*******************************************************************
// CLOSESOCKET
//*******************************************************************
#if defined __unix__ || defined __APPLE__
  close(s); // close listening socket
#elif defined _WIN32
  closesocket(s); // close listening socket
  WSACleanup();   /* call WSACleanup when done using the Winsock dll */
#endif
  return 0;
}
