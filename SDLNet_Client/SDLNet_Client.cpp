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
//  // 初始化SDL_net库
//  if (SDLNet_Init() < 0) {
//    SDL_Log("SDLNet init failed: %s\n", SDLNet_GetError());
//    return -1;
//  }
//
//  // 目标IP地址，这里使用本地测试
//  if (SDLNet_ResolveHost(&ip, DST_IP, 15566) < 0) {
//    SDL_Log("SDLNet Resolve Host failed: %s\n", SDLNet_GetError());
//    return -1;
//  }
//
//  // 打开连接
//  if (!(socket = SDLNet_TCP_Open(&ip))) {
//    SDL_Log("SDLNet Tcp open failed: %s\n", SDLNet_GetError());
//    return -1;
//  }
//  int len = 0;
//  while (!quit) {
//    len = strlen(buffer) + 1;
//    // 发送数据
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