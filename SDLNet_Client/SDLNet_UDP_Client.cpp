#include <SDL.h>
#include <SDL_net.h>

#include <iostream>
#include <string>

const char DST_IP[] = "127.0.0.1";

int main(int argc, char** argv) {
  UDPsocket socket;
  IPaddress server_add;
  UDPpacket* packet = nullptr;
  bool quit = false;
  char buffer[100] = {0};

  // ��ʼ��SDL_net��
  if (SDLNet_Init() < 0) {
    SDL_Log("SDLNet init failed: %s\n", SDLNet_GetError());
    return -1;
  }

  // ��һ������˿�
  if (!(socket = SDLNet_UDP_Open(0))) {
    SDL_Log("SDLNet Tcp open failed: %s\n", SDLNet_GetError());
    return -1;
  }

  // ������������ַ
  if (SDLNet_ResolveHost(&server_add, DST_IP, 15566) < 0) {
    SDL_Log("SDLNet Resolve Host failed: %s\n", SDLNet_GetError());
    return -1;
  }

  // �������ݰ�
  if (!(packet = SDLNet_AllocPacket(512))) {
    SDL_Log("SDL_net alloc packet error: %s\n", SDLNet_GetError());
    return -1;
  }

  while (!quit) {
    time_t tt = time(nullptr);
    std::string message = "hello, I am udp client!";
    message += std::to_string(tt);
    memcpy_s(packet->data, 512, message.c_str(), message.size());
    packet->address.host = server_add.host;         // ����Ŀ���ַ
    packet->address.port = server_add.port;         // ����Ŀ��˿�
    packet->len = message.size() + 1;               // �������ݳ���
    int len = SDLNet_UDP_Send(socket, -1, packet);  // ��������
    if (len < 0) {
      SDL_Log("SDL_net udp send error: %s\n", SDLNet_GetError());
      return -1;
    }
    memset(packet->data, 0, packet->maxlen);
    SDL_Delay(2000);
  }

  SDLNet_UDP_Close(socket);
  SDLNet_FreePacket(packet);
  SDLNet_Quit();
  return 0;
}