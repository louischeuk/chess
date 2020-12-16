#include <exception>
#include <string>

class AnyError : public std::exception {
protected:
    std::string explaination;
public:
    AnyError(const std::string& msg) noexcept : explaination(msg){}
    const char* what() const noexcept override {
        return explaination.c_str();
    }
};

class SquareError : public AnyError {
private:
    std::string square;
public:
    SquareError(const std::string& msg, const std::string& square) noexcept :
        AnyError(msg), square(square) {
            explaination = explaination + square;
        }
};

class ColorError : public AnyError {
private:
    std::string color;
    std::string explaination_two;
public:
    ColorError(const std::string& msg, const std::string color,
    const std::string& msg_two) noexcept :
        AnyError(msg), color(color), explaination_two(msg_two) {
            explaination = explaination + color + explaination_two;
        }
};
