#ifndef SPOTIFY_VIEW_HPP_
# define SPOTIFY_VIEW_HPP_

# include "GUI/Views/IView.hpp"

# include "GUI/Views/Spotify/SpotifyPlayerPanel.hpp"

namespace GUI::Views
{

    class SpotifyView : public IView
    {
        public:
            SpotifyView(wxWindow *parent, const wxSize &size, ViewsID view_id);
        
        protected:
            void CreateView(void) override;
            void UpdateView(std::shared_ptr<Core::States::IState>state) override;

            GUI::Views::Components::SpotifyPlayerPanel *m_player;
    };

} //  namespace GUI::Views

#endif //!SPOTIFY_VIEW_HPP_