#include <iostream>
#include <string>
#include <cctype>


class PasswordValidator 
{
protected:
    PasswordValidator* mNextValidator;

public:
    PasswordValidator() : mNextValidator(nullptr) {}

    void setNext(PasswordValidator* validator) 
    {
        mNextValidator = validator;
    }

    virtual bool validate(const std::string& password) = 0;
};


// Проверка на минимальную длину
class LengthValidator : public PasswordValidator 
{
private:
    int mMinLength;

public:
    LengthValidator(int length) : mMinLength(length) {}

    bool validate(const std::string& password) override 
    {
        if (password.length() >= mMinLength) 
        {
            if (mNextValidator != nullptr)
                return mNextValidator->validate(password);
            return true;
        } 
        else 
        {
            return false;
        }
    }
};

// Проверка наличия цифр в пароле
class DigitValidator : public PasswordValidator 
{
public:

    bool validate(const std::string& password) override 
    {
        for (char ch : password) 
        {
            if (std::isdigit(ch)) 
            {
                if (mNextValidator != nullptr)
                    return mNextValidator->validate(password);

                return true;
            }
        }
        return false;
    }
};

// Проверка наличия специальных символов в пароле
class SpecialCharValidator : public PasswordValidator 
{
public:
    bool validate(const std::string& password) override 
    {
        for (char ch : password) 
        {
            if (!std::isalnum(ch)) 
            {
                if (mNextValidator != nullptr)
                    return mNextValidator->validate(password);
                return true;
            }
        }
        return false;
    }
};

int main() 
{
    LengthValidator lengthValidator(8);
    DigitValidator digitValidator;
    SpecialCharValidator specialCharValidator;

    lengthValidator.setNext(&digitValidator);
    digitValidator.setNext(&specialCharValidator);


    PasswordValidator* validator = &lengthValidator;

    std::string ps1 = "weak";
    std::string ps2 = "strong123";
    std::string ps3 = "veryStrong$%123!!";

    if (validator->validate(ps1))
        std::cout << "Password " << ps1 << " is valid!" << std::endl;
    else
        std::cout << "Password " << ps1 << " is invalid!" << std::endl;


    if (validator->validate(ps2))
        std::cout << "Password " << ps2 << " is valid!" << std::endl;
    else
        std::cout << "Password " << ps2 << " is invalid!" << std::endl;


    if (validator->validate(ps3))
        std::cout << "Password " << ps3 << " is valid!" << std::endl;
    else
        std::cout << "Password " << ps3 << " is invalid!" << std::endl;
}