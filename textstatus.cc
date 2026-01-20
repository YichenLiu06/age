export module textstatus;

import <string>;
import <vector>;

export class TextStatus {
    const size_t size;
    // Represents the current text that should be displayed
    std::vector<std::string> status;
    public:
    TextStatus(int size);
    void setLine(int line, const std::string &msg);
    const std::string &getLine(int line) const;
    void clear();
    int getSize() const;
};
