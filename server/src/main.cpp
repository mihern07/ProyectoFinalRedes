#include "Server.h"

int main()
{
    Server server("127.0.0.1", "7777");
    server.ProcessMessages();

    return 0;
}