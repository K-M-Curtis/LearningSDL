#include <SDL.h>
#include <SDL_net.h>

#include <iostream>

int main(int argc, char* argv[]) {
  UDPsocket server_socket;
  UDPpacket* packet = nullptr;
  bool quit = false;

  // 初始化SDL_net库
  if (SDLNet_Init() < 0) {
    SDL_Log("SDL_net init failed: %s\n", SDLNet_GetError());
    return -1;
  }

  // 打开一个socket端口15566
  if (!(server_socket = SDLNet_UDP_Open(15566))) {
    SDL_Log("SDL_net tcp open failed: %s\n", SDLNet_GetError());
    return -1;
  }

  // 给数据包开辟空间
  if (!(packet = SDLNet_AllocPacket(512))) {
    SDL_Log("SDL_net alloc packet error: %s\n", SDLNet_GetError());
    return -1;
  }

  while (!quit) {
    // 等待数据包
    if (SDLNet_UDP_Recv(server_socket, packet)) {
      std::cout << "UDP Packet incoming " << std::endl;
      std::cout << "Channel: " << packet->channel << std::endl;
      std::cout << "Data: " << packet->data << std::endl;
      std::cout << "Len: " << packet->len << std::endl;
      std::cout << "MaxLen: " << packet->maxlen << std::endl;
      std::cout << "Status: " << packet->status << std::endl;

      unsigned short port = SDLNet_Read16(&packet->address.port);
      char ip[32] = {0};
      unsigned char* part = (unsigned char*)&packet->address.host;
      sprintf_s(ip, "%d.%d.%d.%d", *part, *(part + 1), *(part + 2),
                *(part + 3));
      std::cout << "client_ip: " << ip << ":" << port << std::endl;
      memset(packet->data, 0, packet->maxlen);  // 清空缓存数据
    }
  }

  SDLNet_UDP_Close(server_socket);
  SDLNet_FreePacket(packet);
  SDLNet_Quit();
  return 0;
}
