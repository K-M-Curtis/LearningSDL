//#include <SDL.h>
//#include <SDL_net.h>
//
//#include <iostream>
//
////#pragma comment( \
////    lib,         \
////    "E\:\\WorkSpace\\Tools\\developLinkLib\\SDL2-devel-2.30.1-VC\\SDL2-2.30.1\\lib\\x86\\SDL2.lib")
////#pragma comment( \
////    lib,         \
////    "E\:\\WorkSpace\\Tools\\developLinkLib\\SDL2-devel-2.30.1-VC\\SDL2-2.30.1\\lib\\x86\\SDL2main.lib")
////#pragma comment( \
////    lib,         \
////    "E\:\\WorkSpace\\Tools\\developLinkLib\\SDL2-devel-2.30.1-VC\\SDL2-2.30.1\\lib\\x86\\SDL2_net.lib")
//
//int main(int argc, char* argv[]) {
//  TCPsocket server_socket, client_socket;
//  IPaddress server_ip;
//  IPaddress* client_ip = nullptr;
//  bool quit = false;
//  char buffer[512] = {0};
//  // 初始化SDL_net库
//  if (SDLNet_Init() < 0) {
//    SDL_Log("SDL_net init failed: %s\n", SDLNet_GetError());
//    return -1;
//  }
//  // 解析主机和端口，nullptr表示本机默认，端口15566
//  if (SDLNet_ResolveHost(&server_ip, nullptr, 15566)) {
//    SDL_Log("SDL_net ResolveHost failed: %s\n", SDLNet_GetError());
//    return -1;
//  }
//  // 打开一个TCP socket，监听主机的端口
//  if (!(server_socket = SDLNet_TCP_Open(&server_ip))) {
//    SDL_Log("SDL_net tcp open failed: %s\n", SDLNet_GetError());
//    return -1;
//  }
//  // 等待连接，发送数据
//  while (!quit) {
//    // 检查sd是否有新的连接，如果有，就接受，打开一个新的socket
//    if ((client_socket = SDLNet_TCP_Accept(server_socket)) != nullptr) {
//      // 获取远程客户端地址
//      if ((client_ip = SDLNet_TCP_GetPeerAddress(client_socket)) != nullptr) {
//        // 输出地址和端口
//        std::cout << "Host connected: " << SDLNet_Read32(&client_ip->host)
//                  << ":" << SDLNet_Read16(&client_ip->port) << std::endl;
//        char ip[32] = {0};
//        unsigned char* part = (unsigned char*)&client_ip->host;
//        sprintf_s(ip, "%d.%d.%d.%d", *part, *(part + 1), *(part + 2),
//                  *(part + 3));
//        std::cout << "client_ip: " << ip << std::endl;
//      }
//      while (!quit) {
//        // 接收数据
//        int len = SDLNet_TCP_Recv(client_socket, buffer, 512);
//        if (len > 0) {
//          std::cout << " Received: " << buffer << std::endl;
//          if (strcmp(buffer, "exit") == 0) {
//            quit = true;
//          }
//        } else {
//          std::cout << "Connnect closed..." << std::endl;
//          break;
//        }
//      }
//      SDLNet_TCP_Close(client_socket);  // 关闭连接
//    } else {
//      // 延时一下，减少CPU占用
//      SDL_Delay(100);
//    }
//  }
//
//  SDLNet_TCP_Close(server_socket);
//  SDLNet_Quit();
//  return 0;
//}