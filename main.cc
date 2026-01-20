import pong;
import flappybird;

import <string>;
import <iostream>;

int main(int argc, char* argv[]){
    if(argc <= 1){
        std::cout << "Please select either pong or flappybird using a command line argument" << std::endl;
    }
    else{
        std::string game = argv[1];
        if(game == "pong"){
            Pong pong;
            pong.go();
        }
        else if(game == "flappybird"){
            FlappyBird flappybird;
            flappybird.go();
        }
        else {
            std::cout << "Please select either pong or flappybird using a command line argument" << std::endl;
        }
    }
}
