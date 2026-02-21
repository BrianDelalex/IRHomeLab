#ifndef ICONTROLLER_HPP_
# define ICONTROLLER_HPP_

# include "Core/States/IState.hpp"


namespace Core::Controllers
{

class IController
{
    public:
        virtual ~IController() = default;

        virtual SetStateChangeCallback(std::function<void(States::IState *)>) = 0;
};
} //  namespace Core::Controllers

#endif //!ICONTROLLER_HPP_