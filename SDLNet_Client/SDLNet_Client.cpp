//#include <SDL.h>
//#include <SDL_net.h>
//
//#include <iostream>
//
//const char DST_IP[] = "127.0.0.1";
//
//int main(int argc, char** argv) {
//  IPaddress ip;
//  TCPsocket socket;
//  bool quit = false;
//  char buffer[512] = {"Hello, I am client!"};
//
//  // ��ʼ��SDL_net��
//  if (SDLNet_Init() < 0) {
//    SDL_Log("SDLNet init failed: %s\n", SDLNet_GetError());
//    return -1;
//  }
//
//  // Ŀ��IP��ַ������ʹ�ñ��ز���
//  if (SDLNet_ResolveHost(&ip, DST_IP, 15566) < 0) {
//    SDL_Log("SDLNet Resolve Host failed: %s\n", SDLNet_GetError());
//    return -1;
//  }
//
//  // ������
//  if (!(socket = SDLNet_TCP_Open(&ip))) {
//    SDL_Log("SDLNet Tcp open failed: %s\n", SDLNet_GetError());
//    return -1;
//  }
//  int len = 0;
//  while (!quit) {
//    len = strlen(buffer) + 1;
//    // ��������
//    if (SDLNet_TCP_Send(socket, buffer, len) < len) {
//      std::cout << "SDLNet tcp send error: " << SDLNet_GetError() << std::endl;
//      return -1;
//    }
//    SDL_Delay(1000);
//  }
//
//  SDLNet_TCP_Close(socket);
//  SDLNet_Quit();
//  return 0;
//}