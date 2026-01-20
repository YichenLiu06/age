module textstatus;

import <vector>;
import <string>;

TextStatus::TextStatus(int size): size{size}, status{size, ""} {}

void TextStatus::setLine(int line, const std::string &msg){
    status[line] = msg;
}

const std::string &TextStatus::getLine(int line) const {
    return status[line];
}

void TextStatus::clear(){
    for(int i=0; i<size; ++i){
        status[i] = "";
    }
}

int TextStatus::getSize() const {
    return size;
}
