#ifndef DUMMY_CONTROLLER_HPP_
# define DUMMY_CONTROLLER_HPP_

# include "Core/Controllers/IController.hpp"

namespace Core::States
{
    class DummyState : public IState
    {
        public:
            DummyState() {}

            std::shared_ptr<IState> Clone() override
            {
                return std::make_shared<DummyState>(*this);
            }

            int GetVolume(void) const
            {
                return m_volume;
            }

            bool IsPlaying(void) const
            {
                return m_playing;
            }
            void IncreaseVolume(void)
            {
                if (m_volume < 100)
                    m_volume++;
            }
            void DecreaseVolume(void)
            {
                if (m_volume > 0)
                    m_volume--;
            }
            void PlayPause(void)
            {
                m_playing = !m_playing;
            }
        private:
            int m_volume {0};
            bool m_playing {false};
    };
} //  namespace Core::States

namespace Core::Controllers
{
    class DummyController : public IController
    {
        public:
            DummyController(WidgetsID id) : IController(id)
            {

            }

            void CommandHandler(const IRButton& button) override
            {
                switch (button)
                {
                case IRButton::BTN_VOL_PLUS:
                    m_state.IncreaseVolume();
                    break;
                case IRButton::BTN_VOL_MINUS:
                    m_state.DecreaseVolume();
                    break;
                case IRButton::BTN_PLAY:
                    m_state.PlayPause();
                    break;
                default:
                    return;
                }
                UpdateState(m_state.Clone());
            }
        private:
            Core::States::DummyState m_state;
    };
} //  namespace Core::Controllers

#endif //!DUMMY_CONTROLLER_HPP_
