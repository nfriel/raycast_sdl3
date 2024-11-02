#include "lib/start.h"
#include "lib/loop.h"

int main(int argc, char *argv[])
{
    if (start())
    {
        loop(); 
    }
    
    stop();
}
