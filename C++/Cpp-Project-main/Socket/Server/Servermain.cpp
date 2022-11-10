#include <iostream>
#include <algorithm>
#include "server.h"

int main(int argc, char *argv[])
{
    SokServer a(argc, argv);
    a.myServ();
}