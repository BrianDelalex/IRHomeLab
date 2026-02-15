# include <unistd.h>
# include <fcntl.h>

# include <iostream>
# include <string>

constexpr std::string IRDRIVER_DEVICE_PATH = "/dev/irdriver";

int main(void)
{
    int fd = open(IRDRIVER_DEVICE_PATH.c_str(), O_WRONLY);
    if (fd == -1)
    {
        std::cerr << "Error while opening " << IRDRIVER_DEVICE_PATH << std::endl;
        return 84;
    }
    while (true)
    {
        std::string input;

        std::cout << "Enter the remote controller code to simulate: ";
        std::cin >> input;
        try
        {
            std::stoi(input);
        } 
        catch (std::invalid_argument &)
        {
            std::cerr << "The input isn't a numerical value!" << std::endl;
            continue;
        }
        catch (std::out_of_range &)
        {
            std::cerr << "Invalid value!" << std::endl;
            continue;
        }

        if (write(fd, input.data(),  input.size()) == -1)
        {
            std::cerr << "Error while writing to " << IRDRIVER_DEVICE_PATH << std::endl;
        }
    }
}