#include <iostream>
#include "server.h"
#include <signal.h>
#include <iostream>

void exitHandler(int s)
{
    return;
}

int main(int argc, char* argv[])
{
	if (argc < 2)
		return 1;
    Server serv(argv[1],80,false);
    serv.addMethod("/Get_KMK",[](Package param)->std::string
    {
        auto iParam = param.getParam();
        Randomizer rd('0','9');
        if (param.paramSize() >= 2)
            rd.changeSeed(std::stoi(iParam.begin()->second), std::stoi(std::next(iParam.begin())->second));
        std::array<char, 22> KMK;
        std::generate(KMK.begin(), KMK.end(), [&rd]() {return rd.getRandomValue(); });
        return KMK.data();
    });
    serv.start();

    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = exitHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
    pause();
    serv.stop();
    return 0;
}
