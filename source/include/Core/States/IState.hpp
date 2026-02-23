#ifndef ISTATE_HPP_
# define ISTATE_HPP_

namespace Core::States
{
    class IState
    {
        public:
            virtual std::shared_ptr<IState> Clone() = 0;
    };
} //  namespace Core::States

#endif //!ISTATE_HPP_